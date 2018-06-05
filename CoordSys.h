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

class CSpherical{
public:
	double lon; // longitude
	double lat; // latitude
	double radEarth = 6371302.0; // радиус Земли - метр
	// углы поворота
	double i;
	double omBig;
	double omMin;
};

class CAlmanac{
public:
	// дата
	int yearAlm;
	int monthAlm;
	int dayAlm;
	int year;
	int month;
	int day;
	double lambda;
	double Tlambda;
	double di;
	double w;
	double e;
	double dT;
	double dTT;
	double Tcp = 43200;
	double icp = 63;
	double ae = 6378.136;			//экваториальный радиус Земли
	double C = -1082.62575*pow(10,-6);	// коэффициент при второй зональной  гармонике  разложения
									    // геопотенциала	в ряд по сферическим функциям
	double ny = 398600.4418;		// константа гравитационного поля Земли
	double omEarth = 0.7292115*pow(10,-4);  // угловая скорость вращения Земли
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

class CDatetime{
public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int micro;
};

class CDate{
public:
	int year;
	int month; 
	int day;
};

class testAa{
public:
	double x;
private:
	double y;
};

class testBb : testAa
{
public:
	double z;
};

CCartesian KepToDec(CKeplerian);
CCartesian ModelAlmDec(CAlmanac);
CAnglesRot RotVector(CAnglesRot);
CCartesian SphCoordToDec(CSpherical);

#endif
