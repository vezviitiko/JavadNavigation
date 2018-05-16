#ifndef _model_model_h
#define _model_model_h
#include <iostream>
#include <string>
#include <Core/Core.h>

#include "CoordSys.h"

using namespace Upp;

const double PI = 3.1415926535897932384626433832795;

float dateTojd(int year,int month, int day);
float jdTomjd(float jd);
float mjdTojd(float mjd);
float datetimeTojd(CDatetime);
CDate jdTodate(float jd);
CDatetime jdTodatetime(float jd);
float hmsmTodays(int hour, int min,int sec, int micro);
CDatetime daysTohmsm(float days);

#endif



