#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#define MAX_TEXT 10000 // максимальная длина текста
#define MAX_LEX 100 // максимальная длина лексемы
#define MAX_KEYW 9 // число ключевых слов
typedef char TypeLex[MAX_LEX]; // изображение лексемы
typedef char TypeMod[MAX_TEXT];

// ключевые слова
#define TConst 1
#define TClass 2
#define TMain 3
#define TInt 4
#define TShort 5
#define TLong 6
#define TFloat 7
#define TReturn 8
#define TWhile 9


// идентификаторы и константы
#define TIdent 20
#define TConstInt 30
#define TConstExp 31
#define TConstFloat 32


// специальные знаки
#define TDot 40
#define TComma 41
#define TSemicolon 42
#define TLeftBracket 43
#define TRightBracket 44
#define TLeftSquareBracket 45
#define TRightSquareBracket 46

// знаки операций
#define TLess 50
#define TLessOrEqual 51
#define TMore 52
#define TGreatOrEqual 53
#define TEqual 54
#define TNotEqual 55
#define TOperatorEqvivalentnosti 56
#define TPlusEqual 57
#define TMinusEqual 58
#define TMultEqual 59
#define TDivEqual 60
#define TModeEqual 61

#define TSave 67
#define TLeftShift 69
#define TRightShift 70

#define TPlus 74
#define TMinus 75
#define TMult 76
#define TDiv 77
#define TMode 78

// конец исходного модуля
#define TEnd 100
// ошибочный символ
#define TErr 200
