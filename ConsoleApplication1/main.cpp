#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

/*На логическим уровне разрабатываемая структура данных представляет собой обычную линейную последовательность
элементов (например, строк) со стандартным набором операций (добавление в конец, вставка и удаление по логическому номеру,
сортировка, бинарный поиск, вставка с сохранением порядка, сохранение и загрузка из текстового файла, выравнивание
(балансировка - выравнивание размерностей структур данных нижнего уровня). Физическая структура данных имеет два уровня.

На нижнем уровне поддерживается ограничение размерности структуры данных: при переполнении она разбивается пополам,
соответствующие изменения вносятся в верхний уровень. При выполнении работы произвести измерение зависимости «грязного»
времени работы программы и ее трудоемкости (количества базовых операций). Оценить вид полученной
зависимости (линейно-логарифмическая, квадратичная).

Список - каждый элемент является заголовком односвязного списка. Элемент списка второго уровня содержит
указатель на строку. (Включение элемента последним в список производить с учетом
выравнивания длины текущего и следующего списков).*/

const int countMenuItem1 = 12;
const char * menu1[countMenuItem1] = {
	//{"0.Show List of List"},
	{ "1.Clear and Input new List from keyboard" },
	{ "2.Clear and Load List from file" },
	{ "3.Search string in the List" },
	{ "4.Save DataBase to file" },
	{ "5.Balancing" },					//
	{ "6.Insert by indx" },				//
	{ "7.Insert to sort List" },			//не реализовано
	{ "8.Delete by indx" },				//не реализовано
	{ "9.Sort" },
	{ "10.Testing..." },					//не реализовано
	{ "11.Save and exit" },
	{ "12.Exit without saving" } };
const int countMenuItem0 = 3;
const char * menu0[countMenuItem0] = { { "1.Input new List from keyboard" },{ "2.Load from file" },{ "3.Exit" } };

void main()
{
	printMenu(menu0, countMenuItem0);
	FirstList * head = creatHeadFirstList();

	switch (choiseFrom(countMenuItem0))
	{
	case 1:		//1.Input new List from keyboard
		secondFillFirstList(head);
		break;
	case 2:		//2.Load from file
		loadFromFile(head);
		break;
	case -1:	//3.Exit
		return;
	}
	int isExit = 0;
	int isSort = 0;
	while (!isExit)
	{
		//system("cls");
		showFirstList(head);
		printMenu(menu1, countMenuItem1);

		FirstList *tmpFirstList;
		SecondList * tmpSecList;
		SecondList *tmpElem;
		int numb;
		char *tmp;
		int maxIndx, indx, isSuccess;


		switch (choiseFrom(countMenuItem1))
		{
		case 1:		//Clear and Input new List from keyboard
			clearFirstList(head);
			head = creatHeadFirstList();
			secondFillFirstList(head);
			break;
		case 2:		//2.Clear and Load List from file
			clearFirstList(head);
			head = creatHeadFirstList();
			loadFromFile(head);
			break;
		case 3:		//3.Search string in the List
			printf("Please input serching String?\n>>>");
			tmp = getInput();
			tmpSecList = findString(head, tmp);
			printf("Result is:\n");
			//showSecondList(tmpSecList);
			if (tmpSecList != NULL)
				printf("indx = %d, string \"%s\"\n", tmpSecList->indx, tmpSecList->content);
			else
				printf("No one finding...\n");
			system("pause");
			free(tmp);
			break;
		case 4:		//4.Save DataBase to file
			saveToFile(head);
			break;
		case 5:		//5.Balancing
			tmpFirstList = balance(head);
			clearFirstList(head);
			head = tmpFirstList;
			isSort = 0;
			break;
		case 6:		//6.Insert by indx

			printf("Input indx and string\n");
			scanf("%d", &numb);
			tmpElem = creatElemSecondList();
			if (tmpElem == NULL)
			{
				printf("Sorry, you input wrong string...");
				system("pause");
				break;
			}
			inputByNumber(head, tmpElem, numb);
			refreshIndex(head);
			isSort = 0;
			break;
		case 7:		//7.Insert to sort List
			if (isSort == 1)
			{
				printf("Input the new string (Element of List)\n");
				tmpSecList = creatElemSecondList();
				if (tmpSecList != NULL)
				{
					int numb = findIndexOfInput(head, tmpSecList);
					inputByNumber(head, tmpSecList, numb);
					refreshIndex(head);
				}
			}
			else
			{
				printf("Your list is not sort. Please sort the List and try again.");
				system("pause");
			}
			break;
		case 8:		//8.Delete by indx
			printf("Please input indx of deleting Element?\n");
			maxIndx = getcountsAllOfSecList(head);
			indx = getNumber(0, maxIndx);
			isSuccess = delByIndex(head, indx);
			if (isSuccess == -1)	// для отладки
			{
				printf("BAD NEWS... Do not delete...\n");
			}

			system("pause");
			break;
		case 9:		//9.Sort

			tmpFirstList = creatSortOfFirstList(head);
			clearFirstList(head);
			head = tmpFirstList;
			isSort = 1;
			break;
		case 10:	//10.Testing
			testing();
			break;
		case 11:	//11.Save and exit
			saveToFile(head);
			isExit = 1;
			break;
		case -1:	//12.Exit without saving
			isExit = 1;
			break;
		}
	}

	system("pause");
}