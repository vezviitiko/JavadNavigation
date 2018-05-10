#include "ParsingJPS.h"

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
	StringStream inStream;
	FILE* inFile;
	
	String jpsString;
	String jpsName;
	String jpsCont;
	String jpsBynStr;
	
//	JpsData* jps = new JpsData("","");
//	JpsData* predJps;
	
	int i = 0;
	LOG("Trying to open " << name << " file");
	if ((inFile = fopen(name, "rb")) == NULL){
		LOG("Faced problems while opening file ");
	}else{
		LOG("Sucsessfully opened file\n");
		inStream.Open(LoadFile(name));
		do{
			i++;
			jpsString = inStream.GetLine();
			if (jpsString.GetCount() != 0){
				jpsName = GetJpsName(jpsString);
				jpsCont = GetJpsValue(jpsString);
				jpsBynStr = GetBitsStr(jpsCont);
				if (jpsName == "JP") {JpsData* jps = new JpsFileId(jpsCont, jpsName, jpsBynStr); jpsData.Add(jps); delete jps;}
				if (jpsName == "MF") {JpsData* jps = new JpsFormat(jpsCont, jpsName, jpsBynStr); jpsData.Add(jps); delete jps;}
				if (jpsName == "~~") {
					JpsData* jps = new ReceiverTime(jpsName,jpsBynStr);
					jpsData.Add(jps),
					delete jps;
					LOG("strNum = " << AsString(i));
					LOG("Receiver Time Test");
					LOG(jpsCont);
					LOG(jpsBynStr);
					LOG(jpsString);
					LOG("");
				}
				if (jpsName == "::") {
					JpsData* jps = new EpochTime(jpsName, jpsBynStr);
					jpsData.Add(jps);
					delete jps;
					LOG("strNum = " << AsString(i));
					LOG("Epoch Time test");
					LOG(jpsCont);
					LOG(jpsBynStr);
					LOG(jpsString);
					LOG("");
				}
				if (jpsName == "RD") {
					JpsData* jps = new ReceiverDate(jpsName, jpsBynStr);
					jpsData.Add(jps);
					delete jps;
					LOG("strNum = " << AsString(i));
					LOG("Receiver Date Test");
					LOG(jpsCont);
					LOG(jpsBynStr);
					LOG(jpsString);
					LOG("");
				}
			}
		}while(!inStream.IsEof());
	}
}



//	int i = 0;
//	
//	LOG("Trying to open " << name << " file");
//	if((inFile = fopen(name, "rb")) == NULL){
//		LOG("Faced problems while opening file ");
//	}else{
//		LOG("Sucsessfully opened file\n");
//		inStream.Open(LoadFile(name));
//		do{
//			jpsString = inStream.GetLine();
//			if (jpsString.GetCount() != 0){
//				jpsName = GetJpsName(jpsString);
//				jpsCont = GetJpsValue(jpsString);
//				jpsRec.Add(JpsRec(jpsName, jpsCont));
//			}
//		}while(!inStream.IsEof());
//	}




//void JpsFile::outputFile()
//{
//	for (int i = 0; i < jpsRec.GetCount(); i++){
//		LOG(jpsRec[i].recName << " " << jpsRec[i].recStr);
//	}
//}

//void JpsFile::analyzeJpsVector()
//{
//	for (int i = 0; i < jpsRec.GetCount(); i++){
//		jpsRec[i].getBitsStr();
//	}
//	
//	for (int i = 0; i < jpsRec.GetCount(); i++){
//		if (jpsRec[i].recName == "JP") {/*Using JP constr*/}
//		if (jpsRec[i].recName == "MF") {/*Using MF constr*/}
//		if (jpsRec[i].recName == "~~")
//		{
//			JpsData* jps = new ReceiverTime("RT", jpsRec[i].binStr);
//			jpsData.Add(jps);
//		}
//	}
//}