#ifndef _kamaz_DataConverter_h_
#define _kamaz_DataConverter_h_

#include <Core/Core.h>

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

double dateTojd(int year,int month, double day);
double jdTomjd(double jd);
double mjdTojd(double mjd);
double datetimeTojd(CDatetime);
CDate jdTodate(double jd);
CDatetime jdTodatetime(double jd);
double hmsmTodays(int hour, int min,int sec, int micro);
CDatetime daysTohmsm(double days);

#endif
