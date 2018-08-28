#include "JpsDataClass.h"
#include "ParsingJPS.h"

//В этом файле собраны конструкторы читалки
//для разных типов строк и соответствующих им типов данных

JpsData::JpsData(String dt, int size, char inStr[])
{
	datType = dt;
	string stdStr = "";
	for (int i = 0; i < size; i++){
		stdStr += inStr[i];
	}
	bynStr = GetBitsStr(stdStr);
	
	String valStr = "";
	String headerValStr = "";
	int count = 0;
	int i = 0;
	
	do{
		i++;
		if (count > 1){
			valStr += bynStr[i];
			if (valStr.GetLength() > 8){
				headerValStr += char(BinaryToDecimal(valStr, "unsigned"));
				valStr = "";
			}
		}
		if (bynStr[i] == 0) {count++;}
	}while (count < 5);
	
	String hexStr = "";
	int len = 0;
	for (int i = 18; i < (18 + 9 * 3); i++)
	{
		if (bynStr[i] != 0){
			hexStr += bynStr[i];
		}else{
			len++;
		}
	}
	hexStr = BinToHex(hexStr, len);
	double doubVal = HexToDec(hexStr);
	dataLength = int(doubVal);
}

JpsFileId::JpsFileId(String readableStr, String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	
}

ReceiverTime::ReceiverTime(String dt, int size, char inStr[]) : JpsData (dt, size, inStr)
{
	String val[4];
	String secStr = "";
	for (int i = 0; i < 4; i++){
		int count = 0;
		do{
			val[i] += bynStr[46 + (9 * i) + count];
			count++;
		}while (bynStr[46 + (9 * i) + count] != 0);
	}
	for (int i = 0; i < 4; i++){
		secStr += val[3 - i];
	}
	tod = BinaryToDecimal(secStr, "unsigned");
}

EpochTime::EpochTime(String dt, int size, char inStr[]) : JpsData (dt, size, inStr)
{
	String valStr = BinaryStrGen(bynStr, 4, 46);
	tod = BinaryToDecimal(valStr, "unsigned");
}

ReceiverDate::ReceiverDate(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String val[2];
	String valStr = "";
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		do{
			val[0] += bynStr[46 + (9 * i) + count];
			count++;
		}while (bynStr[46 + (9 * i) + count] != 0);
		if (i == 0){
			count++;
			do{
				val[1] += bynStr[46 + (9 * i) + count];
				count++;
			}while (bynStr[46 + (9 * i) + count] != 0);
			year = BinaryToDecimal(val[1] + val[0], "unsigned");
		}
		if (i == 2) {month = BinaryToDecimal(val[0], "unsigned");}
		if (i == 3) {day   = BinaryToDecimal(val[0], "unsigned");}
		val[0] = "";
		
		LOG("Reading Receiver Date");
	}
}

SatElevations::SatElevations(String dt, int size, char inStr[], int satNum) : JpsData (dt, size, inStr)
{
	nSats = satNum;
	String test = "";
	for (int i = 0; i < 4; i++)
	{
		test += inStr[i];
	}
	if (test != "ELTA")
	{
		//RDUMP(dataLength);
	}
}

RTtoRTO::RTtoRTO(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String ieeeStr = "";
	String valStr[8];
	for (int i = 0; i < 8; i++){
		int count = 0;
		valStr[i] = "";
		do{
			valStr[i] += bynStr[46 + (9 * i) + count];
			count++;
		}while(bynStr[46 + (9 * i) + count] != 0);
	}
	for (int i = 0; i < 8; i++){
		ieeeStr += valStr[7 - i];
	}
	val = IEEE(ieeeStr, 8);
	
	for (int i = 0; i < 8; i++){
		int count = 0;
		valStr[i] = "";
		do{
			valStr[i] += bynStr[118 + (9 * i) + count];
			count++;
		}while (bynStr[118 + (9 * i) + count] != 0);
	}
	ieeeStr = "";
	for (int i = 0; i < 8; i++){
		ieeeStr += valStr[7 - i];
	}
	sval = IEEE(ieeeStr, 8);
}

GloTime::GloTime(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String ieeeStr;
	
	ieeeStr = BinaryStrGen(bynStr, 4, 46);
	tod = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 82);
	dn = IEEE(ieeeStr, 4);
}

DerOfRtOffset::DerOfRtOffset(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String ieeeStr;

	ieeeStr = BinaryStrGen(bynStr, 4, 46);
	val = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 82);
	sval = IEEE(ieeeStr, 4);
}

RoughAccurOfTimApprox::RoughAccurOfTimApprox(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String ieeeStr;
	
	ieeeStr = BinaryStrGen(bynStr, 4, 46);
	acc = IEEE(ieeeStr, 4);
}

GpsTime::GpsTime(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String ieeeStr;
	
	ieeeStr = BinaryStrGen(bynStr, 4, 46);
	tow = BinaryToDecimal(ieeeStr, "unsigned");
	
	ieeeStr = BinaryStrGen(bynStr, 2, 64);
	wn = BinaryToDecimal(ieeeStr, "unsigned");
}

CNR::CNR(String dt, int size, char inStr[], String type) : JpsData (dt, size, inStr)
{
	cnrType = type;
	String valStr;
	for (int i = 0; i < dataLength; i++){
		valStr = BinaryStrGen(bynStr, 1, (46 + i * 9));
		cnr.Add(int(BinaryToDecimal(valStr, "unsigned")));
	}
}

CNR_4::CNR_4(String dt, int size, char inStr[], String type) : JpsData (dt, size, inStr)
{
	cnrType = type;
	String valStr;
	if (dataLength < 100){
		for (int i = 0; i < dataLength; i++){
			valStr = BinaryStrGen(bynStr, 1, (46 + i * 9));
			cnrX4.Add(int(BinaryToDecimal(valStr, "unsigned")));
		}
	}
}

Flags::Flags(String dt, int size, char inStr[], String type) : JpsData (dt, size, inStr)
{
	flagType = type;
	String valStr;
	for (int i = 0; i < dataLength; i++)
	{
		valStr = BinaryStrGen(bynStr, 2, (46 + i * 9 * 2));
		flags.Add(int(BinaryToDecimal(valStr, "unsigned")));
	}
}

QAmp::QAmp(String dt, int size, char inStr[], String type) : JpsData (dt, size, inStr)
{
	thisType = type;
	//RDUMP(dataLength);
}

TrackingTimeCA::TrackingTimeCA(String dt, int size, char inStr[], String type) : JpsData (dt, size, inStr)
{
	TimeType = type;
	String valStr;
	if (dataLength < 100){
		for (int i = 0; i < dataLength; i++){
			valStr = BinaryStrGen(bynStr, 2, (46 + i * 2 * 9));
			tt.Add(int(BinaryToDecimal(valStr, "unsigned")));
		}
	}
}


//Проверить у Санька на потери памяти
//Странно, что у него на ADD не руается
NavStatus::NavStatus(String dt, int size, char inStr[]) : JpsData (dt, size, inStr){
	String valStr;
	
	if (dataLength < 100){
		for (int i = 0; i < dataLength; i++){
			valStr = BinaryStrGen(bynStr, 1, (46 + i * 9));
			ns.Add(BinaryToDecimal(valStr, "unsigned"));
		}
	
		valStr = BinaryStrGen(bynStr, 1, (46 + dataLength * 9));
		solType = BinaryToDecimal(valStr, "unsigned");
	}
}

GloAlmanac::GloAlmanac(String dt, int size, char inStr[]) : JpsData (dt, size, inStr){
	String valStr;
	String ieeeStr;
	
	valStr = BinaryStrGen(bynStr, 1, 46);
	sv = BinaryToDecimal(valStr, "unsigned");

	valStr = BinaryStrGen(bynStr, 1, 55);
	frqNum = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 2, 64);
	dna = BinaryToDecimal(valStr, "signed");
	
	ieeeStr = BinaryStrGen(bynStr, 4, 82);
	tlam = IEEE(ieeeStr, 4);
	
	valStr = BinaryStrGen(bynStr, 1, 118);
	flags = BinaryToDecimal(valStr, "unsigned");
	
	ieeeStr = BinaryStrGen(bynStr, 4, 127);
	tauN = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 163);
	tauSys = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 199);
	ecc = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 235);
	lambda = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 271);
	argPer = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 307);
	delT = IEEE(ieeeStr, 4);

	//Странное значение!
	ieeeStr = BinaryStrGen(bynStr, 4, 343);
	delTdt = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 379);
	deli = IEEE(ieeeStr, 4);
	
	
	//Ещё странное занчение!
	valStr = BinaryStrGen(bynStr, 1, 415);
	n4 = BinaryToDecimal(valStr, "unsigned");
	
	//Ещё странное значение
	valStr = BinaryStrGen(bynStr, 1, 424);
	navType = BinaryToDecimal(valStr, "unsigned");
	//RDUMP(valStr);
	
	//Ещё странное значение
	ieeeStr = BinaryStrGen(bynStr, 4, 433);
	gammaN = IEEE(ieeeStr, 4);
}


GloEphemeris::GloEphemeris(String dt, int size, char inStr[]) : JpsData (dt, size, inStr){
	String valStr = BinaryStrGen(bynStr, 1, 46);
	sv = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 55);
	frqNum = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 2, 64);
	dne = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 4, 82);
	tk = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 4, 118);
	tb = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 1, 154);
	health = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 163);
	age = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 172);
	//Флаги написать читалку по ИКД ГЛОНАСС
	flags = BinaryToDecimal(valStr, "unsigned");
	
	String ieeeStr;
	for (int i = 0; i < 3; i++){
		ieeeStr = BinaryStrGen(bynStr, 8, (181 + 9 * 8 * i));
		r[i] = IEEE(ieeeStr, 8);
	}
	for (int i = 0; i < 3; i++){
		ieeeStr = BinaryStrGen(bynStr, 4, (397 + 9 * 4 * i));
		v[i] = IEEE(ieeeStr, 4);
	}
	
	for (int i = 0; i < 3; i++){
		ieeeStr = BinaryStrGen(bynStr, 4, (505 + 9 * 4 * i));
		w[i] = IEEE(ieeeStr, 4);
	}
	
	ieeeStr = BinaryStrGen(bynStr, 8, 613);
	tauSys = IEEE(ieeeStr, 8);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 685);
	tau = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 721);
	gamma = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 757);
	fDelTauN = IEEE(ieeeStr, 4);
	
	valStr = BinaryStrGen(bynStr, 1, 793);
	nFt = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 802);
	nN4 = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 2, 811);
	//Флаги написать читалку по ИКД ГЛОНАСС
	flags2 = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 829);
	navType = BinaryToDecimal(valStr, "unsigned");
	
	ieeeStr = BinaryStrGen(bynStr, 4, 838);
	beta = IEEE(ieeeStr, 4);
	
	ieeeStr = BinaryStrGen(bynStr, 4, 874);
	tauSysDot = IEEE(ieeeStr, 4);

	valStr = BinaryStrGen(bynStr, 1, 910);
	ec = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 919);
	ee = BinaryToDecimal(valStr, "unsigned");
	
	valStr = BinaryStrGen(bynStr, 1, 928);
	fc = BinaryToDecimal(valStr, "signed");
	
	valStr = BinaryStrGen(bynStr, 1, 937);
	fe = BinaryToDecimal(valStr, "signed");

	valStr = BinaryStrGen(bynStr, 2, 946);
	reserv = BinaryToDecimal(valStr, "unsigned");
}

GpsUtcTimParam::GpsUtcTimParam(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	// UtcOffs
	vel = BinaryStrGen(bynStr, 8, 46);
	utc.a0 = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	utc.a1 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	utc.tot = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 190);
	utc.wnt = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 208);
	utc.dtls = BinaryToDecimal(vel, "signed");
	
	vel = BinaryStrGen(bynStr, 1, 217);
	utc.dn = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 226);
	utc.wnlsf = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 244);
	utc.dtlsf = BinaryToDecimal(vel, "signed");
}

SBASUtcTimParam::SBASUtcTimParam(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	// UtcOffs
	vel = BinaryStrGen(bynStr, 8, 46);
	utc.a0 = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	utc.a1 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	utc.tot = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 190);
	utc.wnt = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 208);
	utc.dtls = BinaryToDecimal(vel, "signed");
	
	vel = BinaryStrGen(bynStr, 1, 217);
	utc.dn = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 226);
	utc.wnlsf = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 244);
	utc.dtlsf = BinaryToDecimal(vel, "signed");
	
	// additional
	vel = BinaryStrGen(bynStr, 1, 253);
	utcsi = BinaryToDecimal(vel, "signed");
	
	vel = BinaryStrGen(bynStr, 4, 262);
	tow = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 298);
	wn = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 316);
	flags = BinaryToDecimal(vel, "unsigned");
}

GalUtcGpsParam::GalUtcGpsParam(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	// UtcOffs
	vel = BinaryStrGen(bynStr, 8, 46);
	utc.a0 = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	utc.a1 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	utc.tot = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 190);
	utc.wnt = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 208);
	utc.dtls = BinaryToDecimal(vel, "signed");
	
	vel = BinaryStrGen(bynStr, 1, 217);
	utc.dn = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 226);
	utc.wnlsf = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 244);
	utc.dtlsf = BinaryToDecimal(vel, "signed");
	
	// additional
	vel = BinaryStrGen(bynStr, 4, 253);
	a0g = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 289);
	a1g = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 325);
	t0g = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 361);
	wn0g = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 4, 379);
	flags = BinaryToDecimal(vel, "unsigned");
}

GloUtcGpsParam::GloUtcGpsParam(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 8, 46);
	tauSys = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	tauGps = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	B1 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 190);
	B2 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 226);
	KP = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 235);
	N4 = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 244);
	Dn = BinaryToDecimal(vel, "signed");
}

SolutionTime::SolutionTime(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	time = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 82);
	solType = BinaryToDecimal(vel, "unsigned");
}

Pos::Pos(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;

	vel = BinaryStrGen(bynStr, 8, 46);
	x = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 8, 118);
	y = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 8, 190);
	z = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 4, 262);
	pSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 298);
	solType = BinaryToDecimal(vel, "unsigned");
}

Vel::Vel(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	x = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	y = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	z = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	vSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 190);
	solType = BinaryToDecimal(vel, "unsigned");
}


PosVel::PosVel(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;

	vel = BinaryStrGen(bynStr, 8, 46);
	x = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 8, 118);
	y = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 8, 190);
	z = IEEE(vel, 8);

	vel = BinaryStrGen(bynStr, 4, 262);
	pSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 298);
	vx = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 334);
	vy = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 370);
	vz = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 406);
	vSigma = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 1, 442);
	solType = BinaryToDecimal(vel, "unsigned");
}

GeoPos::GeoPos(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 8, 46);
	lat = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 8, 118);
	lon = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 8, 190);
	alt = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 262);
	pSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 190);
	solType = BinaryToDecimal(vel, "unsigned");
}

GeoVel::GeoVel(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	lat = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	lon = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	alt = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	pSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 190);
	solType = BinaryToDecimal(vel, "unsigned");
}

Rms::Rms(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	hpos = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	vpos = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	hvel = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	vvel = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 190);
	solType = BinaryToDecimal(vel, "unsigned");
}

LocalPlanePos::LocalPlanePos(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 8, 46);
	n = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 8, 118);
	e = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 8, 190);
	u = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 8, 262);
	sep = IEEE(vel, 8);
	
	vel = BinaryStrGen(bynStr, 4, 298);
	pSigma = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 334);
	solType = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 343);
	grid = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 352);
	geoid = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 2, 361);
	prj = BinaryToDecimal(vel, "unsigned");
}

Dops::Dops(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	hdop = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	vdop = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	tdop = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 1, 154);
	solType = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 4, 163);
	edop = IEEE(vel, 4);
}

PosCov::PosCov(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	// CovMatr
	vel = BinaryStrGen(bynStr, 4, 46);
	covMatr.xx = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	covMatr.yy = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	covMatr.zz = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 154);
	covMatr.tt = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 190);
	covMatr.xy = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 226);
	covMatr.xz = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 262);
	covMatr.xt = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 298);
	covMatr.yz = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 334);
	covMatr.yt = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 370);
	covMatr.zt = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 1, 406);
	covMatr.solType = BinaryToDecimal(vel, "unsigned");
}

Baseline::Baseline(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
		
	vel = BinaryStrGen(bynStr, 4, 46);
	x = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 82);
	y = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 118);
	z = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 4, 154);
	sigma = IEEE(vel, 4);
		
	vel = BinaryStrGen(bynStr, 1, 190);
	solType = BinaryToDecimal(vel, "unsigned");
		
	vel = BinaryStrGen(bynStr, 4, 199);
	time = BinaryToDecimal(vel, "signed");
}

Baselines::Baselines(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;

	vel = BinaryStrGen(bynStr, 4, 46);
	b10[0] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 82);
	b10[1] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 118);
	b10[2] = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 154);
	b11[0] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 190);
	b11[1] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 226);
	b11[2] = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 262);
	b12[0] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 298);
	b12[1] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 334);
	b12[2] = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 370);
	rms[0] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 406);
	rms[1] = IEEE(vel, 4);
	vel = BinaryStrGen(bynStr, 4, 442);
	rms[2] = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 478);
	solType[0] = BinaryToDecimal(vel, "unsigned");
	vel = BinaryStrGen(bynStr, 4, 514);
	solType[1] = BinaryToDecimal(vel, "unsigned");
	vel = BinaryStrGen(bynStr, 4, 550);
	solType[2] = BinaryToDecimal(vel, "unsigned");
}

FullRotationMatr::FullRotationMatr(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	vel = BinaryStrGen(bynStr, 4, 46);
	q00 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 82);
	q01 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 118);
	q02 = IEEE(vel, 4);

	vel = BinaryStrGen(bynStr, 4, 154);
	q10 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 190);
	q11 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 226);
	q12 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 262);
	q20 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 298);
	q21 = IEEE(vel, 4);
	
	vel = BinaryStrGen(bynStr, 4, 334);
	q22 = IEEE(vel, 4);
}

PosStat::PosStat(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 1, 46);
	solType = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 55);
	gpsLocked = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 64);
	gloLocked = BinaryToDecimal(vel, "unsigned");

	vel = BinaryStrGen(bynStr, 1, 73);
	gpsAvail = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 82);
	gloAvail = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 91);
	gpsUsed = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 100);
	gloUsed = BinaryToDecimal(vel, "unsigned");
	
	vel = BinaryStrGen(bynStr, 1, 109);
	fixProg = BinaryToDecimal(vel, "unsigned");
}

PosCompTime::PosCompTime(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	vel = BinaryStrGen(bynStr, 4, 46);
	pt = BinaryToDecimal(vel, "unsigned");
}

SatIndex::SatIndex(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength; i++)
	{
		vel = BinaryStrGen(bynStr, 1, (46 + 9 * i));
		usi.Add(BinaryToDecimal(vel, "unsigned"));
	}
}

AntName::AntName(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	
	for ( int i = 0; i < dataLength; i++)
	{
		vel = BinaryStrGen(bynStr, 1, 46);
		name.Add(AsString(BinaryToDecimal(vel, "unsigned")));
	}
}

SatNumbers::SatNumbers(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	LOG("I'm in the SatNumbers Constructor");
	RDUMP(bynStr);
	for ( int i = 0; i < dataLength; i++)
	{
		vel = BinaryStrGen(bynStr, 1, (46 + 9 * i));
		RDUMP(vel);
		osn.Add(BinaryToDecimal(vel, "unsigned"));
	}
}

SatAzimuth::SatAzimuth(String dt, int size, char inStr[]) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength; i++)
	{
		vel = BinaryStrGen(bynStr, 1, 46);
		azim.Add(BinaryToDecimal(vel, "unsigned"));
	}
}

PseudoRange::PseudoRange(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	LOG("\nPseudo Range constructor test output");
	RDUMP(dataLength);
	RDUMP(bynStr);
	LOG("The end of Pseudo Range constructor test output\n");
	for ( int i = 0; i < dataLength/8; i++)
	{
		vel = BinaryStrGen(bynStr, 8, (46 + 72 * i));
		rp.Add(IEEE(vel,8));
	}
}

InPseudoRanges::InPseudoRanges(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		srp.Add(BinaryToDecimal(vel, "signed"));
	}
}

RelPseudoRanges::RelPseudoRanges(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		rpr.Add(IEEE(vel, 4));
	}
}

SRPR::SRPR(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/2; i++)
	{
		vel = BinaryStrGen(bynStr, 2, (46 + 18 * i));
		srpr.Add(BinaryToDecimal(vel, "unsigned"));
	}
}

SC::SC(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		String intStr = BinaryStrGen(bynStr, 2, 82);
		
		smooth.Add(Smooth(IEEE(vel,4), BinaryToDecimal(intStr, "unsigned")));
	}
}

SS::SS(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/2; i++)
	{
		vel = BinaryStrGen(bynStr, 2, (46 + 18 * i));
		smooth.Add(BinaryToDecimal(vel, "unsigned"));
	}
}

CP::CP(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/8; i++)
	{
		vel = BinaryStrGen(bynStr, 8, (46 + 72 * i));
		cp.Add(IEEE(vel, 8));
	}
}

SCP::SCP(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		scp.Add(IEEE(vel, 4));
	}
}

RCP_RC::RCP_RC(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		rcp.Add(IEEE(vel, 4));
	}
}

RCP_rc::RCP_rc(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/2; i++)
	{
		vel = BinaryStrGen(bynStr, 2, (46 + 18 * i));
		rcp.Add(BinaryToDecimal(vel, "signed"));
	}
}

Doppler::Doppler(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/4; i++)
	{
		vel = BinaryStrGen(bynStr, 4, (46 + 36 * i));
		dp.Add(BinaryToDecimal(vel, "signed"));
	}
}

SRDP::SRDP(String dt, int size, char inStr[], String type) : JpsData(dt, size, inStr)
{
	String vel;
	for ( int i = 0; i < dataLength/2; i++)
	{
		vel = BinaryStrGen(bynStr, 2, (46 + 18 * i));
		srdp.Add(BinaryToDecimal(vel, "signed"));
	}
}

//RTtoRTO(String dt, int size, char inStr[]);

// 48 == 0
// 49 == 1
// 0  == разделитель
