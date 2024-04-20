#pragma once
#include "defs.h"
#include "Scaner.h"

enum TypeObject {
    ObjEmpty = 0,   // пустая вершина
    ObjVar,         // переменная
    ObjClass,      // объект типа класса
    ObjTypeClass,  // тип  «класс» 
    ObjMain         // main
};

enum PrimitiveDataType {
    UndefinedType = 0,   // для пустой вершины
    IntegerType,
    ShortType,
    FloatType
};
static const char* PrimitiveDataTypeStrings[] = { "undef", "int", "short", "float" };

struct Node {
    TypeLex id;                 // идентификатор объекта
    TypeObject objType = ObjEmpty;         // тип  объекта
    PrimitiveDataType dataType = UndefinedType; // тип данных
    bool  Const = 0;            // константа
};

class Tree {
private:
    Node* node; // данные таблицы
    Tree* parent, * left, * right; // родитель, левый и правый потомок
public:
    static Scaner* scan;
    static Tree* Cur; // текущий элемент дерева

    Tree(Tree* l, Tree* r, Tree* u, Node* Data);
    Tree(Scaner* scan);

    // необходимые функции  работы с таблицей:
    void SetLeft(Node* Data);
    void SetRight(Node* Data);
    void SetRightT(Tree* node);

    Tree* GetRight();

    Tree* FindRoot();
    Tree* FindUp(Tree* From, TypeLex id);
    Tree* FindUp(TypeLex id);
    Tree* FindUpOneLevel(Tree* From, TypeLex id);
    Tree* FindRightLeft(Tree* From, TypeLex id);
    Tree* FindRightLeft(TypeLex id);

    PrimitiveDataType GetType(int lexType);

    void Print();

    // СЕМАНТИЧЕСКИЕ ПОДПРОГРАММЫ
        // установить текущий узел дерева
    void SetCur(Tree* a);

    //Получить тип объекта
    TypeObject GetObjType(Tree* Addr);
    //Получить тип данных
    PrimitiveDataType GetDataType(Tree* Addr);

    // занесение идентификатора в таблицу
    Tree* SemInclude(TypeLex a, TypeObject ob, PrimitiveDataType t, bool cons);

    // поиск переменных и структур
    Tree* SemFindVar(TypeLex a);
    Tree* SemFindClass(TypeLex a);
    Tree* SemFindClassVar(TypeLex a);

    // результат операции
    PrimitiveDataType GetTypeResult(PrimitiveDataType op1, PrimitiveDataType op2, int operation, TypeLex a);

    // проверка идентификатора а на повторное описание внутри блока
    int DupControl(Tree* Addr, TypeLex a);
};

/*
#include "defs.h"
#include "Scaner.h"

enum TypeObject {
    ObjEmpty = 0,   // пустая вершина
    ObjVar,         // переменная
    ObjClass,      // объект типа класса
    ObjTypeClass,  // тип  «класс» 
    ObjMain         // main
};

enum  PrimitiveDataType {
    UndefinedType = 0,   // для пустой вершины
    IntegerType,
    ShortType,
    LongType,
    FloatType
};
static const char* PrimitiveDataTypeStrings[] = { "undef", "int", "short", "double" };      

struct Node {
    TypeLex id;                 // идентификатор объекта
    TypeObject objType = ObjEmpty;         // тип  объекта
    PrimitiveDataType dataType = UndefinedType; // тип данных
    bool  Const = 0;            // константа
};

class Tree {
private:
    Node* node; // данные таблицы
    Tree* parent, * left, * right; // родитель, левый и правый потомок
public:
    static Scaner* scan;
    static Tree* Cur; // текущий элемент дерева

    Tree(Tree* l, Tree* r, Tree* u, Node* Data);
    Tree(Scaner* scan);

    // необходимые функции  работы с таблицей:
    void SetLeft(Node* Data);
    void SetRight(Node* Data);

    void SetRightT(Tree* node);
    Tree* GetRight();

    Tree* FindRoot();
    Tree* FindUp(Tree* From, TypeLex id);
    Tree* FindUp(TypeLex id);
    Tree* FindUpOneLevel(Tree* From, TypeLex id);
    Tree* FindRightLeft(Tree* From, TypeLex id);
    Tree* FindRightLeft(TypeLex id);

    PrimitiveDataType GetType(int lexType);

    void Print();

    // СЕМАНТИЧЕСКИЕ ПОДПРОГРАММЫ
    // установить текущий узел дерева
    void SetCur(Tree* a);

    // получить значение текущего узла дерева
    Tree* GetCur(void);



    // занесение идентификатора в таблицу
    Tree* SemInclude(TypeLex a, TypeObject ob, PrimitiveDataType t, bool cons);

    //новый уровень (для составного оператора)
    Tree* SemNewLevel();

    // установить тип t для переменной по адресу Addr
    void SemSetType(Tree* Addr, PrimitiveDataType t);
    void SemSetObjType(Tree* Addr, TypeObject t);

    // найти в таблице переменную с именем a
    // и вернуть ссылку на соответствующий элемент дерева
    Tree* SemGetType(TypeLex a);

    // проверка идентификатора а на повторное описание внутри блока
    int DupControl(Tree* Addr, TypeLex a);
};
*/