include "FlightSearch.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <ctime>

FlightSearch::FlightSearch(const std::string& apiKey) : apiKey(apiKey) {}

std::string FlightSearch::sendRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, std::string* s) -> size_t {
            s->append(static_cast<char*>(contents), size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

std::vector<std::pair<std::string, std::string>> FlightSearch::generateDateRange(int startMonths, int endMonths) {
    std::vector<std::pair<std::string, std::string>> dateRange;
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    for (int i = startMonths; i <= endMonths; ++i) {
        std::tm departureDate = *now;
        departureDate.tm_mon += i;
        std::mktime(&departureDate);
        std::tm returnDate = departureDate;
        returnDate.tm_mday += 7; // Assume a 7-day trip
        std::mktime(&returnDate);

        char buffer1[11], buffer2[11];
        strftime(buffer1, sizeof(buffer1), "%Y-%m-%d", &departureDate);
        strftime(buffer2, sizeof(buffer2), "%Y-%m-%d", &returnDate);

        dateRange.emplace_back(buffer1, buffer2);
    }
    return dateRange;
}

std::string FlightSearch::findCheapestFlight(const std::string& departureCity, const std::string& destinationCity, const std::vector<std::pair<std::string, std::string>>& dateRange) {
    std::string cheapestFlight;
    double minPrice = std::numeric_limits<double>::max();

    for (const auto& dates : dateRange) {
        std::string url = "https://partners.api.skyscanner.net/apiservices/browseroutes/v1.0/US/USD/en-US/" + departureCity + "/" + destinationCity + "/" + dates.first + "/" + dates.second + "?apiKey=" + apiKey;
        std::string response = sendRequest(url);

        Json::CharReaderBuilder readerBuilder;
        Json::Value root;
        std::string errs;
        std::istringstream s(response);
        if (Json::parseFromStream(readerBuilder, s, &root, &errs)) {
            for (const auto& quote : root["Quotes"]) {
                double price = quote["MinPrice"].asDouble();
                if (price < minPrice) {
                    minPrice = price;
                    cheapestFlight = "Departure: " + dates.first + ", Return: " + dates.second + ", Price: " + std::to_string(price) + " USD";
                }
            }
        }
    }
    return cheapestFlight;
}