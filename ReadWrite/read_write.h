//  Created by Omar Basheer on 11/27/22.

#ifndef READWRITE_H
#define READWRITE_H

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * @class ReadWrite
 * @brief A class that handles reading and writing operations for flight information.
 *
 * This class provides static methods to read user input file containing start city and country,
 * and destination city and country. It also calculates the haversine distance between airports
 * in a solution path and writes the flight plan to an output file.
 */
class ReadWrite {
private:
    static std::string StartCity; /**< The start city a given flight. */
    static std::string StartCountry; /**< The start country a given flight. */
    static std::string Destination_City; /**< The destination city a given flight. */
    static std::string Destination_Country; /**< The destination country a given flight. */

public:
    /**
     * @brief Retrieves the start city.
     * 
     * @return The start city as a std::string.
     */
    static std::string getStartCity();

    /**
     * @brief Retrieves the start country.
     * 
     * @return The start country as a std::string.
     */
    static std::string getStartCountry();

    /**
     * @brief Retrieves the destination city.
     * 
     * @return The destination city as a std::string.
     */
    static std::string getDestination_City();

    /**
     * @brief Retrieves the destination country.
     * 
     * @return The destination country as a std::string.
     */
    static std::string getDestination_Country();

    /**
     * @brief Sets the start city.
     * 
     * @param city The start city to set.
     */
    static void setStartCity(const std::string city);

    /**
     * @brief Sets the start country.
     * 
     * @param country The start country to set.
     */
    static void setStartCountry(const std::string country);

    /**
     * @brief Sets the destination city.
     * 
     * @param city The destination city to set.
     */
    static void setDestinationCity(const std::string city);

    /**
     * @brief Sets the destination country.
     * 
     * @param country The destination country to set.
     */
    static void setDestinationCountry(const std::string country);

    /**
     * @brief Reads user input file containing start city and country, and destination city and country.
     * 
     * @param input_filename The file name of the user's input file.
     */
    static void inputFileReader(const std::string &input_filename);

    /**
     * @brief Calculates haversine distance between airports in a solution path and accumulates the values
     * to obtain the total distance between the start and goal airports given a particular solution path.
     * Passes solution path with lowest distance to outputFileWriter for file writing.
     * 
     * @param all_starts A string vector of the IATA codes of all airports in the given start city.
     * @param all_goals A string vector of the IATA codes of all airports in the given goal city.
     */
    static void haversineHelper(const std::vector<std::string> all_starts, const std::vector<std::string> all_goals);

    /**
     * @brief Writes the flight plan to an output file.
     * 
     * @param flight_path The flight path to be written to the output file.
     */
    static void outputFileWriter(const std::string flight_path);
};

#endif // READWRITE_H
