
#include "defs.h"
#include "Semant.h"
#include "Scaner.h"



class Diagram {
private:
	Scaner* sc;
	Tree* Root;
	// функции СД:
	void Class();
	void Main();
	void Dannie();
	void Operator();
	void SostOperator();
	void While();
	void Prisvaivanie();

	PrimitiveDataType Viraj();
	PrimitiveDataType Sravnenie();
	PrimitiveDataType Sdvig();
	PrimitiveDataType Slagaemoe();
	PrimitiveDataType Mnojitel();
	PrimitiveDataType ElemViraj();

public:
	Diagram(Scaner* s) { sc = s; Root = new	Tree(sc); }
	~Diagram() {}
	void Programm(); // программа
	void Print();
};

#pragma once
