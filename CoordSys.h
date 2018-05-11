#ifndef _model_CoordSys_h_
#define _model_CoordSys_h_

#include "cmath"

class CCartesian{
public:
	double x;
	double y;
	double z;
	double dx;
	double dy;
	double dz;
};

class CKeplerian{
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

class CAnglesRot{
public:
	double x;
	double y;
	double z;
	double teta;
	double fi;
	double psi;
	
	CAnglesRot(double aX, double aY, double aZ, double aTeta, double aFi, double aPsi)
		{
		x = aX;
		y = aY;
		z = aZ;
		teta = aTeta;
		fi = aFi;
		psi = aPsi;
		}
};

CCartesian KepToDec(CKeplerian);
CAnglesRot RotVector(CAnglesRot);

#endif
