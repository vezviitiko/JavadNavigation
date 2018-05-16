#include "model.h"

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
		
	LOG("---- матрица поворота ----");
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
			RDUMP(arrRotMat[i][j]);
	}
	
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
	   
	RDUMP(ang.x);
	RDUMP(ang.y);
	RDUMP(ang.z);
	return ang;
}
