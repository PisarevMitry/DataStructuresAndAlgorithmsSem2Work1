#include "main.h"

//Функция вывода меню
void menu() {
	cout << "Список операций с двунапраленным списком:" << endl << endl << "1. Вставить новый узел перед первым узлом" << endl << "2. Вывести список слева направо" << endl << "3. Вывести список справа налево" << endl << "4. Найти элемент по номеру счета в банке" << endl << "5. Удалить все сведения по одному счету" << endl << "6. Создать новый список с остатками по всем видам операций одного счета из исходного" << endl << "7. Выйти" << endl;
}

//Функция автоматического тестирования программы
void automaticTest() {

	Item* list = nullptr;
	int n = -1;
	int account_number;
	tm date;
	string type_of_operation;
	int deposit;

	cout << "Скопируйте и вставьте входные параметры:\n1 12 01 2008 приход 300\n1 11 01 2009 расход 300\n1 10 03 2006 приход 800\n2 08 04 2009 приход 300\n3 06 12 2009 приход 403\n5 02 01 2014 приход 1020\n5 02 01 2014 приход 1020\n8 01 07 2015 приход 300\n1 04 03 2009 расход 800\n2 07 08 2013 расход 300\n9 08 11 1990 приход 10\n7 01 10 2002 приход 300\n5 02 01 2014 расход 100" << endl;
	for (int i = 0;i < 13;i++)
	{
		cin >> account_number >> date.tm_mday >> date.tm_mon >> date.tm_year >> type_of_operation >> deposit;
		createList(list, account_number, date, type_of_operation, deposit);
	}

	//набор данных для теста (вставить в консоль)
		/*1 12 01 2008 приход 300
		1 11 01 2009 расход 300
		1 10 03 2006 приход 800
		2 08 04 2009 приход 300
		3 06 12 2009 приход 403
		5 02 01 2014 приход 1020
		5 02 01 2014 приход 1020
		8 01 07 2015 приход 300
		1 04 03 2009 расход 800
		2 07 08 2013 расход 300
		9 08 11 1990 приход 10
		7 01 10 2002 приход 300
		5 02 01 2014 расход 100*/

	cout << "Список в начале (вывод с начала до конца): " << endl;
	print_left(list);
	cout << "Список в начале (вывод с конца до начала): " << endl;
	print_right(list);
	cout << "Последняя операция по банковскому счету номер 1: " << endl;
	printItem(searchByAccountNumber(list, 1));
	cout << "Список после того, как в него добавили один узел: " << endl;
	date.tm_mday = 2;
	date.tm_mon = 1;
	date.tm_year = 2014;
	createList(list, 5, date, "расход", 100);
	print_left(list);
	cout << "Список всех операций по банковскому счету 1: " << endl;
	print_left(createListFromOriginal(list, 1));
	cout << "Список после того, как удалили данные о счетах с сумарным вкладом равным нулю: " << endl;
	deletingAccountInformation(list);
	print_left(list);
}

//Функция ручного тестирования программы
void manualTest()
{
	Item* list = nullptr;
	int n = -1;
	int k;
	int account_number;
	tm date;
	string type_of_operation;
	int deposit;

	menu();

	while (n != 0) {
		cout << "Введите номер действия:" << endl;
		cin >> n;
		switch (n) {
		case 1:
		{
			cout << "Введите значения полей узла, который хотите создать, в формате: номер банковского счета, дата (в формате ДД ММ ГГГГ через пробелы), тип операции (приход/расход), депозит." << endl;
			cin >> account_number >> date.tm_mday >> date.tm_mon >> date.tm_year >> type_of_operation >> deposit;
			createList(list, account_number, date, type_of_operation, deposit);
		}
		break;
		case 2:
		{
			print_left(list);
		}
		break;
		case 3:
		{
			print_right(list);
		}
		break;
		case 4:
		{
			cout << "Введите номер счета в банке, последнюю операцию по которому вы хотите посмотреть: ";
			cin >> account_number;
			printItem(searchByAccountNumber(list, account_number));
		}
		break;
		case 5:
		{
			deletingAccountInformation(list);
			cout << "Данные о счетах с сумарным депозитом равным нулю - удалены." << endl;
		}
		break;
		case 6:
		{
			cout << "Введите номер счета в банке, для которого вы хотите посмотреть все операции: ";
			cin >> account_number;
			print_left(createListFromOriginal(list, account_number));
		}
		break;
		case 7:
		{
			return;
			delete list;
		}
		break;
		default:
			cout << "Ошибка" << endl;
			break;
		}
	}
}

//Главная функция программы
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	cout << "Для ручного тестирования введите 1, для автоматического тестирования введите 2:" << endl;
	int k;
	cin >> k;
	switch (k) {
	case 1:
	{
		manualTest();
	}
	break;
	case 2:
	{
		automaticTest();
	}
	break;
	default:
		cout << "Ошибка" << endl;
		break;
	}
}