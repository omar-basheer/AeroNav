//  Created by Omar Basheer on 11/20/22.
#ifndef ROUTES_H
#define ROUTES_H

#include <map>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @class Route
 * @brief Represents a route between two airports.
 *
 * The Route class stores information about a route between two airports, including the source airport code,
 * destination airport code, airline code, and number of stops. It also provides methods for accessing and
 * manipulating this information.
 */
class Route{

private:
    std::string Source_AirportCode; /**< The code of the source airport. */
    std::string Destination_AirportCode; /**< The code of the destination airport. */
    std::string AirlineCode; /**< The code of the airline operating the route. */
    std::string Stops; /**< The number of stops in the route. */

public:
    /**
     * @brief Default constructor for the Route class.
     */
    Route();

    /**
     * @brief Constructs a new Route object.
     *
     * @param Destination_AirportCode The code of the destination airport.
     * @param airlineCode The code of the airline operating the route.
     */
    Route(std::string Destination_AirportCode, std::string airlineCode);

    /**
     * @brief Retrieves the source airport code associated with the route.
     *
     * @return The source airport code as a string.
     */
    const std::string getSA_Code() const;

    /**
     * @brief Retrieves the destination airport code associated with the route.
     *
     * @return The destination airport code as a string.
     */
    const std::string getDA_Code() const;

    /**
     * @brief Retrieves the airline code associated with the route.
     *
     * @return The airline code as a string.
     */
    const std::string getAirline_Code() const;

    /**
     * @brief Retrieves the number of stops in the route.
     *
     * @return The number of stops as a string.
     */
    const std::string getStops() const;

    /**
     * @brief Converts the Route object to a string representation.
     *
     * @return The string representation of the Route object.
     */
    const std::string toString() const;

    /**
     * @brief A map that stores the routes for each airport.
     */
    static std::map<std::string, std::vector<std::string>> AirportRoutesMap;

    /**
     * @brief A map that stores the routes for each airline.
     */
    static std::map<std::vector<std::string>, std::vector<std::string>> AirlineRoutesMap;

    /**
     * @brief Converts a string representation of a vector to a vector of strings.
     *
     * @param vector_string The string representation of the vector.
     * @return The vector of strings.
     */
    static std::vector<std::string> stringToVec(std::string vector_string);

    /**
     * @brief Converts a vector of strings to a string representation.
     *
     * @param string_vector The vector of strings.
     * @return The string representation of the vector.
     */
    static std::string const vecToString(std::vector<std::string> string_vector);

    /**
     * @brief Reads the airport routes from a file and returns a map of airport codes and their routes.
     *
     * @param filename The name of the file to read from.
     * @return A map of airport codes and their routes.
     */
    static std::map<std::string, std::vector<std::string>> AirportRouteReader(const std::string &filename);

    /**
     * @brief Reads the airline routes from a file and returns a map of airline codes and their routes.
     *
     * @param filename The name of the file to read from.
     * @return A map of airline codes and their routes.
     */
    static std::map<std::vector<std::string>, std::vector<std::string>> AirlineRouteReader(const std::string &filename);

    /**
     * @brief Prints the contents of a map of airport routes.
     *
     * @param thisMap The map of airport routes.
     */
    static void printMap(std::map<std::string, std::vector<std::string>> thisMap);

    /**
     * @brief Prints the contents of a map of airline routes.
     *
     * @param thisMap The map of airline routes.
     */
    static void printMap(std::map<std::vector<std::string>, std::vector<std::string>> thisMap);

    /**
     * @brief Checks if a deque contains a specific value.
     *
     * @param deq The deque to search in.
     * @param value The value to search for.
     * @return True if the deque contains the value, false otherwise.
     */
    static bool contains(std::deque<std::string> deq, std::string value);

    /**
     * @brief Checks if a vector contains a specific value.
     *
     * @param vec The vector to search in.
     * @param value The value to search for.
     * @return True if the vector contains the value, false otherwise.
     */
    static bool contains(std::vector<std::string> vec, std::string value);

    /**
     * @brief Finds a route between two airports.
     *
     * @param start_airport The code of the starting airport.
     * @param goal_airport The code of the destination airport.
     * @return The route between the two airports as a string.
     */
    static std::string findRoute(std::string start_airport, std::string goal_airport);

    /**
     * @brief Constructs the solution path for a route.
     *
     * @param solution_map The map containing the solution path.
     * @param child The child node of the solution path.
     * @return The solution path as a string.
     */
    static std::string solution_path(std::map<std::string, std::string> solution_map, std::string child);
};

#endif // ROUTES_H
