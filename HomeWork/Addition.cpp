#include "Addition.h"

//������������ �������� ������ ����������� �����
long size_of_main_list;

//��������� �� ������� ���������� �����
long* bank_accounts;

//������� ������� ������ ���� ����� ������ �����	
//�����������: �� ���� ��������� ��������� �� ������ ������� ������ � �������, ������� ���������� ��������
//�����������: ������� ��������� ������� � ������ ������	
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

//������� �������� �������� �� �����
//�����������: �� ���� ��������� ��������� �� ������ ������� ������
//�����������: ������� ������� ���� ������������� (��� ������ � ���), � ������� ����� ����� ������ ����� ����
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

//������� �������� ������ ������ � ��������� �� ���� ����� �������� ������ ����� �� ���������
//�����������: �� ���� ��������� ��������� �� ������ ������� ������ � ����� ����������� �����
//�����������: ������� ������� ������ �� ���� �������� �� ������� ����������� �����, �������� ���� � ������ ���� �� ������� � ���������� ��������� �� ������
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

//������� �������� ������ �������� ����� ������ �����
//�����������: �� ���� ��������� ��������� �� ������ ������� ������ � ���������� ���� ����� ����
//�����������: ������� ��������� � ������ ������ ����� ����
void createList(Item*& list, int account_number, tm date, string type_of_operation, int deposit)
{
	Item* nodeService = createItem(account_number, date, type_of_operation, deposit);
	insertBeforeFirst(list, nodeService);
}

//������� �������� ����
//�����������: �� ���� ��������� ���������� ���� ����� ����
//�����������: ������� ������� ����� ����
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

//������� �������� ���������� ���������� ������� ���������� ������ (���������� ������������� ������ ����������� �����)
//�����������: �� ���� ��������� ������ �� ������ ������� ������
//�����������: ������� ������� ������������ �������� ���� (����� ����������� �����) ����� ���� ��������� ������ � ������� ���������� ������ ������ �����������
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

//������� ����������� ����� ����� ������ ��� ������� �����
//�����������: �� ���� ��������� ������ �� ������ ������� ������
//�����������: ������� ������������ ����� ����� ��� ���� ���������� ������ ������ ����������� ������� �� O(1)
void determiningTotalDeposit(Item* list)
{
	countingNumberAccounts(list);
	Item* node = list;
	while (node)
	{
		if (node->type_of_operation == "������")
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

//������� �������� ������ ����
//�����������: �� ���� ��������� ��������� �� ������ ������� ������ � ��������� �� ����, ������� ����� �������
//�����������: ������� ������� ����
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

//������� �������� ���� ����� � �������� ������� ����������� �����
//�����������: �� ���� ��������� ��������� �� ������ ������� ������ � ����� ����������� �����, ��� �������� ����� ������� ��� ��������
//�����������: ������� ������� ��� ����, � ������� ���� account_number ��������� � ����������
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

//������� ��������� ����
//�����������: �� ���� ��������� ��������� �� ����
//�����������: ������� �������� ���� (����) �� �������� ������� ����
void changeDate(Item* node)
{
	time_t t = time(nullptr);
	node->date = *std::localtime(&t);
}
