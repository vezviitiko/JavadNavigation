#include "model.h"






CONSOLE_APP_MAIN
{
	LOG("Hello world");
	/*
	 NOM_KA = 24
	 CHAN = 2
	 HEALTH = 1
	 E = 0.000935
	 N_DAY = 837
	 I_CORR = 0.014292
	 LAMBDA = 0.763962
	 T_LAMBDA = 28240.125000
	 OMEGA = 0.301666
	 DT_DRAC = -2655.708984
	 AF1 = -0.000122
	 AF0 = 0.000164
	 CHECK_ = 0
	 MJD = 58224.104433
	*/
	/*
	G01 2018 04 16 00 00 00-0.409865751862D-04-0.261479726760D-11 0.000000000000D+00
     0.830000000000D+02 0.579375000000D+02 0.479127100424D-08 0.136321882824D+01
     0.319071114063D-05 0.760033272672D-02 0.566244125366D-05 0.515366792870D+04
     0.864000000000D+05-0.540167093277D-07-0.199576327491D+01 0.203028321266D-06
     0.970469805449D+00 0.276437500000D+03 0.612966614851D+00-0.838856370306D-08
     0.313227332890D-09 0.100000000000D+01 0.199700000000D+04 0.000000000000D+00
     0.280000000000D+01 0.000000000000D+00 0.558793544769D-08 0.830000000000D+02
     0.863700000000D+05
	*/
	
	
	// способ один
	double e = 0.760033272672*pow(10,-2);				// ЭКСЦЕНТРИСИТЕТ
	double a = sqr(0.515366792870*pow(10,4));			// большая полуось = м
	double dln = 0.479127100424*pow(10,-8);
	double n0 = sqrt(398600.4415/pow(a,3));
	double n = n0 + dln;;
	double tk = 0.863700000000*pow(10,5);
	double M0 = 0.136321882824*10;						// средняя аномалия
	double M = M0 + n * tk;
	double teta = 0.970469805449*pow(10,0);				// наклонение (рад)
	double fi = -0.199576327491*pow(10,1);			// долгота восходящего узла
	double psi = 0.612966614851*pow(10,0);				// аргумент перицентра
	
	RDUMP(a);
	RDUMP(e);
	RDUMP(n);
	RDUMP(M);
	double E0,E1,E2;
	// найдем Е - эксцентрическую аномалия
	// M = E - e*sin(M);
	E0 = M + e*sin(M);
	E1 = M + e*sin(E0);
	E2 = M + e*sin(E1);
	RDUMP(E0);
	RDUMP(E1);
	RDUMP(E2);

	// найдем V - истинная аномалия
	// tg(V/2) = sqrt((1+e)/(1-e))tg(E/2)
	double at2_sin = (sqrt(1 - sqr(e))/(1 - e*cos(E2)));
	double at2_cos = ((cos(E2)- e)/(1 - e*cos(E2)));
    double V = atan2(at2_sin, at2_cos);
    
	//V = atan(2*(((sqrt(1-pow(e,2)))*sin(E2))/(1-e*cos(E2))));
	RDUMP(V);
	
	
	// находим x
	double x = a*cos(E2);
	RDUMP(x);
	
	// находим y ------
	// находим малая полуось
	double b = a*sqrt(1-pow(e,2));
	RDUMP(b);
	// находим половину расстояния до фокуса
	double c = sqrt(pow(a,2)-pow(b,2));
	RDUMP(c);
	// находим разницу между x и расстоянием до фокуса
	double ras = x-c;
	RDUMP(ras);
	
	double y = ras*sin(V);
	RDUMP(y);
	
	// проверка

	double z = sqrt(pow(x,2)+pow(y,2));
	RDUMP(z);
	
	z = 0;
	// получение вектора x, y ,z
	//	    x
	//N = ( y )
	//      z
	
	int N = 3;
	
	double aMatrix[3] = {x,y,z};
	
	/*
	A[1] = x;
	A[2] = y;
	A[3] = z;
	*/
	
	printf("\naMatrix\n");
	for (int i = 0; i < N; i++)
	{
	   	printf("%f ", aMatrix[i]);
	    printf("\n");
	}
	
	double B[3][3];
	printf("fi = %f ", fi);
	printf("psi = %f ", teta);
	printf("teta = %f ", teta);
	B[1][1] = cos(fi)*cos(psi)-sin(fi)*sin(psi)*cos(teta);
	printf("B[1][1] = %f ", B[1][1]);
	B[2][1] = -sin(fi)*cos(psi)-cos(fi)*sin(psi)*cos(teta);
	B[3][1] = sin(psi)*sin(teta);
	B[1][2] = cos(fi)*sin(psi)+sin(fi)*cos(psi)*cos(teta);
	B[2][2] = -sin(fi)*sin(psi)+cos(fi)*cos(psi)*cos(teta);
	B[3][2] = -cos(psi)*sin(teta);
	B[1][3] = sin(fi)*sin(teta);
	B[2][3] = sin(fi)*sin(teta);
	B[3][3] = cos(teta);
	
	printf("\nbMatrix\n");
	for (int i = 0; i < N; i++)
	{
	    for (int j = 0; j < N; j++)
	        printf("%f ", B[i][j]);
	    printf("\n");
	}
	
	for(int i = 0; i < N; i++)
	    for(int j = 0; j < N; j++)
	    {
	        B[i][j] = aMatrix[i] * B[i][j];
	    }
	    
	printf("\nthe result\n");
	for (int i = 0; i < N; i++)
	{
	    for (int j = 0; j < N; j++)
	        printf("%f ", B[i][j]);
	    printf("\n");
	}
		
}
