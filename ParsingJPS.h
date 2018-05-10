#ifndef _ParsingJPS_ParsingJPS_h
#define _ParsingJPS_ParsingJPS_h

#include <Core/Core.h>
#include <fstream>

#include "JpsDataClass.h"

using namespace Upp;

class JpsFile :public Moveable<JpsFile>{
public:
	typedef JpsFile CLASSNAME;
	String name;
	String content;
	
	String fileIdent;
	
	Vector <JpsData*> jpsData;
	
	void readFile();
	void analyzeJpsVector();
	
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


//Дополнительные функции
String Revert(String);
String GetBitsStr(String recStr);
#endif
