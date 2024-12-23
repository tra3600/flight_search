#include <iostream>
#include "FlightSearch.h"

int main() {
    // Remplacez par votre propre clé API Skyscanner
    std::string apiKey = "YOUR_API_KEY";

    FlightSearch fs(apiKey);

    std::vector<std::pair<std::string, std::string>> dateRange = fs.generateDateRange(6, 10);

    std::string cheapestFlightFromParis = fs.findCheapestFlight("PAR", "BKK", dateRange);
    std::string cheapestFlightFromRome = fs.findCheapestFlight("ROM", "BKK", dateRange);

    std::cout << "Cheapest flight from Paris to Bangkok: " << cheapestFlightFromParis << std::endl;
    std::cout << "Cheapest flight from Rome to Bangkok: " << cheapestFlightFromRome << std::endl;

    return 0;
}