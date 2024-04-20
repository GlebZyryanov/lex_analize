#include "defs.h"
#include "Semant.h"

#define max(a,b) a<b? b : a


// конструктор создает новый узел с пустыми связями и данными
Tree::Tree(Scaner* scan) {
	this->scan = scan;

	node = new Node();
	node->objType = ObjEmpty;
	node->dataType = UndefinedType;


	parent = NULL;
	left = NULL;
	right = NULL;

	Cur = this;
}

// конструктор создает узел с заданными связями и данными
Tree::Tree(Tree* l, Tree* r, Tree* u, Node* d) {
	node = new Node();

	parent = u; left = l; right = r; // установили ссылки

	memcpy(node, d, sizeof(Node)); // установили данные
}

// создать левого потомка от текущей вершины this
void Tree::SetLeft(Node* Data) {
	left = new Tree(NULL, NULL, this, Data);
}

// создать правого потомка от текущей вершины this
void Tree::SetRight(Node* Data) {
	Tree* a = new Tree(NULL, NULL, this, Data); // новая вершина
	right = a; // связали this с новой вершиной
}

void Tree::SetRightT(Tree* node) {
	right = node;
}

Tree* Tree::GetRight() {
	return right;
}

Tree* Tree::FindRoot()
{
	Tree* i = Cur;

	while ((i != NULL) && (i->parent != NULL))
		i = i->parent;

	return i;
}

// поиск данных в дереве, начиная от текущей вершины this
// до его корня вверх по связям
Tree* Tree::FindUp(TypeLex id) {
	return FindUp(this, id);
}

// поиск данных в дереве от заданной вершины From
// до его корня вверх по связям
Tree* Tree::FindUp(Tree* From, TypeLex id) {
	Tree* i = From; // текущая вершина поиска
	while ((i != NULL) &&
		(memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) != 0))
		i = i->parent; // поднимаемся наверх по связям
	return i;
}

// поиск прямых потомков текущей вершины this
Tree* Tree::FindRightLeft(TypeLex id) {
	return FindRightLeft(this, id);
}

// поиск прямых потомков заданной вершины From
Tree* Tree::FindRightLeft(Tree* From, TypeLex id) {
	Tree* i = From->right; // текущая вершина поиска
	while ((i != NULL) &&
		(memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) != 0))
		i = i->left;
	// обходим только соседей по левым связям
	return i;
}

Tree* Tree::FindUpOneLevel(Tree* From, TypeLex id)
// Поиск элемента id вверх по дереву от текущей вершины From.
// Поиск осуществляется на одном уровне вложенности по левым связям
{
	Tree* i = From; // текущая вершина поиска
	while ((i != NULL) && (i->parent == NULL || i->parent->right != i))
	{
		if (memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) == 0)
			return i; // нaшли совпадающий идентификатор
		i = i->parent; // поднимаемся наверх по связям
	}
	return NULL;
}

// отладочная программа печати дерева
void Tree::Print()
{
	if (node->objType != ObjEmpty)
		printf("    %-15s  ---->", node->id);
	else
		printf("    ПУСТАЯ            ---->");

	if (left != NULL)
	{
		if (left->node->objType != ObjEmpty)
			printf("      слева находится %s", left->node->id);
		else
			printf("      слева ПУСТАЯ");
	}


	if (right != NULL)
	{
		if (right->node->objType != ObjEmpty)
			printf("      справа находится %s", right->node->id);
		else
			printf("      справа ПУСТАЯ");
	}

	printf("\n");

	if (left != NULL)
		left->Print();

	if (right != NULL)
	{
		printf("\n\nРОДИТЕЛЬ: ");
		if (node->objType != ObjEmpty)
			printf("Вершина это %s\n", node->id);
		else
			printf("Вершина ПУСТАЯ\n");
		right->Print();
	}
}