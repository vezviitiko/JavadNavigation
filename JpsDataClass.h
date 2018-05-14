#ifndef _ParsingJPS_JpsDataClass_h_
#define _ParsingJPS_JpsDataClass_h_

#include <Core/Core.h>

using namespace Upp;
using namespace std;

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


class SatElevations : public JpsData {
public:
	Vector <int> elevation;
	int nSats;
	SatElevations(String dt, int size, char inStr[], int satNum);
};

////Эпоха
//class EpochTime : public JpsData {
//public:
//	EpochTime(String dt, char inStr[]);
//	int tod;					//Time of Day	{Число секунд от начала суток}
//	int cs;						//Checksum		{Хз что такое. Спросить у Николаев}
//};
//



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


#endif