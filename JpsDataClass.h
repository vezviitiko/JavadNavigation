#ifndef _ParsingJPS_JpsDataClass_h_
#define _ParsingJPS_JpsDataClass_h_

#include <Core/Core.h>

using namespace Upp;

//Главный родительский класс
class JpsData{
public:
	JpsData(String dt, String bs);
	String bynStr;			//Бинарная строка данных
	String datType;			//Тип Jps-строки
	
	//Здесь в дочерних классах добавляется
	//переменная для данных необходимого типа
};

//Идентификатор файла
class JpsFileId : public JpsData {
public:
	JpsFileId(String readableStr, String dt, String bs);
	String readableStr;									//Строка читаьельная
	String fileTypeId;									//Идентификатор типа файла
	String descriptor;									//Описание
};

//Формат сообщений
class JpsFormat : public JpsData {
public:
	JpsFormat(String readableStr, String dt, String bs);
	
	String id;
	String majorVer;
	String minorVer;
	String order;
	int cs;
};

//Время приёмника
class ReceiverTime : public JpsData {
public:
	ReceiverTime(String dt, String bs);
	int tod;						//Time of Day	{Число секунд от начала суток}
	int cs;							//Checksum		{Хз что такое. Спросить у Николаев}
};

//Эпоха
class EpochTime : public JpsData {
public:
	EpochTime(String dt, String bs);
	int tod;					//Time of Day	{Число секунд от начала суток}
	int cs;						//Checksum		{Хз что такое. Спросить у Николаев}
};

class ReceiverDate : public JpsData {
public:
	ReceiverDate(String, String);
	int year;
	int month;
	int day;
	int base;
	int cs;
};

#endif