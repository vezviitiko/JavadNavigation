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
				headerValStr += char(BinaryToDecimal(valStr));
				valStr = "";
			}
		}
		if (bynStr[i] == 0) {count++;}
	}while (count < 5);
	dataLength = int(atof(headerValStr));
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
	tod = BinaryToDecimal(secStr);
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
			year = BinaryToDecimal(val[1] + val[0]);
		}
		if (i == 2) {month = BinaryToDecimal(val[0]);}
		if (i == 3) {day   = BinaryToDecimal(val[0]);}
		val[0] = "";
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
		RDUMP(dataLength);
	}
}


// 48 == 0
// 49 == 1
// 0  == разделитель