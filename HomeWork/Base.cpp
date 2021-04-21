#include "Base.h"

//Функция поиска узла по номеру счета в банке
//Предусловие: на вход поступает ссылка на первый элемент списка и номер банковского счета
//Постусловие: функция возвращает ссылку на первый элемент списка с данным номером банковского счета
Item* searchByAccountNumber(Item* list, int account_number)
{
	Item* node = list;
	while (node)
	{
		if (node->account_number == account_number)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

//Функция вывода списка слева направо
//Предусловие: на вход поступает ссылка на первый элемент списка
//Постусловие: функция выводит список с начала до конца
void print_left(Item* list)
{
	if (list)
	{
		Item* node = list;
		cout << setw(35) << left << "Номер банковского счета" << setw(15) << left << "Дата" << setw(20) << left << "Тип операции" << setw(25) << left << "Депозит" << endl;
		while (node)
		{
			printItem(node);
			node = node->next;
		}
	}
	else
	{
		cout << "Список пуст" << endl;
	}
}

//Функция вывода списка справа налево
//Предусловие: на вход поступает ссылка на первый элемент списка
//Постусловие: функция выводит список с конца до начала
void print_right(Item* list)
{
	if (list)
	{
		Item* node = list;
		while (node->next != NULL)
		{
			node = node->next;
		}
		cout << setw(35) << left << "Номер банковского счета" << setw(15) << left << "Дата" << setw(20) << left << "Тип операции" << setw(25) << left << "Депозит" << endl;
		while (node)
		{
			printItem(node);
			node = node->prev;
		}
	}
	else
	{
		cout << "Список пуст" << endl;
	}
}

//Функция вывода одного узла
//Предусловие: на вход поступает ссылка узел списка
//Постусловие: функция выводит значений полей узла в форматированном виде
void printItem(Item* node)
{
	cout << setw(35) << left << node->account_number << setw(2) << left << node->date.tm_mday << "." << setw(2) << node->date.tm_mon + 1 << "." << setw(9) << node->date.tm_year + 1900 << setw(20) << left << node->type_of_operation << setw(25) << left << node->deposit << endl;
}