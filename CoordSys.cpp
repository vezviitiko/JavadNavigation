#include <Core/Core.h>
#include "CoordSys.h"

using namespace Upp;

void Keplerian::midAnomCalc()
{
	M = E - e * sin(E);
}

void Keplerian::exAnomCalc()
{
	double EE = M;
	double E1;
	
	for (int i = 0; i < 4; i++)
	{
		E1 = e * sin(EE) + M;
	}
	
	E = E1;
}

void Keplerian::trueAnomCalc()
{
	double at2Sin = (sqrt(1.0 - sqr(e))*sin(E))/(1.0 - e*cos(E));
	double at2Cos = ((cos(E)- e)/(1.0 - e*cos(E)));
	
	v = atan2(at2Sin, at2Cos);
}


CONSOLE_APP_MAIN
{
	
}
