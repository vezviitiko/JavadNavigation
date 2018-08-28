#ifndef _ParsingJPS_ParsingJPS_h
#define _ParsingJPS_ParsingJPS_h

#include <Core/Core.h>
#include <fstream>
#include <math.h>
#include <iostream>

#include "JpsDataClass.h"
#include "NavSol.h"
#include "DataConverter.h"

using namespace Upp;
using namespace std;

class JpsFile :public Moveable<JpsFile>{
public:
	typedef JpsFile CLASSNAME;
	String name;
	String content;
	
	String fileIdent;
	//double JpsData;
	
	JpsData *jpsData;
	//Vector <JpsData*> jpsData;
	NavSolInputData navSolDat;
	
	void readFile();
	void analyzeJpsVector();
	void clearJpsDataVector();
	
	//Метод вывода на экран содержимого файла
	void outputFile();
	
	//Конструктор класса
	JpsFile(String name_, String content_);
};

class InitFile{
public:
	String name = "ParsingJps.ini";
	Vector<String> jpsFilesNames;
	int filesCount;
	void parse();
};

class TestJpsDataClass : public JpsData{
	
};

class PseudoRangeData : public Moveable<PseudoRangeData>{
public:
	typedef PseudoRangeData CLASSNAME;
	
	double time;			//Эпоха измерений в форме MJD;
	Vector <int> si;		//Номер аппарата в дальнейших сообщениях
	Vector <int> nn;		//Индексы аппаратов в собственной системе
	Vector <double> range;	//Значения псевдодальностей
	String type;			//Тип псевдодальности (Возможно на что то повлияет)
};

//Дополнительные функции
String Revert(String);
String GetBitsStr(string recStr);
double BinaryToDecimal(String binStr, String type);
double HexToDec(String hexStr);
String BinToHex(String binStr, int len);
String BinaryStrGen(String binStr , int sizeBit, int start);
#endif
