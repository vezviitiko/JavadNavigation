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

float dateTojd(int year,int month, int day);
float jdTomjd(float jd);
float mjdTojd(float mjd);
float datetimeTojd(CDatetime);
CDate jdTodate(float jd);
CDatetime jdTodatetime(float jd);
float hmsmTodays(int hour, int min,int sec, int micro);
CDatetime daysTohmsm(float days);

#endif
