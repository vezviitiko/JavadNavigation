#include "kamaz.h"

CONSOLE_APP_MAIN
{
	LOG("Hello world");
	/*
	 НАЧАЛЬНЫЕ ВХОДНЫЕ ДАННЫЕ ИЗ НАВИГАЦИОННОГО ФАЙЛА
	 ДЛЯ ТЕСТИРОВАНИЯ

	G01 2018 04 16 00 00 00-0.409865751862D-04-0.261479726760D-11 0.000000000000D+00
     0.830000000000D+02 0.579375000000D+02 0.479127100424D-08 0.136321882824D+01
     0.319071114063D-05 0.760033272672D-02 0.566244125366D-05 0.515366792870D+04
     0.864000000000D+05-0.540167093277D-07-0.199576327491D+01 0.203028321266D-06
     0.970469805449D+00 0.276437500000D+03 0.612966614851D+00-0.838856370306D-08
     0.313227332890D-09 0.100000000000D+01 0.199700000000D+04 0.000000000000D+00
     0.280000000000D+01 0.000000000000D+00 0.558793544769D-08 0.830000000000D+02
     0.863700000000D+05

	======================================================================================

	НАЧАЛЬНЫЕ ВХОДНЫЕ ДАННЫЕ ИЗ АЛЬМАНАХА
	ДЛЯ ТЕСТИРОВАНИЯ
	02 01 2018    1806
 	7   5  1  01 01 2018  0.168096250E+05  0.000000000E+00  0.000000000E+00  0.228881836E-04
	0.2881289E+00  0.8143425E-02 -0.6967163E+00  0.1114845E-02 -0.2656043E+04  0.3662109E-03
	
	*/
	
	// формирование начальных значений
	/*CKeplerian kep; // Создание объекта класса
	*/
	CCartesian car;
	CAlmanac   alm;
	
	CSpherical sph;
	/*
	
	// ФОРМИРОВАНИЕ ЗНАЧЕНИЕ ИЗ НАВ.ФАЙЛА
	kep.e = 0.760033272672*pow(10,-2);				// ЭКСЦЕНТРИСИТЕТ
	kep.a = sqr(0.515366792870*pow(10,4));			// большая полуось = м
	kep.i = 0.970469805449*pow(10,0);				// наклонение (рад)
	kep.omBig = -0.199576327491*pow(10,1);				// долгота восходящего узла
	kep.omMin = 0.612966614851*pow(10,0);				// аргумент перицентра
	
	// вычисление средней аномалии
	double dln = 0.479127100424*pow(10,-8);
	double n0 = sqrt(398600.4415/pow(kep.a,3));
	double n = n0 + dln;;
	double tk = 0.863700000000*pow(10,5);
	double M0 = 0.136321882824*10;
	kep.M = M0 + n * tk;								// средняя аномалия
	
	// формирование декартовых координат из навигационного файла
	car = KepToDec(kep);
		
	// ФОРМИРОВАНИЕ ЗНАЧЕНИЕ ИЗ АЛЬМАНАХА
	alm.yearAlm = 2018;
	alm.monthAlm = 1;
	alm.dayAlm = 2;
	
	alm.day = 1;
	alm.month = 1;
	alm.year = 2018;
	
	alm.Tlambda = 0.168096250*pow(10,5);
	alm.lambda = 0.2881289;
	alm.di = 0.8143425*pow(10,-2);
	alm.w = -0.6967163;
	alm.e = 0.1114845*pow(10,-2);
	alm.dT = -0.2656043*pow(10,4);
	alm.dTT = 0.3662109*pow(10,-3);
		
	// формирование декартовых координат по Альманаху
	car = ModelAlmDec(alm);
	*/
	// формирование координат относитьльно Спутниковой тарелки
	double lat = 55.9121311;
	double lon = 37.8090947;
	double hgt = 160.;
	RDUMP("++++++++++++++++++++");
	RDUMP(lat);
	RDUMP(lon);
	RDUMP(hgt);
	car = SphCoordToDec(CSpherical(lat, lon , hgt));

	sph = DecToSphCoord(car);
	
	/*PostgreSQLTest dlg;
	if(dlg.OpenDB())
    {
		LOG("start DB");
    }*/
    /*
    CDatetime datetime;
    datetime.year = 2018;
    datetime.month = 8;
    datetime.day = 1;
    datetime.hour = 0;
    datetime.min = 0;
    datetime.sec = 0;
    
    RDUMP(datetimeTojd(datetime));
    
    datetime.year = 2018;
    datetime.month = 8;
    datetime.day = 1;
    datetime.hour = 2;
    datetime.min = 30;
    datetime.sec = 0;
    
    RDUMP(datetimeTojd(datetime));
    
    datetime.year = 2018;
    datetime.month = 8;
    datetime.day = 1;
    datetime.hour = 10;
    datetime.min = 0;
    datetime.sec = 0;
    
    RDUMP(datetimeTojd(datetime));
    */
}
