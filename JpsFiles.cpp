#include "ParsingJPS.h"
#include "JpsDataClass.h"

String GetJpsName(String jpsString){
	String name = "";
	
	name += jpsString[0];
	name += jpsString[1];

	return name;
}

String GetJpsValue(String jpsString){
	String value = "";
	for (int i = 2; i < jpsString.GetCount() - 2; i++){
		value += jpsString[i];
	}
	return value;
}
//Методы класса JpsFile
JpsFile::JpsFile(String name_, String content_)
{
	name = name_;
	content = content_;
}

void JpsFile::readFile()
{
	int strLen = 1300;
	char buf;
	char str[strLen];
	int fileLen;
	string test;
	
	//открытие потока входящх данных {В данном случае в качестве потока рассматривается файл}
	ifstream inFileStr(name, ios::binary);
	
	//Определим длину файла
	inFileStr.seekg(0, inFileStr.end);
	fileLen = inFileStr.tellg();
	inFileStr.seekg(0, inFileStr.beg);
	
	cout << "test output\n";
	for (int i = 0; i < fileLen; i++){
		inFileStr.read((char*)&buf,1);
		if (i <= strLen){
			str[i] = buf;
		}else{
			for (int j = 0; j < strLen; j++){
				str[j] = str[j + 1];
			}
			str[strLen - 1] = buf;
			test = ""; test += str[0]; test += str[1];
//			if (test == "JP") {LOG("Have found JP");}
//			if (test == "MF") {LOG("Have found MF");}
			if (test == "~~") {
				jpsData.Add(new ReceiverTime("RT", strLen, str));
				}
				
			if (test == "::") {
				LOG("Have found ET");
			}
			if (test == "RD") {
				jpsData.Add(new ReceiverDate("RD", strLen, str));
			}
			
			if (test == "TO") {
				jpsData.Add(new RTtoRTO("TO", strLen, str));
				}
			if (test == "DO") {
				jpsData.Add(new DerOfRtOffset("DO", strLen, str));
			}
			if (test == "BP") {
				jpsData.Add(new RoughAccurOfTimApprox("BP", strLen, str));
			}
			if (test == "GT") {
				jpsData.Add(new GpsTime("GT", strLen, str));
			}
			if (test == "GO") {
				jpsData.Add(new GpsToRecTimOff("GO", strLen, str));
			}
			if (test == "NT") {
				jpsData.Add(new GloTime("NT", strLen, str));
			}
			if (test == "NO") {
				jpsData.Add(new GloRecTimOff("NO", strLen, str));
			}
			if (test == "EO") {
				jpsData.Add(new GalRecTimOff("EO", strLen, str));
			}
			if (test == "WO") {
				jpsData.Add(new SbasRecTimOff("WO", strLen, str));
			}
			if (test == "QO") {
				jpsData.Add(new QzssRecTimOff("QO", strLen, str));
			}
			if (test == "CO") {
				jpsData.Add(new BeiRecTimOff("CO", strLen, str));
			}
			if (test == "Io") {
				jpsData.Add(new IrnssRecTimOff("Io", strLen, str));
			}
			if (test == "UO") {
				jpsData.Add(new GpsUtcTimParam("UO", strLen, str));
			}
			if (test == "WU"){
				jpsData.Add(new SBASUtcTimParam("WU", strLen, str));
			}
			if (test == "EU"){
				jpsData.Add(new GalUtcGpsParam("EU", strLen, str));
			}
//			if (test == "QU") {
//				jpsData.Add(new QzssUtcParam("QU", strLen, str));
//			}
//			if (test == "CU") {
//				jpsData.Add(new BeiDouUtcParam("CU", strLen, str));
//			}
//			if (test == "IU") {
//				jpsData.Add(new IrnssUtcParam("IU", strLen, str));
//			}
			if (test == "NU") {
				jpsData.Add(new GloUtcGpsParam("NU", strLen, str));
			}
			if (test == "ST") {
				jpsData.Add(new SolutionTime("ST", strLen, str));
			}
			if (test == "PO") {
				jpsData.Add(new Pos("PO", strLen, str));
			}
			if (test == "VE") {
				jpsData.Add(new Vel("VE", strLen, str));
			}
			if (test == "PV") {
				jpsData.Add(new PosVel("PV", strLen, str));
			}
			if (test == "PG") {
				jpsData.Add(new GeoPos("PG", strLen, str));
			}
			if (test == "VG") {
				jpsData.Add(new GeoVel("VG", strLen, str));
			}
			if (test == "SG") {
				jpsData.Add(new Rms("SG", strLen, str));
			}
			if (test == "mp") {
				jpsData.Add(new LocalPlanePos("mp", strLen, str));
			}
//			if (test == "bp") {
//				jpsData.Add(new RSLocalPlanePos("bp", strLen, str));
//			}
			if (test == "DP")  {
				jpsData.Add(new Dops("DP", strLen, str));
			}
			if (test == "SP")   {
				jpsData.Add(new PosCov("SP", strLen, str));
			}
//			if (test == "SV")   {
//				jpsData.Add(new VelCov("SV", strLen, str));
//			}
			if (test == "BL")  {
				jpsData.Add(new Baseline("BL", strLen, str));
			}
			if (test == "bL")  {
				jpsData.Add(new Baselines("bL", strLen, str));
			}
			if (test == "mR") {
				jpsData.Add(new FullRotationMatr("mR", strLen, str));
			}
			if (test == "PS")  {
				jpsData.Add(new PosStat("PS", strLen, str));
			}
			if (test == "PT")  {
				jpsData.Add(new PosCompTime("PT", strLen, str));
			}
			if (test == "SI")  {
				jpsData.Add(new SatIndex("SI", strLen, str));
			}
			if (test == "AN") {
				jpsData.Add(new AntName("AN", strLen, str));
			}
			if (test == "NN") {
				jpsData.Add(new SatNumbers("NN", strLen, str));
			}
			if (test == "EL") {
				jpsData.Add(new SatElevations("EL", strLen, str, 1));
			}
			if (test == "AZ") {
				 jpsData.Add(new SatAzimuth("AZ", strLen, str));
			}
			
			if (test == "RC") {
				 jpsData.Add(new PseudoRange("RC", strLen, str, "RC"));
			}
			if (test == "R1") {
				 jpsData.Add(new PseudoRange("R1", strLen, str, "R1"));
			}
			if (test == "R2") {
				 jpsData.Add(new PseudoRange("R2", strLen, str, "R2"));
			}
			if (test == "R3") {
				 jpsData.Add(new PseudoRange("R3", strLen, str, "R3"));
			}
			if (test == "R5") {
				 jpsData.Add(new PseudoRange("R5", strLen, str, "R5"));
			}
			if (test == "Rl") {
				 jpsData.Add(new PseudoRange("Rl", strLen, str, "Rl"));
			}
			
			if (test == "rx") {
				 jpsData.Add(new InPseudoRanges("rx", strLen, str, "rx"));
			}
			if (test == "rc") {
				 jpsData.Add(new InPseudoRanges("rc", strLen, str, "rc"));
			}
			if (test == "r1") {
				 jpsData.Add(new InPseudoRanges("r1", strLen, str, "r1"));
			}
			if (test == "r2") {
				 jpsData.Add(new InPseudoRanges("r2", strLen, str, "r2"));
			}
			if (test == "r3") {
				 jpsData.Add(new InPseudoRanges("r3", strLen, str, "r3"));
			}
			if (test == "r5") {
				 jpsData.Add(new InPseudoRanges("r5", strLen, str, "r5"));
			}
			if (test == "rl") {
				 jpsData.Add(new InPseudoRanges("rl", strLen, str, "rl"));
			}
			if (test == "1R") {
				 jpsData.Add(new RelPseudoRanges("1R", strLen, str, "1R"));
			}
			if (test == "2R") {
				 jpsData.Add(new RelPseudoRanges("2R", strLen, str, "2R"));
			}
			if (test == "3R") {
				 jpsData.Add(new RelPseudoRanges("3R", strLen, str, "3R"));
			}
			if (test == "5R") {
				 jpsData.Add(new RelPseudoRanges("5R", strLen, str, "5R"));
			}
			if (test == "lR") {
				 jpsData.Add(new RelPseudoRanges("lR", strLen, str, "lR"));
			}
			if (test == "cr") {
				 jpsData.Add(new SRPR("cr", strLen, str, "cr"));
			}
			if (test == "1r") {
				 jpsData.Add(new SRPR("1r", strLen, str, "1r"));
			}
			if (test == "2r") {
				 jpsData.Add(new SRPR("2r", strLen, str, "2r"));
			}
			if (test == "3r") {
				 jpsData.Add(new SRPR("3r", strLen, str, "3r"));
			}
			if (test == "5r") {
				 jpsData.Add(new SRPR("5r", strLen, str, "5r"));
			}
			if (test == "lr") {
				 jpsData.Add(new SRPR("lr", strLen, str, "lr"));
			}
			if (test == "CC") {
				 jpsData.Add(new SC("CC", strLen, str, "CC"));
			}
			if (test == "C1") {
				 jpsData.Add(new SC("C1", strLen, str, "C1"));
			}
			if (test == "C2") {
				 jpsData.Add(new SC("C2", strLen, str, "C2"));
			}
			if (test == "C3") {
				 jpsData.Add(new SC("C3", strLen, str, "C3"));
			}
			if (test == "C5") {
				 jpsData.Add(new SC("C5", strLen, str, "C5"));
			}
			if (test == "Cl") {
				 jpsData.Add(new SC("Cl", strLen, str, "Cl"));
			}
			if (test == "сс") {
				 jpsData.Add(new SC("сс", strLen, str, "сс"));
			}
			if (test == "с1") {
				 jpsData.Add(new SS("с1", strLen, str, "с1"));
			}
			if (test == "с2") {
				 jpsData.Add(new SS("с2", strLen, str, "с2"));
			}
			if (test == "с3") {
				 jpsData.Add(new SS("с3", strLen, str, "с3"));
			}
			if (test == "с5") {
				 jpsData.Add(new SS("с5", strLen, str, "с5"));
			}
			if (test == "cl") {
				 jpsData.Add(new SS("cl", strLen, str, "cl"));
			}
			if (test == "PC") {
				 jpsData.Add(new CP("PC", strLen, str, "PC"));
			}
			if (test == "P1") {
				 jpsData.Add(new CP("P1", strLen, str, "P1"));
			}
			if (test == "P2") {
				 jpsData.Add(new CP("P2", strLen, str, "P2"));
			}
			if (test == "P3") {
				 jpsData.Add(new CP("P3", strLen, str, "P3"));
			}
			if (test == "P5") {
				 jpsData.Add(new CP("P5", strLen, str, "P5"));
			}
			if (test == "Pl") {
				 jpsData.Add(new CP("Pl", strLen, str, "Pl"));
			}
						
			if (test == "pc") {
				 jpsData.Add(new SCP("pc", strLen, str, "pc"));
			}
			if (test == "p1") {
				 jpsData.Add(new SCP("p1", strLen, str, "p1"));
			}
			if (test == "p2") {
				 jpsData.Add(new SCP("p2", strLen, str, "p2"));
			}
			if (test == "p3") {
				 jpsData.Add(new SCP("p3", strLen, str, "p3"));
			}
			if (test == "p5") {
				 jpsData.Add(new SCP("p5", strLen, str, "p5"));
			}
			if (test == "pl") {
				 jpsData.Add(new SCP("pl", strLen, str, "pl"));
			}
			
			if (test == "CP") {
				 jpsData.Add(new RCP_RC("CP", strLen, str, "CP"));
			}
			if (test == "1P") {
				 jpsData.Add(new RCP_RC("1P", strLen, str, "1P"));
			}
			if (test == "2P") {
				 jpsData.Add(new RCP_RC("2P", strLen, str, "2P"));
			}
			if (test == "3P") {
				 jpsData.Add(new RCP_RC("3P", strLen, str, "3P"));
			}
			if (test == "5P") {
				 jpsData.Add(new RCP_RC("5P", strLen, str, "5P"));
			}
			if (test == "lP") {
				 jpsData.Add(new RCP_RC("lP", strLen, str, "lP"));
			}
			
			if (test == "cp") {
				 jpsData.Add(new RCP_rc("cp", strLen, str, "cp"));
			}
			if (test == "1p") {
				 jpsData.Add(new RCP_rc("1p", strLen, str, "1p"));
			}
			if (test == "2p") {
				jpsData.Add(new RCP_rc("2p", strLen, str, "2p"));
			}
			if (test == "3p") {
				jpsData.Add(new RCP_rc("3p", strLen, str, "3p"));
			}
			if (test == "5p") {
				jpsData.Add(new RCP_rc("5p", strLen, str, "5p"));
			}
			if (test == "lp") {
				jpsData.Add(new RCP_rc("lp", strLen, str, "lp"));
			}
			
			if (test == "DX") {
				jpsData.Add(new Doppler("DX", strLen, str, "DX"));
			}
			if (test == "DC") {
				jpsData.Add(new Doppler("DC", strLen, str, "DC"));
			}
			if (test == "D1") {
				jpsData.Add(new Doppler("D1", strLen, str, "D1"));
			}
			if (test == "D2") {
				jpsData.Add(new Doppler("D2", strLen, str, "D2"));
			}
			if (test == "D3") {
				jpsData.Add(new Doppler("D3", strLen, str, "D3"));
			}
			if (test == "D5") {
				jpsData.Add(new Doppler("D5", strLen, str, "D5"));
			}
			if (test == "Dl") {
				jpsData.Add(new Doppler("Dl", strLen, str, "Dl"));
			}
			if (test == "0d") {
				jpsData.Add(new SRDP("0d", strLen, str, "0d"));
			}
			if (test == "1d") {
				jpsData.Add(new SRDP("1d", strLen, str, "1d"));
			}
			if (test == "2d") {
				jpsData.Add(new SRDP("2d", strLen, str, "2d"));
			}
			if (test == "3d") {
				jpsData.Add(new SRDP("3d", strLen, str, "3d"));
			}
			if (test == "5d") {
				jpsData.Add(new SRDP("5d", strLen, str, "5d"));
			}
			if (test == "ld") {
				jpsData.Add(new SRDP("ld", strLen, str, "ld"));
			}
		}
		
		
		//Отладка
		
		if (i > strLen + 20000)
		{LOG("FIN"); break;}
	}
	
	//Закрытие (в данном случае файла)
	inFileStr.close();
}


void JpsFile::analyzeJpsVector()
{
	long int tod = 0;
	ReceiverDate recDat;
	Vector<int> intVect;
	
	for (int i = 0; i < jpsData.GetCount(); i++)
	{
		if ((jpsData[i] -> datType) == "SI"){
			LOG("These are SI Value");
			try{
				SatIndex *SI = dynamic_cast<SatIndex*>(jpsData[i]);
				//Записываем в большой массив нужыне нам номера
			}catch(std::bad_cast){
				LOG("SI Cast Failed");
			}
		}
		
		if ((jpsData[i] -> datType) == "NN"){
			try{
				SatNumbers *NN = dynamic_cast<SatNumbers*>(jpsData[i]);
				//Записываем данные в массив
				
			}catch(std::bad_cast){
				LOG("NN Cast Failed");
			}
		}
		
		if ((jpsData[i] -> datType) == "RT"){
			try{
				ReceiverTime *RT = dynamic_cast<ReceiverTime*>(jpsData[i]);
				//Записываем данные в массив
			}catch(std::bad_cast){
				LOG("Failed RT Cast");
			}
		}
		
		if ((jpsData[i] -> datType) == "RD"){
			try{
				ReceiverDate *RD = dynamic_cast<ReceiverDate*>(jpsData[i]);
				//Записываем данные в массив
			}catch(std::bad_cast){
				LOG("Failed RD Cast");
			}
		}
		
		if ((jpsData[i] -> datType) == "RC" || (jpsData[i] -> datType) == "R1"
			|| (jpsData[i] -> datType) == "R2" || (jpsData[i] -> datType) == "R3"
			|| (jpsData[i] -> datType) == "R5" || (jpsData[i] -> datType) == "Rl")
		{
			try{
				PseudoRange *PR = dynamic_cast<PseudoRange*>(jpsData[i]);
				//Записываем данные в массив
			}catch(std::bad_cast){
				LOG("Failed PR Cast");
			}
		}
	}
}

void JpsFile::clearJpsDataVector()
{
	
}