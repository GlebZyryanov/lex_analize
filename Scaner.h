
#include "defs.h"


class Scaner {
private:
	TypeMod t; // исходный текст
	int uk; // позиция в исходном тексте
	int line_number;		//строка
	int position;		//позиция
	FILE* in;
public:
	Scaner(FILE*);
	~Scaner() {}
	void PutUK(int);
	int GetUK();

	void PrintError(string, string);
	int Scan(TypeLex l); // выделение очередной лексемы

	void GetData(FILE*); // ввод текста из файла с заданным именем
};

#pragma once
