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
			if (test == "~~") {JpsData* jps = new ReceiverTime("RT", strLen, str); jpsData.Add(jps); delete jps;}
//			if (test == "::") {	LOG("Have found ET");}
			if (test == "RD") {JpsData* jps = new ReceiverDate("RD", strLen, str); jpsData.Add(jps); delete jps;}
			if (test == "TO") {
				JpsData* jps = new RTtoRTO("TO", strLen, str);
				jpsData.Add(jps);
				delete jps;
				}
//			if (test == "DO") {LOG("Have found DO");}
//			if (test == "BP") {LOG("Have found BP");}
//			if (test == "GT") {LOG("Have found GT");}
//			if (test == "GO") {LOG("Have found GO");}
//			if (test == "NT") {LOG("Have found NT");}
//			if (test == "NO") {LOG("Have found NO");}
//			if (test == "EO") {LOG("Have found EO");}
//			if (test == "WO") {LOG("Have found WO");}
//			if (test == "QO") {LOG("Have found QO");}
//			if (test == "CO") {LOG("Have found CO");}
//			if (test == "Io") {LOG("Have found Io");}
//			if (test == "UO") {LOG("Have found UO");}
//			if (test == "WU") {LOG("Have found WU");}
//			if (test == "EU") {LOG("Have found EU");}
//			if (test == "QU") {LOG("Have found QU");}
//			if (test == "CU") {LOG("Have found CU");}
//			if (test == "IU") {LOG("Have found IU");}
//			if (test == "NU") {LOG("Have found NU");}
//			if (test == "ST") {LOG("Have found ST");}
//			if (test == "PO") {LOG("Have found PO");}
//			if (test == "VE") {LOG("Have found VE");}
//			if (test == "PV") {LOG("Have found PV");}
//			if (test == "PG") {LOG("Have found PG");}
//			if (test == "VG") {LOG("Have found VG");}
//			if (test == "SG") {LOG("Have found SG");}
//			if (test == "mp") {LOG("Have found mp");}
//			if (test == "bp") {LOG("Have found bp");}
//			if (test == "DP") {LOG("Have found DP");}
//			if (test == "SP") {LOG("Have found SP");}
//			if (test == "SV") {LOG("Have found SV");}
//			if (test == "BL") {LOG("Have found BL");}
//			if (test == "bL") {LOG("Have found bL");}
//			if (test == "mR") {LOG("Have found mR");}
//			if (test == "PS") {LOG("Have found PS");}
//			if (test == "SI") {LOG("Have found SI");}
//			if (test == "AN") {LOG("Have found AN");}
//			if (test == "NN") {LOG("Have found NN");}
			if (test == "EL") {
				JpsData* jps = new SatElevations("EL", strLen, str, 1);
				jpsData.Add(jps);
				delete jps;
			}
//			if (test == "AZ") {LOG("Have found AZ");}
//			if (test == "RC") {LOG("Have found RC");}
//			if (test == "R1") {LOG("Have found R1");}
//			if (test == "R2") {LOG("Have found R2");}
//			if (test == "R3") {LOG("Have found R3");}
//			if (test == "R5") {LOG("Have found R5");}
//			if (test == "Rl") {LOG("Have found RI");}
//			if (test == "rx") {LOG("Have found rx");}
//			if (test == "rc") {LOG("Have found rc");}
//			if (test == "r1") {LOG("Have found r1");}
//			if (test == "r2") {LOG("Have found r2");}
//			if (test == "r3") {LOG("Have found r3");}
//			if (test == "r5") {LOG("Have found r5");}
//			if (test == "rl") {LOG("Have found rl");}
//			if (test == "1R") {LOG("Have found 1R");}
//			if (test == "2R") {LOG("Have found 2R");}
//			if (test == "3R") {LOG("Have found 3R");}
//			if (test == "5R") {LOG("Have found 5R");}
//			if (test == "lR") {LOG("Have found lR");}
//			if (test == "cr") {LOG("Have found cr");}
//			if (test == "1r") {LOG("Have found 1r");}
//			if (test == "2r") {LOG("Have found 2r");}
//			if (test == "3r") {LOG("Have found 3r");}
//			if (test == "5r") {LOG("Have found 5r");}
//			if (test == "lr") {LOG("Have found lr");}
//			if (test == "GT") {LOG("Have found GP");}
		}
		
		
		//Отладка
		if (i > strLen + 100000)
		{break;}
	}
	
	//Закрытие (в данном случае файла)
	inFileStr.close();
}


//	ifstream inFileStr(name, ios::binary);
//		inFileStr.read((char*)&x, sizeof(x));
//	inFileStr.close();
//	LOG("WTF output");
//	RDUMP(x);


//				if (jpsName == "JP") {JpsData* jps = new JpsFileId(jpsCont, jpsName, jpsBynStr); jpsData.Add(jps); delete jps;}
//				if (jpsName == "MF") {JpsData* jps = new JpsFormat(jpsCont, jpsName, jpsBynStr); jpsData.Add(jps); delete jps;}
//				if (jpsName == "~~") {
//					JpsData* jps = new ReceiverTime(jpsName,jpsBynStr);
//					jpsData.Add(jps),
//					delete jps;
//					LOG("strNum = " << AsString(i));
//					LOG("Receiver Time Test");
//					LOG(jpsCont);
//					LOG(jpsBynStr);
//					LOG(jpsString);
//					LOG("");
//				}
//				if (jpsName == "::") {
//					JpsData* jps = new EpochTime(jpsName, jpsBynStr);
//					jpsData.Add(jps);
//					delete jps;
//					LOG("strNum = " << AsString(i));
//					LOG("Epoch Time test");
//					LOG(jpsCont);
//					LOG(jpsBynStr);
//					LOG(jpsString);
//					LOG("");
//				}
//				if (jpsName == "RD") {
//					JpsData* jps = new ReceiverDate(jpsName, jpsBynStr);
//					jpsData.Add(jps);
//					delete jps;
//					LOG("strNum = " << AsString(i));
//					LOG("Receiver Date Test");
//					LOG(jpsCont);
//					LOG(jpsBynStr);
//					LOG(jpsString);
//					LOG("");
//				}