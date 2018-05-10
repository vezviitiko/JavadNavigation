#include "JpsDataClass.h"

//В этом файле собраны конструкторы читалки
//для разных типов строк и соответствующих им типов данных

JpsData::JpsData(String dt, String bs)
{
	datType = dt;
	bynStr = bs;
}

ReceiverTime::ReceiverTime(String dt, String bs) : JpsData(dt, bs)
{
	
}

EpochTime::EpochTime(String dt, String bs) : JpsData(dt, bs)
{
	
}

JpsFileId::JpsFileId(String readStr, String dt, String bs) : JpsData(dt, bs)
{
	
}

JpsFormat::JpsFormat(String readStr, String dt, String bs) : JpsData(dt, bs)
{
	
}

ReceiverDate::ReceiverDate(String dt, String bs) : JpsData(dt, bs)
{
	
}