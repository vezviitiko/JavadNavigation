#include "ParsingJPS.h"


String Revert(String rStr){
	String othStr;
	
	for (int i = 0; i <= rStr.GetLength(); i++){
		othStr += rStr[rStr.GetLength() - i];
	}
	
	return othStr;
}


String GetBitsStr(String recStr)
{
	String bitStr = "";
	String iStr;
	std::string recS = std::string(recStr);
	
	for (auto p = recS.begin(); p != recS.end(); ++p){
		char c = *p;
		iStr = "";
		for (int i = 0; i < 8; i++){
			bool isSet = c & (1 << i);
			if (isSet){
				iStr += AsString(1);
			}else{
				iStr += AsString(0);
			}
		}
		iStr = Revert(iStr);
		bitStr += iStr;
	}
	
	return bitStr;
}
//Vector <byte> StrToByteVec(String str){
//	Vector <byte> byteVec;
//	
//	LOG("It is ok");
//	
//	return byteVec;
//}

//	using namespace std;
//	
//	unsigned char test = 'a';
//	String tt1 = "a";
//	for (int i = 0; i < 8; i++){
//		tt1 += AsString((test >> i) & 1);
//		//LOG(AsString((test >> i) & 1));
//	}
//	LOG("Using unsigned char");
//	RDUMP(tt1);
//	
//	
//	LOG("\nUsing bitsmask");
//	char test2 = 'a';
//	String tt2 = "";
//	for (int i = 0; i < 8; i++){
//		bool isSet = test2 & (1 << i);
//		LOG("Bit " << AsString(i) << ": " << isSet);
//	}
//	
//	LOG("\nUsing a string");
//	string s = "abc";
//	String tt3;
//	String ttz = "";
//	for (auto p = s.begin(); p != s.end(); ++p){
//		char c = *p;
//		for (int i = 0; i < 8; i++){
//			tt3 = "";
//			bool isSet = c & (1 << i);
//			if (isSet){
//				tt3 += AsString(1);
//			}else{
//				tt3 += AsString(0);
//			}
//		}
//	}
//	RDUMP(ttz);
