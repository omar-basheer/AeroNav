// Haversine
// Created by omar on 11/28/22.
// This code is contributed by Mahadev.
// Obtained from GeeksForGeeks.org

#include <cmath>
#include <iostream>
#include "haversine.h"

/**
 * Calculates the distance between two points on the Earth's surface using the Haversine formula.
 *
 * @param lat1 The latitude of the first point in degrees.
 * @param lon1 The longitude of the first point in degrees.
 * @param lat2 The latitude of the second point in degrees.
 * @param lon2 The longitude of the second point in degrees.
 * @return The distance between the two points in kilometers.
 */
double haversine(double lat1, double lon1, double lat2, double lon2)
{
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1)*M_PI / 180.0;
    lat2 = (lat2)*M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

// Driver code
int main()
{
   double lat1 = 51.5007;
   double lon1 = 0.1246;
   double lat2 = 40.6892;
   double lon2 = 74.0445;

   std::cout << haversine(lat1, lon1, lat2, lon2) << " K.M.";
   return 0;
}
