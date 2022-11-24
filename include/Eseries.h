#include <math.h>
#include <set>
#pragma once

/*
 * To get the E24 sets m is the set indexed from 0 of [3,6,12,24].
 * Set is calculated with Set=3*2^m.
 * n should be in the range [0,Set-1].
 */
double E24Series(unsigned int n, unsigned int m);

/*
 * To get the E192 sets m is the set indexed from 0 of [3,6,12,24,48,96,192].
 * Set is calculated with Set=3*2^m.
 * Note 3-24 are not E24 sets as they are calulated differently
 * n should be in the range [0,Set-1].
 */
double E192Series(unsigned int n, unsigned int m);

/*
 * To get the E192 and E24 sets m is the set indexed from 0 of [3,6,12,24,48,96,192].
 * Set is calculated with Set=3*2^m.
 * Note 3-24 are not E24 sets as they are calulated differently.
 * if m is in the range [0,3] then E24 is used.
 * if m is in the range [4,6] then E192 is used with the added E24 set.
 */
std::set<double> E192_E24_Series(unsigned int m);
