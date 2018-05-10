#include "ParsingJPS.h"



CONSOLE_APP_MAIN
{
	InitFile initFile;
	Vector<JpsFile> jpsFile;
	initFile.parse();
	
	//Формируем массив jps-файлов
	for (int i = 0; i < initFile.jpsFilesNames.GetCount(); i++)
	{
		jpsFile.Add(JpsFile(initFile.jpsFilesNames[i],""));
	}
	
	for (int i = 0; i < jpsFile.GetCount(); i++){
		LOG("I'm here");
		jpsFile[i].readFile();
		break;		//Убрать. Поставил для отладки
	}
}