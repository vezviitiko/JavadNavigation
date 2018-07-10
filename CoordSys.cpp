#include "CoordSys.h"

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
	double at2Sin = (sqrt(1. - sqr(e))*sin(E))/(1.0 - e*cos(E));
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
	return in*M_PI/180.;
}
// Функция перевода радиан в градусы
double RadToDegrees(double in)
{
	return in*180./M_PI;
}

CCartesian KepToDec(CKeplerian kep)
{
	CCartesian car;
	
	// находим x ------
	kep.exAnomCalc();
	car.x = kep.a*cos(kep.E);
	
	// находим y ------
	kep.trueAnomCalc();
	
	// находим растояние от оси x до орбиты
	double dxo = kep.a*sqrt(1-pow(kep.e,2));
	// находим половину расстояния до фокуса
	double c = sqrt(pow(kep.a,2)-pow(dxo,2));
	// находим разницу между x и расстоянием до фокуса
	double dxc = car.x-c;
	car.y = dxc*sin(kep.v);
		
	// находим z ------
	car.z = 0;
		
	RDUMP(car.x);
	RDUMP(car.y);
	RDUMP(car.z);

	// поворот вектора
	CAnglesRot ang(car.x,car.y,car.z,kep.i,kep.omBig,kep.omMin);
	ang = RotVector(ang);
	
	car.x = ang.x;
	car.y = ang.y;
	car.z = ang.z;
	
	RDUMP(car.x);
	RDUMP(car.y);
	RDUMP(car.z);
	return car;
}

CAnglesRot RotVector(CAnglesRot ang)
{
	// матрица поворота
	double **arrRotMat = new double* [3];
		for (int count = 0; count < 3; count++)
			arrRotMat[count] = new double [3];

	arrRotMat[0][0] = cos(ang.fi)*cos(ang.psi)-sin(ang.fi)*sin(ang.psi)*cos(ang.teta);
	arrRotMat[1][0] = -sin(ang.fi)*cos(ang.psi)-cos(ang.fi)*sin(ang.psi)*cos(ang.teta);
	arrRotMat[2][0] = sin(ang.psi)*sin(ang.teta);
	arrRotMat[0][1] = cos(ang.fi)*sin(ang.psi)+sin(ang.fi)*cos(ang.psi)*cos(ang.teta);
	arrRotMat[1][1] = -sin(ang.fi)*sin(ang.psi)+cos(ang.fi)*cos(ang.psi)*cos(ang.teta);
	arrRotMat[2][1] = -cos(ang.psi)*sin(ang.teta);
	arrRotMat[0][2] = sin(ang.fi)*sin(ang.teta);
	arrRotMat[1][2] = sin(ang.fi)*sin(ang.teta);
	arrRotMat[2][2] = cos(ang.teta);
	
	// входной вектор
	double *inVector = new double[3];
	
	inVector[0] = ang.x;
	inVector[1] = ang.y;
	inVector[2] = ang.z;
	
	double *outVector = new double[3];
	for(int i=0; i<3; i++)
	{
		outVector[i]=0;
		for(int j=0; j<3; j++)
		{
			outVector[i]+=arrRotMat[i][j]*inVector[j];
		}
	}

	ang.x = outVector[0];
	ang.y = outVector[1];
	ang.z = outVector[2];
	
	// освобождение памяти
	delete [] inVector;
	delete [] outVector;
	for (int count = 0; count < 3; count++)
       delete [] arrRotMat[count];
	delete [] arrRotMat;

	return ang;
}

CCartesian SphCoordToDec(CSpherical sph)
{
	CCartesian car;
	
	sph.lat = DegreesToRad(sph.lat);
	sph.lon = DegreesToRad(sph.lon);

	double cos_lat = cos(sph.lat);
    double n = sph.c / sqrt(1. + sph.e12 * sqr(cos_lat));
    double p = (n + sph.hgt) * cos_lat;
    
    car.x = p * cos(sph.lon);
	car.y = p * sin(sph.lon);
	car.z = (n + sph.hgt - sph.e2 * n) * sin(sph.lat);
	
	RDUMP("========================");
	RDUMP(car.x);
	RDUMP(car.y);
	RDUMP(car.z);
	RDUMP(sqrt(sqr(car.x) + sqr(car.y) + sqr(car.z)));
	return car;
	
}


CSpherical DecToSphCoord(CCartesian car)
{
	CSpherical sph;	
	double D = sqrt(sqr(car.x) + sqr(car.y));
	
	if (D == 0.){
		sph.lat = (M_PI / 2.) * (car.z / abs(car.z));
		sph.lon = 0.;
		sph.hgt = car.z * sin(sph.lat) - sph.a * sqrt(1-sph.e2*sqr(sin(sph.lat)));
	}
	else{
		if ((car.y < 0.) and (car.x > 0.)){
			sph.lon = 2.*M_PI - abs(asin(car.y/D));
		}
		else if ((car.y < 0.) and (car.x < 0.)){
			sph.lon = M_PI + abs(asin(car.y/D));
		}
		else if ((car.y > 0.) and (car.x < 0.)){
			sph.lon = M_PI - abs(asin(car.y/D));
		}
		else if ((car.y > 0.) and (car.x > 0.)){
			sph.lon = abs(asin(car.y/D));
		}
		else if ((car.y == 0.) and (car.x > 0.)){
			sph.lon = 0.;
		}
		else if ((car.y == 0.) and (car.x < 0.)){
			sph.lon = M_PI;
		}
		
		if (car.z == 0.){
			sph.lat = 0.;
			sph.hgt = D - sph.a;
		}
		else{
			double r = sqrt(sqr(car.x) + sqr(car.y) + sqr(car.z));
			double c = asin(car.z/r);
			double p = (sph.e2*sph.a)/(2.*r);
			
			double s1, b, s2 = 0.;
			do{
				s1 = s2;
				b = c + s1;
				s2 = asin(p*sin(2.*b)/(sqrt(1.-sph.e2*sqr(sin(b)))));
				sph.lat = b;
			}while (abs(s2-s1) > pow(10, -4));
			sph.hgt = D * cos(sph.lat) + car.z * sin(sph.lat) - sph.a*sqrt(1-sph.e2*sqr(sin(sph.lat)));
		}
	}
	RDUMP("========================");
	sph.lat = RadToDegrees(sph.lat);
	sph.lon = RadToDegrees(sph.lon);
	RDUMP(sph.lat);
	RDUMP(sph.lon);
	RDUMP(sph.hgt);
	return sph;
}
