#include <math.h>
#include <set>
#include "Eseries.h"

#define DE_FACTO_E24                                                                               \
	{ 2.7, 3, 3.3, 3.6, 3.9, 4.3, 4.7, 8.2 }
#define EPILON 0.0001

/*
 * To get the E24 sets m is the set indexed from 0 of [3,6,12,24].
 * Set is calculated with Set=3*2^m.
 * n should be in the range [0,Set-1].
 */
double E24Series(unsigned int n, unsigned int m) {
	m = 3 * (1 << m);
	double e24[8] = DE_FACTO_E24;
	double CalcR = std::pow(10, (double)n / (double)m);
	CalcR = std::round(CalcR * 10) / 10;
	for (auto i : e24)
		if (std::abs(CalcR - i) <= 0.1 + EPILON) {
			CalcR = i;
			break;
		}
	return CalcR;
}

/*
 * To get the E192 sets m is the set indexed from 0 of [3,6,12,24,48,96,192].
 * Set is calculated with Set=3*2^m.
 * Note 3-24 are not E24 sets as they are calulated differently
 * n should be in the range [0,Set-1].
 */
double E192Series(unsigned int n, unsigned int m) {
	m = 3 * (1 << m);
	double CalcR = std::pow(10, (double)n / (double)m);
	CalcR = std::round(CalcR * 100) / 100;
	return CalcR;
}

/*
 * To get the E192 and E24 sets m is the set indexed from 0 of
 * [3,6,12,24,48,96,192]. Set is calculated with Set=3*2^m. Note 3-24 are not
 * E24 sets as they are calulated differently. if m is in the range [0,3] then
 * E24 is used. if m is in the range [4,6] then E192 is used with the added E24
 * set.
 */
std::set<double> E192_E24_Series(unsigned int m) {
	std::set<double> E192_E24_set;
	unsigned int Em = 3 * (1 << m);
	/* Set is only E24 return it */
	if (m <= 3) {
		for (unsigned int i = 0; i < Em; i++)
			E192_E24_set.insert(E24Series(i, m));
		return E192_E24_set;
	}
	/* Set is combined E24 and E192 calculate it */
	for (unsigned int i = 0; i < Em; i++)
		E192_E24_set.insert(E192Series(i, m));
	for (unsigned int i = 0; i < 24; i++)
		E192_E24_set.insert(E24Series(i, 3));
	return E192_E24_set;
}
