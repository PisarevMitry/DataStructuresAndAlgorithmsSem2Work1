#include "Addition.h"

//Максимальное значение нормер банковского счета
long size_of_main_list;

//Указатель на массиив банковских ячеек
long* bank_accounts;

//Функция вставки нового узла перед первым узлом	
//Предусловие: на вход поступает указатель на первый элемент списка и элемент, который необходимо вставить
//Постусловие: функция вставляет элемент в начало списка	
void insertBeforeFirst(Item*& list, Item* node)
{
	if (list)
	{
		node->next = list;
		node->prev = nullptr;
		list = node;
		list->next->prev = list;
	}
	else
	{
		list = node;
		list->next = nullptr;
		list->prev = nullptr;
	}
}

//Функция удаления сведений по счету
//Предусловие: на вход поступает указатель на первый элемент списка
//Постусловие: функция удаляет всех пользователей (все записи о них), у которых общая сумма вклада равна нулю
void deletingAccountInformation(Item*& list)
{
	determiningTotalDeposit(list);
	for (long i = 0;i < size_of_main_list;i++)
	{
		if (bank_accounts[i] <= 0)
		{
			deleteItem(list, i);
		}
	}
}

//Функция создания нового списка с остатками по всем видам операций одного счета из исходного
//Предусловие: на вход поступает указатель на первый элемент списка и номер банковского счета
//Постусловие: функция создает список из всех операций по данному банковскуму счету, изменяет дату в каждом узле на текущую и возвращает указатель на список
Item* createListFromOriginal(Item*& list, int account_number)
{
	if (list == nullptr)
	{
		return nullptr;
	}
	else
	{
		Item* nodeResult = nullptr;
		Item* nodeService1 = list;
		Item* nodeService2;
		Item* nodeService3;
		while (nodeService1)
		{
			nodeService2 = new Item;
			nodeService2 = searchByAccountNumber(nodeService1, account_number);
			nodeService1 = nodeService2->next;
			if (nodeService2)
			{
				nodeService3 = createItem(nodeService2->account_number, nodeService2->date, nodeService2->type_of_operation, nodeService2->deposit);
				changeDate(nodeService3);
				insertBeforeFirst(nodeResult, nodeService3);
			}
		}
		return nodeResult;
	}
}

//Функция создания списка вставкой перед первым узлом
//Предусловие: на вход поступает указатель на первый элемент списка и содержание всех полей узла
//Постусловие: функция добавляет в начало списка новый узел
void createList(Item*& list, int account_number, tm date, string type_of_operation, int deposit)
{
	Item* nodeService = createItem(account_number, date, type_of_operation, deposit);
	insertBeforeFirst(list, nodeService);
}

//Функция создания узла
//Предусловие: на вход поступает содержание всех полей узла
//Постусловие: функция создает новый узел
Item* createItem(int account_number, tm date, string type_of_operation, int deposit)
{
	Item* node = new Item;
	node->account_number = account_number;
	node->date.tm_mday = date.tm_mday;
	node->date.tm_mon = date.tm_mon - 1;
	node->date.tm_year = date.tm_year - 1900;
	node->type_of_operation = type_of_operation;
	node->deposit = deposit;
	node->next = nullptr;
	node->prev = nullptr;
	return node;
}

//Функция подсчета количества уникальных номеров банковских счетов (нахождение максимального номера банковского счета)
//Предусловие: на вход поступает ссылка на первый элемент списка
//Постусловие: функция находит максимальное значение поля (номер банковского счета) среди всех элементов списка и создает глобальный массив данной размерности
void countingNumberAccounts(Item* list)
{
	Item* node = list;
	while (node)
	{
		if (node->account_number > size_of_main_list)
		{
			size_of_main_list = node->account_number;
		}
		node = node->next;
	}
	bank_accounts = new long[size_of_main_list];
	fill(bank_accounts, bank_accounts + size_of_main_list, NULL);
}

//Функции определения общей суммы вклада для каждого счета
//Предусловие: на вход поступает ссылка на первый элемент списка
//Постусловие: функция подсчитывает общий вклад для всех банковских счетов внутри глобального массива за O(1)
void determiningTotalDeposit(Item* list)
{
	countingNumberAccounts(list);
	Item* node = list;
	while (node)
	{
		if (node->type_of_operation == "приход")
		{
			bank_accounts[node->account_number] += node->deposit;
		}
		else
		{
			bank_accounts[node->account_number] -= node->deposit;
		}
		node = node->next;
	}
}

//Функция удаления одного узла
//Предусловие: на вход поступает указатель на первый элемент списка и указатель на узел, который нужно удалить
//Постусловие: функция удаляет узел
void deleteItem(Item*& list, Item* node)
{
	if (node != list)
		node->prev->next = node->next;
	if (node->next != nullptr)
		node->next->prev = node->prev;
	if (node == list && node->next == nullptr)
		list = nullptr;
	if (node == list && node->next != nullptr)
	{
		list = list->next;
		list->prev = nullptr;
	}
	delete node;
}

//Функция удаления всех узлов с заданным номером банковского счета
//Предусловие: на вход поступает указатель на первый элемент списка и номер банковского счета, для которого нужно удалить все элементы
//Постусловие: функция удаляет все узлы, у которых поле account_number совпадает с параметром
void deleteItem(Item*& list, int account_number) {
	if (list == nullptr)
	{
		return;
	}
	else
	{
		Item* node = list;
		while (node) {
			Item nodeService = *node;
			if (node->account_number == account_number) {
				deleteItem(list, node);
			}
			node = nodeService.next;
		}
	}
}

//Функция изменения даты
//Предусловие: на вход поступает указатель на узел
//Постусловие: функция изменяет поле (дата) на значение текущей даты
void changeDate(Item* node)
{
	time_t t = time(nullptr);
	node->date = *std::localtime(&t);
}
