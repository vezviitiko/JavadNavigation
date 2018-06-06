#include "DataConverter.h"

float dateTojd(int year,int month,int day)
{
	/*
    Convert a date to Julian Day.
    
    Algorithm from 'Practical Astronomy with your Calculator or Spreadsheet', 
        4th ed., Duffet-Smith and Zwart, 2011.
    
    Parameters
    ----------
    year : int
        Year as integer. Years preceding 1 A.D. should be 0 or negative.
        The year before 1 A.D. is 0, 10 B.C. is year -9.
        
    month : int
        Month as integer, Jan = 1, Feb. = 2, etc.
    
    day : float
        Day, may contain fractional part.
    
    Returns
    -------
    jd : float
        Julian Day
        
    Examples
    --------
    Convert 6 a.m., February 17, 1985 to Julian Day
    
    >>> date_to_jd(1985,2,17.25)
    2446113.75
    
    */
    
    int A, B, C, D, yearp, monthp;
    
    if ((month == 1) || (month == 2)){
        yearp = year - 1;
        monthp = month + 12;
	}
    else{
        yearp = year;
        monthp = month;
	}
    // this checks where we are in relation to October 15, 1582, the beginning
    // of the Gregorian calendar.
    
    if ((year < 1582) ||
        (year == 1582 && month < 10) ||
        (year == 1582 && month == 10 && day < 15)){
	        // before start of Gregorian calendar
	        B = 0;
    }
    else{
        // after start of Gregorian calendar
        A = (int) (yearp / 100.);
        B = 2 - A + (int) (A / 4.);
	}
		
    if (yearp < 0){
        C = (int) ((365.25 * yearp) - 0.75);
    }
    else{
        C = (int) (365.25 * yearp);
    }
    D = (int) (30.6001 * (monthp + 1));
    
    float jd = B + C + D + day + 1720994.5;
    
	return jd;
}

float jdTomjd(float jd){
    /*
    Convert Julian Day to Modified Julian Day
    
    Parameters
    ----------
    jd : float
        Julian Day
        
    Returns
    -------
    mjd : float
        Modified Julian Day
    
    */
	return jd - 2400000.5;
}

float mjdTojd(float mjd){
    /*
    Convert Modified Julian Day to Julian Day.
        
    Parameters
    ----------
    mjd : float
        Modified Julian Day
        
    Returns
    -------
    jd : float
        Julian Day
    
        
    */
	return mjd + 2400000.5;
}

float hmsmTodays(int hour=0, int min=0,int sec=0, int micro=0){
    /*
    Convert hours, minutes, seconds, and microseconds to fractional days.
    
    Parameters
    ----------
    hour : int, optional
        Hour number. Defaults to 0.
    
    min : int, optional
        Minute number. Defaults to 0.
    
    sec : int, optional
        Second number. Defaults to 0.
    
    micro : int, optional
        Microsecond number. Defaults to 0.
        
    Returns
    -------
    days : float
        Fractional days.
        
    Examples
    --------
    >>> hmsm_to_days(hour=6)
    0.25
    
    */
    float days;
    
    days = sec + (micro / 1.e6);
    
    days = min + (days / 60.);
    
    days = hour + (days / 60.);
    
	return days / 24.;
}

CDatetime daysTohmsm(float days){
    /*
    Convert fractional days to hours, minutes, seconds, and microseconds.
    Precision beyond microseconds is rounded to the nearest microsecond.
    
    Parameters
    ----------
    days : float
        A fractional number of days. Must be less than 1.
        
    Returns
    -------
    hour : int
        Hour number.
    
    min : int
        Minute number.
    
    sec : int
        Second number.
    
    micro : int
        Microsecond number.
        
    Raises
    ------
    ValueError
        If `days` is >= 1.
        
    Examples
    --------
    >>> days_to_hmsm(0.1)
    (2, 24, 0, 0)
    
    */
    CDatetime datetime;
    
    double hours,hour;
    hours = days * 24.;
    hours = modf(hours, &hour);
    
    double mins, min;
    mins = hours * 60.;
    mins = modf(mins, &min);
    
    double secs, sec;
    secs = mins * 60.;
    secs = modf(secs, &sec);
        
    datetime.hour = int(hour);
    datetime.min = int(min);
    datetime.sec = int(sec);
    datetime.micro = (int) round(secs * 1.e6);
    
	return datetime;
}

float datetimeTojd(CDatetime datetime){
    /*
    Convert a `datetime.datetime` object to Julian Day.
    
    Parameters
    ----------
    date : `datetime.datetime` instance
    
    Returns
    -------
    jd : float
        Julian day.
        
    Examples
    --------
    >>> d = datetime.datetime(1985,2,17,6)  
    >>> d
    datetime.datetime(1985, 2, 17, 6, 0)
    >>> jdutil.datetime_to_jd(d)
    2446113.75
    
    */
    
    float days = datetime.day + hmsmTodays(datetime.hour,datetime.min,datetime.sec,datetime.micro);
    
    float jd = dateTojd(datetime.year, datetime.month, days);
    
	return jd;
}

CDate jdTodate(float jd){
    /*
    Convert Julian Day to date.
    
    Algorithm from 'Practical Astronomy with your Calculator or Spreadsheet', 
        4th ed., Duffet-Smith and Zwart, 2011.
    
    Parameters
    ----------
    jd : float
        Julian Day
        
    Returns
    -------
    year : int
        Year as integer. Years preceding 1 A.D. should be 0 or negative.
        The year before 1 A.D. is 0, 10 B.C. is year -9.
        
    month : int
        Month as integer, Jan = 1, Feb. = 2, etc.
    
    day : float
        Day, may contain fractional part.
        
    Examples
    --------
    Convert Julian Day 2446113.75 to year, month, and day.
    
    >>> jd_to_date(2446113.75)
    (1985, 2, 17.25)
    
    */
    
    jd = jd + 0.5;
    double F, I;
    F = modf(jd, &I);
    I = int(I);
    
    int A = (int) ((I - 1867216.25)/36524.25);
    
    int B;
    if (I > 2299160){
        B = I + 1 + A - (int) (A / 4.);
    }
    else{
        B = I;
    }
    
    int C = B + 1524;
    
    int D = (int) ((C - 122.1) / 365.25);
    
    int E = (int) (365.25 * D);
    
    int G = (int) ((C - E) / 30.6001);
    
    int day = C - E + F - (int) (30.6001 * G);
    
    int month;
    if (G < 13.5){
        month = G - 1;
        }
    else{
        month = G - 13;
    }
    
    int year;
    if (month > 2.5){
        year = D - 4716;
    }
    else{
        year = D - 4715;
    }
    
    CDate date;
    date.year = year;
    date.month = month;
    date.day = day;

	return date;
}

CDatetime jdTodatetime(float jd){
    /*
    Convert a Julian Day to an `jdutil.datetime` object.
    
    Parameters
    ----------
    jd : float
        Julian day.
        
    Returns
    -------
    dt : `jdutil.datetime` object
        `jdutil.datetime` equivalent of Julian day.
    
    Examples
    --------
    >>> jd_to_datetime(2446113.75)
    datetime(1985, 2, 17, 6, 0)
    
    */
    CDatetime datetime;
    CDate date;
    
    date = jdTodate(jd);
    
    datetime.year = date.year;
    datetime.month = date.month;
    datetime.day = date.day;
        
    double day,frac_days;
    
    frac_days = modf(datetime.day, &day);
    
    datetime.day = int(day);
    
    datetime = daysTohmsm(frac_days);
  
	return datetime;
}
