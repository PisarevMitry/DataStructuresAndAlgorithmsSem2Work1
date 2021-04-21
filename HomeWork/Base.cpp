#include "Base.h"

//������� ������ ���� �� ������ ����� � �����
//�����������: �� ���� ��������� ������ �� ������ ������� ������ � ����� ����������� �����
//�����������: ������� ���������� ������ �� ������ ������� ������ � ������ ������� ����������� �����
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

//������� ������ ������ ����� �������
//�����������: �� ���� ��������� ������ �� ������ ������� ������
//�����������: ������� ������� ������ � ������ �� �����
void print_left(Item* list)
{
	if (list)
	{
		Item* node = list;
		cout << setw(35) << left << "����� ����������� �����" << setw(15) << left << "����" << setw(20) << left << "��� ��������" << setw(25) << left << "�������" << endl;
		while (node)
		{
			printItem(node);
			node = node->next;
		}
	}
	else
	{
		cout << "������ ����" << endl;
	}
}

//������� ������ ������ ������ ������
//�����������: �� ���� ��������� ������ �� ������ ������� ������
//�����������: ������� ������� ������ � ����� �� ������
void print_right(Item* list)
{
	if (list)
	{
		Item* node = list;
		while (node->next != NULL)
		{
			node = node->next;
		}
		cout << setw(35) << left << "����� ����������� �����" << setw(15) << left << "����" << setw(20) << left << "��� ��������" << setw(25) << left << "�������" << endl;
		while (node)
		{
			printItem(node);
			node = node->prev;
		}
	}
	else
	{
		cout << "������ ����" << endl;
	}
}

//������� ������ ������ ����
//�����������: �� ���� ��������� ������ ���� ������
//�����������: ������� ������� �������� ����� ���� � ��������������� ����
void printItem(Item* node)
{
	cout << setw(35) << left << node->account_number << setw(2) << left << node->date.tm_mday << "." << setw(2) << node->date.tm_mon + 1 << "." << setw(9) << node->date.tm_year + 1900 << setw(20) << left << node->type_of_operation << setw(25) << left << node->deposit << endl;
}