#ifndef _model_CoordSys_h_
#define _model_CoordSys_h_

#include <Core/Core.h>
#include "cmath"

using namespace Upp;

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

	double lon; // longitude - долгота
	double lat; // latitude  - широта
	double hgt; // height    - высота
	
	
	double a = 6378137.;    	// BigSemiaxis м
	double b = 6356752.3142;	// SmallSemiaxis м
	double alph = 298.257223563;	// ellipsoid compression
	double e2 = 0.00669437999014; // первый эксцентриситет
	double e12 = 0.0067394967422751; // второй эксцентриситет
	double c = 6399593.62580398; //полярный радиус кривизны поверхности
	CSpherical () {}
	CSpherical(double slat, double slon, double shgt)
	{
		lat = slat;
		lon = slon;
		hgt = shgt;
	}
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

CCartesian KepToDec(CKeplerian);
CCartesian ModelAlmDec(CAlmanac);
CAnglesRot RotVector(CAnglesRot);
CCartesian SphCoordToDec(CSpherical);
CSpherical DecToSphCoord(CCartesian car);
double RadEarthLat(double lat);
double DegreesToRad(double in);
double RadToDegrees(double in);

#endif
