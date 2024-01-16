// Created by Omar Basheer on 11/19/22.

#ifndef AIRPORT_H
#define AIRPORT_H

#include <map>
#include <string>
#include <vector>

/**
 * @class Airport
 * @brief Represents an airport with its details such as name, city, country, IATA code, latitude, and longitude. Provides methods to access and manipulate the airport information, as well as read airport data from a file
 * and create a map of airports. It also includes utility methods to convert the airport information to a string representation
 * and print the contents of a map of airports.
 */
class Airport
{

private:
    std::string AirportName;
    std::string AirportCity;
    std::string Country;
    std::string IATA_Code;
    std::string Latitude;
    std::string Longitude;

public:
    /**
     * @brief Default constructor for the Airport class.
     * Initializes all member variables to empty strings.
     */
    Airport();

    /**
     * @brief Constructor for the Airport class.
     *
     * @param airportName The name of the airport.
     * @param airportCity The city where the airport is located.
     * @param country The country where the airport is located.
     * @param iataCode The IATA code of the airport.
     * @param latitude The latitude coordinate of the airport.
     * @param longitude The longitude coordinate of the airport.
     */
    Airport(std::string airportName, std::string airportCity, std::string country, std::string iataCode, std::string latitude, std::string longitude);

    /**
     * @brief Get the name of the airport.
     *
     * @return The name of the airport as a string.
     */
    const std::string getAirportName() const;

    /**
     * @brief Get the city of the airport.
     *
     * @return The city of the airport as a string.
     */
    const std::string getAirportCity() const;

    /**
     * @brief Get the country of the airport.
     *
     * @return The country of the airport as a string.
     */
    const std::string getCountry() const;

    /**
     * @brief Get the IATA code of the airport.
     *
     * @return The IATA code as a string.
     */
    const std::string getIataCode() const;

    /**
     * @brief Gets the latitude of the airport.
     *
     * @return The latitude of the airport as a string.
     */
    const std::string getLatitude() const;

    /**
     * @brief Get the longitude of the airport.
     *
     * @return The longitude of the airport as a string.
     */
    const std::string getLongitude() const;

    /**
     * @brief Converts the airport information to a string representation.
     *
     * @return A string representation of the airport information.
     */
    std::string const toString() const;

    /**
     * @brief Converts a vector of strings to a string representation.
     *
     * @param string_vector The vector of strings to be converted.
     * @return The string representation of the vector.
     */
    static std::string vecToString(const std::vector<std::string> string_vector);

    /**
     * @brief Reads airport data from a file and creates a map of airports.
     * The file should be in CSV format with the following columns:
     * 1. Airport ID
     * 2. Name
     * 3. City
     * 4. Country
     * 5. IATA code
     * 6. Latitude
     * 7. Longitude
     *
     * @param filename The name of the file to read the airport data from.
     * @return A map of airports, where the key is a vector of strings containing the IATA code, city, and country,
     *         and the value is an Airport object containing the airport details.
     */
    static std::map<std::vector<std::string>, Airport> AirportFileReader(const std::string &filename);


    /**
     * @brief A map that associates a vector of strings with an Airport object.
     *
     * The keys of the map are vectors of strings, and the values are Airport objects.
     * This map allows efficient lookup of an Airport based on a vector of strings.
     */
    static std::map<std::vector<std::string>, Airport> AirportMap;

    /**
     * @brief Prints the contents of a map of airports.
     *
     * @param thisMap The map of airports to be printed.
     */
    static void printMap(const std::map<std::vector<std::string>, Airport> thisMap);
};

#endif // AIRPORT_H
