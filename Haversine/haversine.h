//  Created by omar on 11/28/22.

#ifndef HAVERSINE_H
#define HAVERSINE_H
#include <cmath>

/**
 * @brief Calculates the distance between two points on the Earth's surface using the Haversine formula.
 *
 * @param lat1 The latitude of the first point in degrees.
 * @param lon1 The longitude of the first point in degrees.
 * @param lat2 The latitude of the second point in degrees.
 * @param lon2 The longitude of the second point in degrees.
 * @return The distance between the two points in kilometers.
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

#endif // HAVERSINE_H 
