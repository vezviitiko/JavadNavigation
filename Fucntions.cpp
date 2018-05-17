#include "ParsingJPS.h"

#include <bitset>

String Revert(String rStr){
	String othStr;
	
	for (int i = 0; i <= rStr.GetLength(); i++){
		othStr += rStr[rStr.GetLength() - i];
	}
	
	return othStr;
}


String GetBitsStr(string recStr)
{
	String bitStr = "";
	String iStr;
	std::string recS = recStr;
	
//	cout << "\nnew test output\n" << recStr << "\n";
	
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

double BinaryToDecimal(String binStr)
{
	double val;
	String valStr;
	valStr << bitset<2000>(string(binStr)).to_ullong();
	val = atof(valStr);
	return val;
}