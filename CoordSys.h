#ifndef _CoordSys_CoordSys_h_
#define _CoordSys_CoordSys_h_

#include "cmath"

class Cartesian{
public:
	double x;
	double y;
	double z;
	double dx;
	double dy;
	double dz;
};

class Keplerian{
public:
	double a;
	double e;
	double i;
	double omBig;
	double omMin;
	double M;
	
	double E;
	double v;
	
	void exAnomCalc();
	void midAnomCalc();
	void trueAnomCalc();
};

#endif
