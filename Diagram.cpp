#include "Diagram.h"
#include "Semant.h"
void Diagram::Programm()
{
	TypeLex l;
	int t, t1, uk1;

	uk1 = sc->GetUK();
	t = sc->Scan(l);

	while (t != TEnd)
	{
		t1 = sc->Scan(l);
		sc->PutUK(uk1);
		if (t == TClass) Class();
		else if (t == TInt && t1 == TMain) Main();
		else Dannie();

		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
}

void Diagram::Class()
{
	TypeLex l;
	int t, uk1;

	t = sc->Scan(l);
	if (t != TClass) sc->PrintError("ОЖИДАЛСЯ class (СД КЛАСС)", l);
	t = sc->Scan(l);
	if (t != TIdent) sc->PrintError("ОЖИДАЛСЯ ИДЕНТИФИКАТОР (СД КЛАСС)", l);

	Tree* v = Root->SemInclude(l, ObjTypeClass, UndefinedType, false);

	t = sc->Scan(l);
	if (t != TLeftSquareBracket) sc->PrintError("ОЖИДАЛСЯ  \'{\'` (СД КЛАСС)", l);

	uk1 = sc->GetUK();
	t = sc->Scan(l);

	while (t != TRightSquareBracket)
	{
		sc->PutUK(uk1);
		Dannie();
		uk1 = sc->GetUK();
		t = sc->Scan(l);
	}
	t = sc->Scan(l);
	if (t != TSemicolon) sc->PrintError("ОЖИДАЛСЯ \';\' (СД КЛАСС)", l);
	Root->SetCur(v);
}

void Diagram::Main()
{
	TypeLex l;
	int t;
	t = sc->Scan(l);

	if (t != TInt) sc->PrintError("ОЖИДАЛСЯ int (СД МЕЙН)", l);
	t = sc->Scan(l);
	if (t != TMain) sc->PrintError("ОЖИДАЛСЯ main (СД МЕЙН)", l);
	t = sc->Scan(l);
	if (t != TLeftBracket) sc->PrintError("ОЖИДАЛСЯ \'(\' (СД МЕЙН)", l);
	t = sc->Scan(l);
	if (t != TRightBracket) sc->PrintError("ОЖИДАЛСЯ \')\' (СД МЕЙН)", l);
	Tree* v = Root->SemInclude((char*)"main", ObjMain, IntegerType, false);
	SostOperator();
	Root->SetCur(v);
}

void Diagram::Dannie()
{
	TypeLex l;
	int t, uk1;

	TypeObject tob = ObjEmpty;
	PrimitiveDataType tda = UndefinedType;
	bool itConst = false;

	uk1 = sc->GetUK(); t = sc->Scan(l);

	if (t != TIdent) {
		if (t != TConst)
			sc->PutUK(uk1);
		else
			itConst = true;

		t = sc->Scan(l);
		if (t == TShort || t == TLong) {
			if (t == TShort)
				tda = ShortType;
			t = sc->Scan(l);
			if (t != TInt) sc->PrintError("Ожидался int (СД ДАННЫЕ)", l);
		}

		if (t != TInt && t != TFloat) sc->PrintError("Ожидался int/float (СД ДАННЫЕ)", l);

		tob = ObjVar;	
	}
	else
		tob = ObjClass;

	if (tda != ShortType)
		tda = Root->GetType(t);

	do {
		t = sc->Scan(l);

		if (t != TIdent) sc->PrintError("Ожидался идентефикатор (СД ДАННЫЕ)", l);

		Tree* v = Root->SemInclude(l, tob, tda, itConst);

		//if (tda == UndefinedType) {
		//	Tree* cl = Root->SemGetType(l);
		//	v->SetRightT(cl->GetRight());
		//}
		if (itConst) {
			uk1 = sc->GetUK();
			t = sc->Scan(l);

			if (t != TSave) sc->PrintError("Для константы требуется инициализация", l);
			sc->PutUK(uk1);
		}

		//uk1 = sc->GetUK();
		t = sc->Scan(l);

		if (t == TSave) {
			Viraj();
			t = sc->Scan(l);
		}
	} while (t == TComma);

	if (t != TSemicolon) sc->PrintError("Ожидался символ \';\' (СД ДАННЫЕ)", l);
}

/*
* 
* Ранее использованный код данных
void Diagram::Dannie()
{
	TypeLex l;
	int t, uk1;

	TypeObject tob = ObjEmpty;
	PrimitiveDataType tda = UndefinedType;
	bool itConst = false;


	uk1 = sc->GetUK(); t = sc->Scan(l);

	if (t != TConst)
	{
		sc->PutUK(uk1);
	}
	else {
			itConst = true;
	}
	t = sc->Scan(l);
	if (t == TShort || t == TLong) {
		if (t == TShort) {
			tda = ShortType;
		}
		t = sc->Scan(l);
		if (t != TInt) sc->PrintError("ОЖИДАЛСЯ int (СД ДАННЫЕ)", l);

	}
	if (t != TInt && t != TFloat && t != TIdent) sc->PrintError("(СД ДАННЫЕ) ОЖИДАЛСЯ ТИП ИЛИ ИДЕНТИФИКАТОР А ПОЛУЧИЛИ", l);
	tob = ObjVar;
	do {
		t = sc->Scan(l);
		if (t != TIdent) sc->PrintError("ОЖИДАЛСЯ ИДЕНТИФИКАТОР (СД ДАННЫЕ)", l);
		uk1 = sc->GetUK();
		t = sc->Scan(l);

		if (t == TSave) {
			Viraj();
			t = sc->Scan(l);
		}
	} while (t == TComma);

	if (t != TSemicolon) sc->PrintError("ОЖИДАЛСЯ \';\' (СД ДАННЫЕ)", l);
}
*/


void Diagram::Operator()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType result;

	uk1 = sc->GetUK();
	t = sc->Scan(l);

	if (t == TLeftSquareBracket || t == TWhile) {
		sc->PutUK(uk1);
		if (t == TLeftSquareBracket) SostOperator();
		if (t == TWhile) While();

	}
	else {
		if (t == TIdent) {
			sc->PutUK(uk1);
			Prisvaivanie();
			t = sc->Scan(l);
		}
		if (t == TReturn) {
			result = Viraj();
			if (result != IntegerType) sc->PrintError("Возвращаемое значение должно быть int", "");
			t = sc->Scan(l);
		}

		if (t != TSemicolon) sc->PrintError("ОЖИДАЛСЯ \';\' (СД ОПЕРАТОР)", l);
	}
}

/*
Ранее использованный код оператора
void Diagram::Operator()
{
	TypeLex l;
	int t, uk1;
	

	uk1 = sc->GetUK();
	t = sc->Scan(l);

	if (t == TLeftSquareBracket || t == TWhile) {
		sc->PutUK(uk1);
		if (t == TLeftSquareBracket) SostOperator();
		if (t == TWhile) While();

	}
	else {
		if (t == TIdent) {
			sc->PutUK(uk1);
			Prisvaivanie();
			t = sc->Scan(l);
		}
		if (t == TReturn) {
			Viraj();
			t = sc->Scan(l);
		}

		if (t != TSemicolon) sc->PrintError("ОЖИДАЛСЯ \';\' (СД ОПЕРАТОР)", l);
	}
}

*/

void Diagram::SostOperator()
{
	TypeLex l;
	int t, t1, uk1;

	t = sc->Scan(l);
	if (t != TLeftSquareBracket) sc->PrintError("ОЖИДАЛСЯ \'{\' (СД СОСТАВНОЙ ОПЕРАТОР)", l);

	uk1 = sc->GetUK();
	t = sc->Scan(l);
	t1 = sc->Scan(l);
	sc->PutUK(uk1);
	while (t != TRightSquareBracket)
	{
		if (t == TConst || t == TShort ||
			t == TLong || t == TInt ||
			t == TFloat || (t == TIdent && t1 == TIdent)) Dannie();
		else Operator();
		uk1 = sc->GetUK(); t = sc->Scan(l); t1 = sc->Scan(l); sc->PutUK(uk1);
	}
	t = sc->Scan(l);
}

void Diagram::While()
{
	TypeLex l;
	int t, uk1;


	t = sc->Scan(l);

	if (t != TWhile) sc->PrintError("ОЖИДАЛСЯ while ", l);

	Tree* v = Root->SemInclude(l, ObjVar, IntegerType, 0);

	t = sc->Scan(l);
	if (t != TLeftBracket) sc->PrintError("ОЖИДАЛСЯ \'(\'", l);
	Viraj();
	t = sc->Scan(l);
	if (t != TRightBracket) sc->PrintError("ОЖИДАЛСЯ \')\'", l);
	Operator();
}

void Diagram::Prisvaivanie()
{
	TypeLex l;
	int t, t1;
	t = sc->Scan(l);

	if (t != TIdent) sc->PrintError("ОЖИДАЛСЯ ИДЕНТИФИКАТОР (СД ПРИСВАИВАНИЕ)", l);

	Tree* var = Root->SemFindVar(l);

	TypeObject tObjVar = Root->GetObjType(var);


	t = sc->Scan(l);
	if (tObjVar == ObjClass) {
		if (t != TDot) sc->PrintError("Нельзя проводить операцию присваивания с объектом класса!", l);
		while (t == TDot) {
			t = sc->Scan(l);
			if (t != TIdent) sc->PrintError("ОЖИДАЛСЯ идентификатор (СД ПРИСВАИВАНИЕ)", l);

			Tree* st = Root->SemFindClassVar(l);

			t = sc->Scan(l);

		}
	}
	if (t < TPlusEqual || t >TSave) {
		sc->PrintError("Ожидался либо != либо = (СД ПРИСВАИВАНИЕ)", l);
	}
	Viraj();
}

PrimitiveDataType Diagram::Viraj()
{
	TypeLex l;
	PrimitiveDataType operand1, operand2;
	int t, uk1;
	operand1 = Sravnenie();
	uk1 = sc->GetUK(); t = sc->Scan(l);
	while ((t == TLeftShift || (t == TRightShift))){
		operand2 = Sravnenie();
		operand1 = Root->GetTypeResult(operand1, operand2, t, l);
		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return operand1;
}


PrimitiveDataType Diagram::Sravnenie()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType operand1, operand2;
	operand1 = Sdvig();
	uk1 = sc->GetUK(); t = sc->Scan(l);
	while ((t >= TLess) && (t <= TOperatorEqvivalentnosti)) {
		operand2 = Sdvig();
		operand1 = Root->GetTypeResult(operand1, operand2, t, l);
		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return operand1;
}

PrimitiveDataType Diagram::Sdvig()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType operand1, operand2;
	operand1 = Slagaemoe();
	uk1 = sc->GetUK(); t = sc->Scan(l);
	while ((t == TLeftShift) || (t == TRightShift)) {
		operand2 = Slagaemoe();
		operand1 = Root->GetTypeResult(operand1, operand2, t, l);
		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return operand1;
}

PrimitiveDataType Diagram::Slagaemoe()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType operand1, operand2;
	operand1 = Mnojitel();
	uk1 = sc->GetUK(); t = sc->Scan(l);
	while ((t == TPlus) || (t == TMinus)) {
		operand2 = Mnojitel();
		operand1 = Root->GetTypeResult(operand1, operand2, t, l);
		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return operand1;
}

PrimitiveDataType Diagram::Mnojitel()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType operand1, operand2;
	operand1 = ElemViraj();
	uk1 = sc->GetUK(); t = sc->Scan(l);
	while ((t == TDiv) || (t == TMult) || (t == TMode)) {
		operand2 = ElemViraj();
		operand1 = Root->GetTypeResult(operand1, operand2, t, l);
		uk1 = sc->GetUK(); t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return operand1;
}


PrimitiveDataType Diagram::ElemViraj()
{
	TypeLex l;
	int t, uk1;
	PrimitiveDataType result;

	t = sc->Scan(l);

	if (t == TConstExp) {
		return FloatType;
	}
		
	if (t == TConstInt) {
		return IntegerType;
	}
		
	if (t == TConstFloat) {
		return FloatType;
	}

	if (t == TLeftBracket) {
		result = Viraj();
		t = sc->Scan(l);
		if (t != TRightBracket) sc->PrintError("ожидался символ \')\' (СД ЭЛ.ВЫРАЖЕНИЕ)", l);
		return result;
	}

	if (t != TIdent) sc->PrintError("ожидался идентификатор (СД ЭЛ.ВЫРАЖЕНИЕ)", l);

	Tree* var = Root->SemFindVar(l);
	TypeObject tObjVar = Root->GetObjType(var);

	if (tObjVar == ObjVar) return Root->GetDataType(var);

	uk1 = sc->GetUK();
	t = sc->Scan(l);

	if (t != TDot) sc->PrintError("Ожидалось поле класса", l);

	while (t == TDot) {
		t = sc->Scan(l);
		if (t != TIdent) sc->PrintError("Ожидался идентификатор (СД ЭЛ.ВЫРАЖЕНИЕ)", l);
		Tree* stVar = Root->SemFindClassVar(l);

		result = Root->GetDataType(stVar);

		uk1 = sc->GetUK();
		t = sc->Scan(l);
	}
	sc->PutUK(uk1);
	return result;
}

void Diagram::Print() {
	Root->Print();
}
