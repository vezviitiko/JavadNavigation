#ifndef _ParsingJPS_JpsDataClass_h_
#define _ParsingJPS_JpsDataClass_h_

#include <Core/Core.h>

using namespace Upp;
using namespace std;

//Формат IEEE-754
class IEEE{
public:
	typedef IEEE CLASSNAME;
	double value;
	
	IEEE() {}
	IEEE(String binStr, int accur);
private:
	int sign;
	double mantiss;
	double expon;
};

//Главный родительский класс
class JpsData{
public:
	JpsData(String dt, int size, char inStr[]);
	
	String bynStr;			//Бинарная строка данных
	String datType;			//Тип Jps-строки
	
	int dataLength;
	//Здесь в дочерних классах добавляется
	//переменная для данных необходимого типа
};

//Идентификатор файла
class JpsFileId : public JpsData {
public:
	JpsFileId(String readableStr, String dt, int size, char inStr[]);
	String readableStr;									//Строка читаьельная
	String fileTypeId;									//Идентификатор типа файла
	String descriptor;									//Описание
};


////Формат сообщений
//class JpsFormat : public JpsData {
//public:
//	JpsFormat(String readableStr, String dt, char inStr[]);
//	
//	String id;
//	String majorVer;
//	String minorVer;
//	String order;
//	int cs;
//};
//

//Время приёмника
class ReceiverTime : public JpsData {
public:
	ReceiverTime(String dt, int size, char inStr[]);
	long int tod;					//Time of Day	{Число секунд от начала суток}
	int cs;							//Checksum		{Хз что такое. Спросить у Николаев}
};

class ReceiverDate : public JpsData {
public:
	ReceiverDate(String dt, int size, char inStr[]);
	int year;
	int month;
	int day;
	int base;
	int cs;
};

//class EpochTime : public JpsData {
//public:
//	EpochTime(String dt, char inStr[]);
//	int tod;					//Time of Day	{Число секунд от начала суток}
//	int cs;						//Checksum		{Хз что такое. Спросить у Николаев}
//};

//Reference Time to Receiver Time Offset
class RTtoRTO : public JpsData{
public:
	RTtoRTO(String dt, int size, char inStr[]);
	IEEE val;		//8 байт
	IEEE sval;		//8 байт
};

//Derivative Of Receiver Time Offset
class DerOfRtOffset : public JpsData{
public:
	DerOfRtOffset(String dt, int size, char inStr[]);
	IEEE val;		//4 байта
	IEEE sval;		//4 байта
};

//Rough Accuracy of Time Approximation
class RoughAccurOfTimApprox : public JpsData{
public:
	RoughAccurOfTimApprox(String dt, int size, char inStr[]);
	IEEE acc;		//4 байта
};

//GPS Time
class GpsTime : public JpsData{
public:
	GpsTime(String dt, int size, char inStr[]);
	int tow;		//4 байта
	int wn;			//2 байта
};

//GPS to Receiver Time Offset
class GpsToRecTimOff : public JpsData{
public:
	GpsToRecTimOff(String dt, int size, char inStr[]);
	IEEE val;		//8 байт
	IEEE sval;		//8 байт
	String sys = "GPS";
};

//GLONASS Time
class GloTime : public JpsData{
public:
	GloTime(String dt, int size, char inStr[]);
	IEEE tod;		//4 байта
	IEEE dn;		//4 байта
};

//GLONASS Receiver Time Offset ::Наследует от GpsToRecTimOff::
class GloRecTimOff : public GpsToRecTimOff{
public:
	GloRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "GLO";
	}
};

//GALILEO Receiver Time Offset ::Наследует от GpsToRecTimOff::
class GalRecTimOff : public GpsToRecTimOff{
public:
	GalRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "GAL";
	}
};

//SBAS Receiver Time Offset ::Наследует от GpsToRecTimOff::
class SbasRecTimOff : public GpsToRecTimOff{
public:
	SbasRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "SBAS";
	}
};

//QZSS Receiver Time Offset ::Наследует от GpsToRecTimOff::
class QzssRecTimOff : public GpsToRecTimOff{
public:
	QzssRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "QZSS";
	}
};

//BeiDou Receiver Time Offset ::Наследует от GpsToRecTimOff::
class BeiRecTimOff : public GpsToRecTimOff{
public:
	BeiRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "BEI";
	}
};

//IRNSS Receiver Time Offset ::Наследует от GpsToRecTimOff::
class IrnssRecTimOff : public GpsToRecTimOff{
public:
	IrnssRecTimOff(String dt, int size, char inStr[]) : GpsToRecTimOff(dt, size, inStr)
	{
		sys = "IRNSS";
	}
};

struct UtcOffs{
public:
	IEEE a0;		//8 байт			[Constant term of polynomial]
	IEEE a1;		//4 байта			[First order term of polynomial]
	int tot;		//4 байта unsigned	[Reference time of week (s)]
	int wnt;		//2 байта unsigned	[Reference week number]
	int dtls;		//1 байт  signed	[Delta time due leap seconds (s)]
	int dn;			//1 байт  unsigned	['Future' reference day number (1..7)]
	int wnlsf;		//2 байта unsigned	['Future' reference week number]
	int dtlsf;		//1 байт  signed	['Future' delta time due to leap seconds]
};

//GPS UTS Time Parameters
class GpsUtcTimParam : public JpsData{
public:
	GpsUtcTimParam(String dt, int size, char inStr[]);
	UtcOffs utc;	//GPS UTC time offset parameters
};

//SBAS UTC Time Parameters
class SBASUtcTimParam : public JpsData{
public:
	SBASUtcTimParam(String dt, int size, char inStr[]);
	UtcOffs utc;	//GPS UTC time offset parameters
	int utcsi;		//1 байт  signed	[UTC Standard Identifier] ::Reference Guide p. 73, tab 3-5::
	int tow;		//4 байта unsigned	[Reference time of week (s)]
	int wn;			//2 байта unsigned	[Reference week number]
	int flags;		//1 байт  unsigned	[Flags, reserved (always 0)]
};

//GALILEO UTC and GPS Time Parameters
class GalUtcGpsParam : public JpsData{
public:
	GalUtcGpsParam(String dt, int size, char inStr[]);
	IEEE a0g;		//4 байта			[Constant term of time offset (s)]
	IEEE a1g;		//4 байта			[Rate of time offset]
	int t0g;		//4 байта unsigned	[Reference time of week]
	int wn0g;		//2 байта unsigned	[Reference week number]
	int flags;		//4 байта unsigned	[Flags of data availability]
};

//QZSS UTC Time Parameters
class QzssUtcParam : public JpsData{
public:
	QzssUtcParam(String dt, int size, char inStr[]);
	UtcOffs utc;
};

//BeiDou UTC Time Parameters
class BeiDouUtcParam : public JpsData{
public:
	BeiDouUtcParam(String dt, int size, char inStr[]);
	UtcOffs utc;
};

//IRNSS UTC Time Param
class IrnssUtcParam : public JpsData{
public:
	IrnssUtcParam(String dt, int size, char inStr[]);
	UtcOffs utc;
};

//GLONASS UTC and GPS Time Parameters
class GloUtcGpsParam : public JpsData{
public:
	GloUtcGpsParam(String dt, int size, char inStr[]);
	IEEE tauSys;	//8 байт			[Time correction to GLONASS time scale]
	IEEE tauGps;	//4 байта			[tauGps = Tgps - Tglo (s)]
	IEEE B1;		//4 байта			[Coeff for calc of UT1]
	IEEE B2;		//4 байта			[Coeff for calc of UT1]
	int KP;			//1 байт unsigned	[Leap second info]
	int N4;			//1 байт unsigned	[Number of 4-year cycle (1..31)]
	int Dn;			//2 байта signed	[Day num within 4-year period]
};

//Solution Time-Tag
class SolutionTime : public JpsData{
public:
	SolutionTime(String dt, int size, char inStr[]);
	int time;		//4 байта
	int solType;	//1 байт
};

//Cartesian Position
class pos : public JpsData{
public:
	pos(String dt, int size, char inStr[]);
	IEEE x, y, z;	//8 байт
	IEEE pSigma;	//4 байта
	int solType;	//Solution type
};

//Cartesian Velocity
class Vel : public JpsData{
public:
	Vel(String dt, int size, char inStr[]);
	IEEE x,y,z;		//4 байтa
	IEEE vSigma;	//4 байтa
	int solType;	//1 байт unsigned
};

//Cartesian Position and Velocity
class PosVel : public JpsData{
public:
	PosVel(String dt, int size, char inStr[]);
	IEEE x,y,z;		//8 байт
	IEEE pSigma;	//4 байтa
	IEEE vx,vy,vz;	//4 байтa
	IEEE vSigma;	//4 байтa
	int solType;	//1 байт unsigned
};

//Geodetic Position
class GeoPos : public JpsData{
public:
	GeoPos(String dt, int size, char inStr[]);
	IEEE lat;		//8 байт			[Latitude (rad)]
	IEEE lon;		//8 байт			[Longitude (rad]
	IEEE alt;		//8 байт			[Ellipsoidal height (m)]
	IEEE pSigma;	//4 байтa			[Position SEP (m)]
	int solType;	//1 байт unsigned	[Solution type]
};

//Geodetic velocity
class GeoVel : public JpsData{
public:
	GeoVel(String dt, int size, char inStr[]);
	IEEE lat;		//4 байтa			[Northing velocity (m/s)]
	IEEE lon;		//4 байтa			[Easting velocity (m/s)]
	IEEE alt;		//4 байтa			[Height velocity (m/s)]
	IEEE pSigma;	//4 байтa			[Velocity SEP (m/s)]
	int solType;	//1 байт			[Solution type]
};

//Position and Velocity RMS Errors
class Rms : public JpsData{
public:
	Rms(String dt, int size, char inStr[]);
	IEEE hpos;		//4 байтa			[Horizontal position RMS error (m)]
	IEEE vpos;		//4 байтa			[Vertical position RMS error (m)]
	IEEE hvel;		//4 байтa			[Horizontal velocity RMS error (m/s)]
	IEEE vvel;		//4 байтa			[Vertical velocity RMS error (m/s)]
	int solType;	//1 байт			[Solution Type]
};

//Position in Local Plane
class LocalPlanePos : public JpsData{
public:
	LocalPlanePos(String dt, int size, char inStr[]);
	IEEE n;			//8 байт			[Northern coordinate (m)]
	IEEE e;			//8 байт			[Eastern coordinate (m)]
	IEEE u;			//8 байт			[Altitude above local ellipsoid (m)]
	IEEE sep;		//8 байт			[Geoid separation relatively to local ellipsoid (m)]
	IEEE pSigma;	//4 байтa			[Position SEP (m)]
	int solType;	//1 байт			[Solution type]

	int grid;		//1 байт			[Grid source]
					//		0-none
					//		1-predefined grid
					//		2-user defined grid
					//		3-result of localization
					//		4-grid got from external source

	int geoid;		//1 байт			[Geoid source]
					//		0-none
					//		1-predefined geoid
					//		2-user defined geoid
					//		4-geoid got from external source
	int prj;		// 2 байта			[EPSG code of used projection]
};

//Reference Station Position in Local Plane		::Наследует от LocalPlanePos::
class RSLocalPlanePos : public LocalPlanePos{
public:
	RSLocalPlanePos(String dt, int size, char inStr[]);
};

//Dilution of Position
class Dops : public JpsData{
public:
	Dops(String dt, int size, char inStr[]);
	IEEE hdop;		//4 байтa			[Horizontal dilution of precision (HDOP)]
	IEEE vdop;		//4 байтa			[Horizontal dilution of precision (VDOP)]
	IEEE tdop;		//4 байтa			[Time dilution of precision (TDOP)]
	int solType;	//1 байт			[Solution type]
	IEEE edop;		//4 байтa			[East dilution of precision (EDOP)]
};

//Ковариационная матрица
struct CovMatr {
	IEEE xx;		//4 байтa
	IEEE yy;		//4 байтa
	IEEE zz;		//4 байтa
	IEEE tt;		//4 байтa
	IEEE xy;		//4 байтa
	IEEE xz;		//4 байтa
	IEEE xt;		//4 байтa
	IEEE yz;		//4 байтa
	IEEE yt;		//4 байтa
	IEEE zt;		//4 байтa
	int solType;	//1 байт
};

//Position Covariance Matrix
class PosCov : public JpsData{
public:
	PosCov(String dt, int size, char inStr[]);
	CovMatr covMatr;
};

class VelCov : public JpsData{
public:
	VelCov(String dt, int size, char inStr[]);
	CovMatr covMatr;
};

//Baseline
class Baseline : public JpsData{
public:
	Baseline(String dt, int size, char inStr[]);
	IEEE x, y, z;	//8 байт			[Calculated baseline vector coodrinates (m)]
	IEEE sigma;		//4 байтa			[Baseline Spherical Error Probable (SEP) (m)]
	int solType;	//1 байт unsigned	[Solution type]
	int time;		//4 байтa signed	[Receiver time of baseline estinate (s)]
};

//Attitude baselines
class Baselines : public JpsData{
public:
	Baselines(String dt, int size, char inStr[]);
	IEEE b10[3];	//4 байтa			[baseline vector M-S0 (m)]
	IEEE b11[3];	//4 байтa			[baseline vector M-S1 (m)]
	IEEE b12[3];	//4 байтa			[baseline vector M-S2 (m)]
	IEEE rms[3];	//4 байтa			[estimated accuracies for baseline vectors (m)]
	int solType[3];	//4 байтa			[solution types for baseline vectors]
};

//Attitude Full Rotation Matrix
class FullRotationMatr : public JpsData{
public:
	FullRotationMatr(String dt, int size, char inStr[]);
	IEEE q00, q01, q02;	//4 байтa		[Components for the rotation matrix Q]
	IEEE q10, q11, q12;	//4 байтa		[Components for the rotation matrix Q]
	IEEE q20, q21, q22;	//4 байтa		[Components for the rotation matrix Q]
};

//Position Statistics
class PosStat : public JpsData{
public:
	PosStat(String dt, int size, char inStr[]);
	int solType;	//1 байт unsigned	[Solution type]
	int gpsLocked;	//1 байт unsigned	[Number of GPS SVs locked]
	int gloLocked;	//1 байт unsigned	[Number of GLONASS SVs locked]
	int gpsAvail;	//1 байт unsigned	[Number of GPS SVs available for positioning]
	int gloAvail;	//1 байт unsigned	[Number of GLONASS SVs available for positioning]
	int gpsUsed;	//1 байт unsigned	[Number of GPS SVs used for positioning]
	int gloUsed;	//1 байт unsigned	[Number of GLONASS SVs used for positioning]
	int fixProg;	//1 байт unsigned	[Ambiguity fixing process indicator]
};

//Time for Continuous Position Computation
class PosCompTime : public JpsData{
public:
	PosCompTime(String dt, int size, char inStr[]);
	int pt;			//4 байта unsigned	[Continuous position computation time (s)]
};

///////Satellite Measurements////////////////////////////////////
///////Vital information at p. 79 of GRIES Reference Guide///////

//Satellite Indices
class SatIndex : public JpsData{
public:
	SatIndex(String dt, int size, char inStr[]);
	Vector <int> usi;	//1 байт unsigned	[Array of Sat Indices]
};

//Antenna names
class AntName : public JpsData{
public:
	AntName(String dt, int size, char inStr[]);
	Vector <String> name; //1 байт			[Antenna names array]
};

//Glonass Satellite System Numbers
class SatNumbers : public JpsData {
public:
	SatNumbers(String dt, int size, char inStr[]);
	Vector <int> osn;	//1 байт			[Glonass SV orbit slot number]
};

//Satellite Elevations
class SatElevations : public JpsData {
public:
	Vector <int> elevation;
	int nSats;
	SatElevations(String dt, int size, char inStr[], int satNum);
};

//Satellite Azimuths
class SatAzimuth : public JpsData{
public:
	Vector <int> azim;
	SatAzimuth(String dt, int size, char inStr[]);
};

//Pseudo-ranges
class PseudoRange : public JpsData{
public:
	PseudoRange(String dt, int size, char inStr[], String type);
	Vector <IEEE> rp;	//8 байт	[Pseudo-ranges (s)]
};

//Integer Pseudo-ranges
class InPseudoRanges : public JpsData{
public:
	InPseudoRanges(String dt, int size, char inStr[], String type);
	Vector <int> srp;	//4 байт	[PR(s) - A_sys] / K_sys
};

//Relative Pseudo-ranges
class RelPseudoRanges : public JpsData {
public:
	RelPseudoRanges(String dt, int size, char inStr[], String type);
	Vector <IEEE> rpr;	//4 байта	[PR - REF]
};

//////////////////////////////////////
//дописать остальные псевдодальности//
//////////////////////////////////////

//CA/L1 Continuous Tracking Time
class TrackingTimeCA : public JpsData {
public:
	TrackingTimeCA(String dt, int size, char inStr[], String type);
	Vector <int> tt;	//2 байта unsigned	[tracking time (s)]
};

//Satellite Navigation Status
class NavStatus : public JpsData {
public:
	NavStatus(String dt, int size, char inStr[]);
	Vector <int> ns;	//1 байт unsigned	[Navigation Status]
	int solType;		//1 байт unsigned	[Solution type]
};

//Ionospheric Delays
class IonoDelay : public JpsData {
public:
	IonoDelay(String dt, int size, char inStr[]);
	Vector <IEEE> delay;	//4 байта	[Ionospheric delay (s)]
};

//Satellite Range Residuals
class RangeResidual : public JpsData {
public:
	RangeResidual(String dt, int size, char inStr[]);
	Vector <IEEE> res;	//4 байта	[Range residual (m)]
};

//Satellite Velocity Residuals
class ValResid : public JpsData {
public:
	ValResid(String dt, int size, char inStr[]);
	Vector <IEEE> res;	//4 байта	[Velocity residual (m)]
};

///////Almanacs and Ephemerides//////////////////////////////////
///////Vital information at p. 90 of GRIES Reference Guide///////

//Almanac
class Almanac : public JpsData {
public:
	Almanac(String dt, int size, char inStr[]);
	int sv;			//1 байт unsigned	[SV PRN number with the range (1..37)]
	int wna;		//2 байта signed	[Almanac reference week]
	int toa;		//4 байта signed	[Almanac reference time of week (s)]
	int healthA;	//1 байт unsinged	[Health summary (from almanac), {bitfield}]
					//	0..4 - code for health of SV signal components
					//	5..7 - navigation data health indicators
					
	int healthS;	//1 байт unsigned	[Satellite health (p. 25 of subframe 5)]
	int config;		//1 байт unsigned	[Satellite configuration (p. 25 of subframe 4)]
					//	{bitfield}:
					//	0..2 - satellite configuration
					//	   3 - anti-spoofing flag
					//	4..7 - reserved
					
	//======Clock data======
	IEEE afq;		//4 байта	[Polynomial coeff (s/s)]
	IEEE af0;		//4 байта	[Polynomial coeff (s)]
	
	//===Ephemeris data=====
	IEEE rootA;		//4 байта	[Square root of the semi-major axis (m^0.5)]
	IEEE ecc;		//4 байта	[Eccentricity]
	IEEE m0;		//4 байта	[Mean anomaly at reference time (semi-circles)]
	IEEE omega0;	//4 байта	[Longitude of accending node of orbit plane
					//				 at the start of week 'wna' (semi-circles)]
	IEEE argPer;	//4 байта	[Argument of perigee (semi-circles)]
	
	//=====Corrections of orbital parameters=====
	IEEE deli;		//4 байта	[Correction to inclination angle (semi-circles)]
	IEEE omegaDot;	//4 байта	[Rate of right ascension (semi-circles)]
};

//GPS Almanac
class GpsAlmanac : public Almanac {
public:
	GpsAlmanac(String dt, int size, char inStr[]);
};

//Galileo Almanac
class GalAlmanac : public Almanac {
public:
	GalAlmanac(String dt, int size, char inStr[]);
	//Galileo-Specific data
	int iod;		//2 байта signed	[Issue of almanac data]
};

//QZSS Almanac
class QzssAlmanac : public Almanac {
public:
	QzssAlmanac(String dt, int size, char inStr[]);
};

//IRNSS Almanac
class IrnssAlmanac : public Almanac {
public:
	IrnssAlmanac(String dt, int size, char inStr[]);
};

//Glonass Almanac
class GloAlmanac : public JpsData {
public:
	GloAlmanac(String dt, int size, char inStr[]);
	int sv;			//1 байт unsigned	[Satellite slot number within (1..32)]
	int frqNum;		//1 байт signed		[Satellite frequency channel number (-7..24)]
	int dna;		//2 байтa signed	[Day number within 4-year period]
	IEEE tlam;		//4 байта			[Time of the first ascending node passage ond day 'dna' (s)]
	int flags;		//1 байт unsigned	[Satellite flags (bitfield)]
					//	0 - health: 1 - healthy SV; as specified by "Cn";
					//				0 - unhealthy
					//	1 - SVs type: 0 - GLONASS; 1 - GLONASS-M; 2..7 - reserved
	
	//====Clock data====
	IEEE tauN;		//4 байта [Coarse time correction to SV clock with respect to GLONASS system time (s)]
	IEEE tauSys;	//8 байт  [Correction to GLONASS system time with recpect to UTC (s)]
	
	//====Ephemeris data====
	IEEE ecc;		//4 байта			[Eccentricity at reference time 'tlam']
	IEEE lambda;	//4 байта			[Longitude of accending node at r-tim (semi-circles)]
	IEEE argPer;	//4 байта			[Argument of perigee at r-tim (semi-circles)]
	IEEE delT;		//4 байта			[Correction to mean Draconic period at r-tim (s/period)]
	IEEE delTdt;	//4 байта			[Rate of change of draconic period (s/period)]
	int n4;			//1 байт			[Number of 4-year period]
	int navTipe;	//1 байт			[Signal type nav. data was decoded from]
	IEEE gammaN;	//4 байта			[Rate of coarse satellite clock correction to GLO time scale (s/s)]
};

//SBAS Almanac
class SbasAlmanac : public JpsData{
public:
	SbasAlmanac(String dt, int size, char inStr[]);
	int waasPrn;	//1 байт unsigned	[SBAS SV PRN number (120..142)]
	int gpsPrn;		//1 байт unsigned	[GPS SV PRN associated with SBAS SV]
	int id;			//1 байт unsigned	[Data Id]
	int healthS;	//1 байт unsigned	[Satellite health]
					//	0 - 0-Ranging on, 1-off
					//	1 - 0-Corrections on, 1-off
					//	2 - 0-Broadcast Integrity on, 1-off
					//	3 - reserved
					//	4..7 - NULL
					
	int tod;			//4 байта unsigned	[Time of day (s)]
	IEEE xg, yg, zg;	//8 байт			[ECFF coordinates (m)]
	IEEE vxg, vyg, vzg;	//4 байта			[ECFF velocity (m/s)]
	int tow;			//4 байта unsigned	[Time of GPS week almanac was received at (s)]
	int wn;				//2 байта unsigned	[GPS week this almanac was received at]
};

//Эфемериды//
//GPS ephemeris required data
class GpsEphReqData{
public:
	GpsEphReqData(String dt, int size, char inStr[]);
	int sv;			//1 байт unsigned		[SV PRN number (1..37)]
	int tow;		//4 байта unsigned		[Time of week (s)]
	int flags;		//1 байт unsigned		[Flags (See GPS ICD For details)]
	
	//====Clock data (Subframe 1)====
	int iodc;		//2 байта signed		[Issue of data, clock]
	int toc;		//4 байта signed		[Clock data reference time (s)]
	int ura;		//1 байт signed			[User range accuracy]
	int healthS;	//1 байт unsigned		[Satellite health]
	int wn;			//1 байт signed			[Week number]
	IEEE tgd;		//4 байта				[Estimated group delay differential (s)]
	IEEE af2;		//4 байта				[Polynomial coefficient (s / s ^ 2)]
	IEEE af1;		//4 байта				[Polynomial coefficient (s / s)]
	IEEE af0;		//4 байта				[Polynomial coefficient (s)]
	
	//====Ephemeris data (Subframes 2 and 3)====
	int toe;		//4 байта signed		[Ephemeris reference time (s)]
	int iode;		//2 байта signed		[Issue of data, ephemeris]
	//----Keplerian orbital parameters----
	IEEE rootA;		//8 байт				[Square root of the semi-major axis (m^0.5)]
	IEEE ecc;		//8 байт				[Eccentricity]
	IEEE m0;		//8 байт				[Mean anomaly at reference time (wn, toe) (semi-circles)]
	IEEE omega0;	//8 байт				[Longitude of ascending node an start of week (semi-circles)]
	IEEE inc0;		//8 байт				[Inclination angle at reference time]
	IEEE argPer;	//8 байт				[Argument of perigee (semi-circles)]
	//----Correction to orbital parameters----
	IEEE deln;		//4 байта				[Mean motion difference from computed value (semi-circles/s)]
	IEEE omegaDot;	//4 байта				[Rate of right ascension (semi-circles/s)]
	IEEE incDot;	//4 байта				[Rate of inclination (semi-circles/s)]
	IEEE crc;		//4 байта				[Amplitude of the cosine harmonic correction term to the orbit radius (m)]
	IEEE crs;		//4 байта				[Amplitude of the cosine harmonic correction term to the orbit radius (m)]
	IEEE cuc;		//4 байта				[Amplitude of the cosine harmonic correction term to the argument of latitude (m)]]
	IEEE cus;		//4 байта				[Amplitude of the cosine harmonic correction term to the argument of latitude (m)]]
	IEEE cic;		//4 байта				[Amplitude of the cosine harmonic correction term to the angle of inclination (m)]]
	IEEE cis;		//4 байта				[Amplitude of the cosine harmonic correction term to the angle of inclination (m)]]
};

struct GpsEphCnavIsc{
	IEEE fIscL1CA;	//4 байта				[Inter-signal correction between L1P(Y) and C/A]
	IEEE fIscL2C;	//4 байта				[Inter-signal correction between L1P(Y) and L2C]
	IEEE fIscL5I5;	//4 байта				[Inter-signal correction between L1P(Y) and L5I5]
	IEEE fIscL5Q5;	//4 байта				[Inter-signal correction between L1P(Y) and L5Q5]
};

struct GpsEphCnav2Isc{
	IEEE fIscL1CP;	//4 байта				[Inter-signal correction between L1P(Y) and L1CP]
	IEEE fIscL1CD;	//4 байта				[Inter-signal correction between L1P(Y) and L1CD]
};

//GPS optional data
class GpsEphOptData {
public:
	GpsEphOptData(String dt, int size, char inStr[]);
	int cNavType;					//1 байт	[]
	int lTope;						//4 байт	[]
	int lTopc;						//4 байт	[]
	IEEE dADot;						//8 байт	[]
	IEEE fDelnDot;					//4 байт	[]
	int cURAoe;						//1 байт	[]
	int cURAoc;						//1 байт	[]
	int cURAoc1;					//1 байт	[]
	int cURAoc2;					//1 байт	[]
	GpsEphCnavIsc gpsEphCnavIsc;
	GpsEphCnav2Isc gpsEphCnav2Isc;
};

//GPS Ephemeris
class GpsEphemeris : public JpsData {
	GpsEphemeris (String dt, int size, char inStr[]);
	GpsEphReqData req;				//[Required data]
	GpsEphOptData opt;				//[Optional data]
};

//GALILEO Ephemeris
class GalEphemeris : public JpsData {
public:
	GalEphemeris (String dt, int size, char inStr[]);
	GpsEphReqData req;				//[GPS required data, 'rec.sv' within (1..30)]
	
	//----Galileo-specific data bloc----
	IEEE bgdE1E5a;		//4 байта			[broadcast group delay E1 - E5a]
	IEEE bgdE1E5b;		//4 байта			[broadcast group delay E1 - E5b]
	IEEE ai0;			//4 байта			[Effiective ionisotion level 1-st order parameter]
	IEEE ai1;			//4 байта			[Effiective ionisotion level 2-st order parameter]
	IEEE ai2;			//4 байта			[Effiective ionisotion level 3-st order parameter]
	int sfi;			//1 байт unsigned	[Ionospheric disturbance flags]
	int navType;		//1 байт ubsigned	[Type of navigation data
						//						0 - GALILEO E1B (INAV)
						//						1 - GALILEO	E5A (FNAV)
						//						3 - GIOVE E1B
						//						4 - GIOVE E5A
};
//Остальные эфемериды пропишем потом

//GLONASS Ephemeris
class GloEphemeris : public JpsData {
public:
	GloEphemeris (String dt, int size, char inStr[]);
	int sv;				//1 байт unsigned
	int frqNum;			//1 байт signed
	int dne;			//2 байта sigend
	int tk;				//4 байта signed
	int tb;				//4 байта signed
	int health;			//1 байт unsigned
	//====Ephemeris data====
	int age;			//1 байт unsigned
	int flags;			//1 байт unsigned
	IEEE r[3];			//8 байт
	IEEE v[3];			//4 байта
	IEEE w[3];			//4 байта
	//====Clock data====
	IEEE tauSys;		//8 байт
	IEEE tau;			//4 байта
	IEEE gamma;			//4 байта
	//====GLONASS-M data====
	IEEE fDelTauN;		//4 байта
	int nFt;			//1 байт unsigned
	int nNt;			//1 байт unsigned
	int flags;			//2 байтф unsigned
	//----Optional data block----
	int navType;		//1 байт unsigned
	IEEE beta;			//4 байта
	IEEE tuSysDot;		//4 байта
	int ec;				//1 байт unsigned
	int ee;				//1 байт unsigned
	int fc;				//1 байт signed
	int fe;				//1 байт signed
	int  reserv;		//2 байта unsigned
}

#endif