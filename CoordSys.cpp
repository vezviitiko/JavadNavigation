#include <Core/Core.h>
#include "CoordSys.h"
#include "kamaz.h"

using namespace Upp;

void CKeplerian::midAnomCalc()
{
	M = E - e * sin(E);
}

void CKeplerian::exAnomCalc()
{
	double EE = M;
	double E1;
	
	for (int i = 0; i < 4; i++)
	{
		E1 = e * sin(EE) + M;
	}
	
	E = E1;
}

void CKeplerian::trueAnomCalc()
{
	double at2Sin = (sqrt(1.0 - sqr(e))*sin(E))/(1.0 - e*cos(E));
	double at2Cos = ((cos(E)- e)/(1.0 - e*cos(E)));
	
	v = atan2(at2Sin, at2Cos);
}

double RadEarthLat(double lat)
{
	double a = 6378137.;    // BigSemiaxis м
	double b = 6356752.3142; // SmallSemiaxis м
	
	// перевод градусов в радианы
	lat = DegreesToRad(lat);
	// геодезической широты перейти к геоцентрической широте
	lat = (a/b)*tan(lat);

	return sqrt((pow(a,4.) + pow(b,4.)*pow(lat,2.)) / (pow(a,2.) + pow(b,2.)*pow(lat,2.)));
}

// Функция перевода градусов в радианы
double DegreesToRad(double in)
{
	return in*PI/180.;
}
