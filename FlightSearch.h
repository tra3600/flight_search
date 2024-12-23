#ifndef FLIGHTSEARCH_H
#define FLIGHTSEARCH_H

#include <string>
#include <vector>

class FlightSearch {
public:
    FlightSearch(const std::string& apiKey);
    std::string findCheapestFlight(const std::string& departureCity, const std::string& destinationCity, const std::vector<std::pair<std::string, std::string>>& dateRange);

private:
    std::string apiKey;
    std::string sendRequest(const std::string& url);
    std::vector<std::pair<std::string, std::string>> generateDateRange(int startMonths, int endMonths);
};

#endif // FLIGHTSEARCH_H