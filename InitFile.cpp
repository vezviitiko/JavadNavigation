#include "ParsingJPS.h"

//Методы класса InitFile
void InitFile::parse()
{
	StringStream inString;
	
	filesCount = 0;
	
	inString.Open(LoadFile(name));
	do{
		jpsFilesNames.Add(AsString(inString.GetLine()));
		filesCount++;
	}while(!inString.IsEof());
}