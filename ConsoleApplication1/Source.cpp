#define _CRT_SECURE_NO_WARNINGS
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

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

struct SecondList
{
	SecondList * next;
	char * content;
	int indx;
};
struct FirstList
{
	FirstList * next;
	FirstList * prev;
	SecondList * headOFSecondList;
	//static int counts;
	int contain;
	int max;
};

FirstList * creatHeadFirstList(); /*	функция возвращает указатель на память выделенную под созданный первый элемент списка первого уровня
										в этой функции мы выделяем память только под элемент первого уровня. 
										Ссылку на элемент второго уровня заNULLяем. Также ссылки на следущий и предыдущий элемент также 
										приравниваем к NULL*/
FirstList * creatFirstList();		/*	функция выделяет память под очередной элемент списка первого уровня и возвращает указатель на него*/
FirstList * addToTailOfLists(FirstList * headFistList, SecondList * paste); /*добавляет элемент в конец списка списков
																			возвращает указатель на новый хвост*/
FirstList * findPtrFirstListForInput(FirstList * head, int &number); //возвращает указатель на элемент списка первого уровня по номеру для вставки
FirstList * findPtrFirstListForDel(FirstList * head, int &number);	/*Возвращает указатель на элемент списка перовго уровня по номеру для удаления*/
FirstList * divisionFirstList(FirstList * head);//делит на два и возвращает указатель на второй
FirstList * creatSortOfFirstList(FirstList * head);	/*создет новый список списков и используя сортировку вставкой
													(из первого списка во второй) сортирует данные первого списка*/
FirstList * balance(FirstList*);	/*Балансировка*/
SecondList * creatElemSecondList();				/*	функция выделяет память под элемент типа SecondList и заполняет его*/
SecondList * creatElemSecListEmpty();	/*создает элемент и выделяет под него память с инициализаторами по умолчанию (пустой)*/
SecondList * copySecondList(SecondList *Elem);// создает указатель на новый элемент скопированный из Elem
SecondList * findString(FirstList *, char * string);	/*Поиск по списку списков*/
void addToSecondList(SecondList * head, SecondList* paste);	// функция добавляет к (СУЩЕСТВУЮЩЕМУ ЭЛЕМЕНТУ) списку второго уровня элемент в конец списка.
void fillSecondList(SecondList * headOfSecondList, bool &isBreak);	/*	функция получает на вход указатель на заголовок списка второго уровня и и ссылку на переменную-флаг указывающую на
												то, что последнее введенное слово было "exit", а значит нужно прекратить ввод. Заполняет список. 
												Подразумевается, что по указателю который передается уже была выделена память ранее.*/
void secondFillFirstList(FirstList * headOfFirstList);// используя fillSecondList() функция заполняет работает на уровне первого списка.
void showFirstList(FirstList*head);	// выводит на экран список первого уровня используя в цикле функцию вывода списка второго уровня
void showSecondList(SecondList*head);	/*	выводит на экран список второго уровня, в качестве аргумента принимает заголовок */
void showOneFirstList(FirstList * head);
bool isExit(const char *);	// проверяет передаваемую строку на совпадение со словом "exit"
void inputByNumber(FirstList * head, SecondList * paste, int numb);
int delByIndex(FirstList * &, int);		//удаляет из списка списков элемент по индексу
int getcountsAllOfSecList(FirstList * head);	//считает общее количество элементов второго уровня
int getCountAllOfFirstList(FirstList * head);	// считает количество элементов первого уровня
void refreshIndex(FirstList * head);//обновляет индексы
void saveToFile(FirstList * head); // записывает текущее состояние в файл
void loadFromFile(FirstList * head);//загружает предыдущее состояние из файла
int findIndexOfInput(FirstList * head, SecondList *); //ищет индекс вставки по сортированному списку списков
int compare(SecondList*, SecondList*); /*сравнивает содержание двух элементов второго уровня*/
void clearSecondList(SecondList *);	/*Рекурсивно очищает память из под списка второго уровня*/
void clearFirstList(FirstList*);	/*Очистка списка*/
bool isEqual(SecondList * elem, char * c);	/*сравнивает содержимое текущего элемента и указатель на строку*/

//////////////////ПРОТОТИПЫ СЛУЖЕБНЫХ ФУНКЦИЙ///////////////////////////////
const int countMenuItem1 = 12;
const char * menu1[countMenuItem1] = {	
							//{"0.Show List of List"},
							{"1.Clear and Input new List from keyboard"},
							{"2.Clear and Load List from file"},
							{"3.Search string in the List"},
							{"4.Save DataBase to file"},
							{"5.Balancing"},					//
							{"6.Insert by indx"},				//
							{"7.Insert to sort List"},			//не реализовано
							{"8.Delete by indx"},				//не реализовано
							{"9.Sort"},
							{"10.Testing..."},					//не реализовано
							{"11.Save and exit"},
							{"12.Exit without saving"} };
const int countMenuItem0 = 3;
const char * menu0[countMenuItem0] = { {"1.Input new List from keyboard"}, {"2.Load from file"}, {"3.Exit"} };
void printMenu(const char **, int);
int choiseFrom(int counOfChoise);
int getNumber(int, int);
char * getInput();	// функция считывает со строки консоли строку и возвращает указатель на нее в качестве результата
void printTheFile();
void testing();
	
/////////////////////////////////////////////////////////////////////////////
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
		printMenu(menu1,countMenuItem1);

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
/////////////////////////////////////////////////////////////////////////////
FirstList * creatHeadFirstList()
{
	FirstList * head = (FirstList*)malloc(sizeof(FirstList));
	head->next = head->prev = NULL;
	head->headOFSecondList = NULL;
	head->contain = 0;
	head->max = 5;
		
	return head;
}
FirstList * creatFirstList()
{
	FirstList * tmp = (FirstList*)malloc(sizeof(FirstList));
	tmp->headOFSecondList = NULL;
	tmp->next = tmp->prev = NULL;
	tmp->contain = 0;
	tmp->max = 5;
	return tmp;
}
FirstList * addToTailOfLists(FirstList * TailFirstList, SecondList * paste)
{
	FirstList * tail = TailFirstList;

	if ((tail->contain + 1) > tail->max)
	{
		tail->next = creatFirstList();
		tail->next->prev = tail;

		//алгоритм добавления новогого элемента FirstList с разделением составляющих на два
		int half = tail->contain / 2;

		SecondList * tmph = tail->headOFSecondList;
		for (int i = half - 1; i > 0; i--)
			tmph = tmph->next;

		tail->next->headOFSecondList = tmph->next;
		tmph->next = NULL;	//

		tail->next->contain = tail->contain / 2 + tail->contain % 2;
		tail->contain = half;


		tail = tail->next;

	}
	if (tail->contain == 0)
	{
		tail->headOFSecondList = paste;
		tail->contain++;

	}
	else
	{
		SecondList * tmp;
		for (tmp = tail->headOFSecondList; tmp->next != NULL; tmp = tmp->next);
		tmp->next = paste;

		tail->contain++;
	}
	return tail;
}
FirstList * findPtrFirstListForInput(FirstList * head, int &number)
{
	FirstList * tmp;
	tmp = head;

	for (; tmp->next != NULL; tmp = tmp->next)
	{
		if (number <= tmp->contain)
			break;
		number -= tmp->contain;
	}
	return tmp;
}
FirstList * findPtrFirstListForDel(FirstList * head, int &number)
{
	FirstList * tmp;							//заводим временный указатель и устанавливаем его на начало
	tmp = head;									//
	for (; tmp->next != NULL; tmp = tmp->next)	//пробегаем в цикле до искомого места
	{
		if (number < tmp->contain)
			break;
		number -= tmp->contain;					//каждый раз от индекса будем отнимать количество содержащихся 
												//элементов в каждом из списков первого уровня
												//т.о. получим указатель на необходимый элемент и индекс относительно этого списка
	}
	return tmp;
}
FirstList * divisionFirstList(FirstList * head)
{
	//создаем новый элемент типа FirstList
	FirstList * tail;
	tail = creatFirstList();
	if (head->next != NULL)
	{
		tail->next = head->next;
		tail->prev = head;
		head->next->prev = tail;
		head->next = tail;

		//приводим в соответсвие связанные с ними данные

		int half = head->contain / 2;
		SecondList * tmp = head->headOFSecondList;
		for (int i = half - 1; i > 0; i--)
			tmp = tmp->next;

		head->next->headOFSecondList = tmp->next;
		tmp->next = NULL;

		head->next->contain = head->contain / 2 + head->contain % 2;
		head->contain = half;
	}
	else
	{
		tail->prev = head;
		head->next = tail;

		//Заводим указатель, и ставим его на середину существующего списка
		int half = head->contain / 2;
		SecondList * tmp = head->headOFSecondList;
		for (int i = half - 1; i > 0; i--)
			tmp = tmp->next;

		tail->headOFSecondList = tmp->next;
		tmp->next = NULL;
		tail->contain = half + head->contain % 2;
		head->contain = half;

	}

	return tail;
}
FirstList * creatSortOfFirstList(FirstList * head)
{
	FirstList * headNew;
	headNew = creatHeadFirstList();
	//int countNew;
	for (FirstList * currentFirstList = head; currentFirstList != NULL; currentFirstList = currentFirstList->next)
	{
		for (SecondList * currentSecList = currentFirstList->headOFSecondList; currentSecList != NULL; currentSecList = currentSecList->next)
		{
			int numb = findIndexOfInput(headNew, currentSecList);
			printf("Input\"%s\" by indx = %d\n", currentSecList->content, numb);
			SecondList * tmp = copySecondList(currentSecList);

			inputByNumber(headNew, tmp, numb);
			printf("read \"%s\" complite!\n", tmp->content);

		}
	}
	refreshIndex(headNew);
	return headNew;
}
FirstList * balance(FirstList*head)
{
	FirstList * headPtr, *newHead, *newHeadPtr;
	headPtr = head;
	newHead = creatHeadFirstList();
	newHeadPtr = newHead;
	int a = getcountsAllOfSecList(headPtr);
	int b = getCountAllOfFirstList(headPtr);
	int average = a / b;
	int residue = a % b;
	int x = 0;//счетчик количества текущих вставок (для того чтобы знать кодга переходить к сл.элементу первого уровня)
	int y = 0;//счетчик количества всех вставок (для отлова конца)
	for (headPtr; headPtr != NULL; headPtr = headPtr->next)
	{
		for (SecondList * current = headPtr->headOFSecondList; current != NULL; current = current->next)
		{
			addToTailOfLists(newHeadPtr, copySecondList(current));
			x++;	//увеличиваем счетчик количества текущих вставок
			y++;	//увеличиваем счетчик количества всех вставок

			if (residue > 0)
			{
				if (x == average + 1)	//заполнили необходимое количество
				{
					newHeadPtr->next = creatFirstList();	//создаем новый элемент первого уровня

					newHeadPtr->next->prev = newHeadPtr;	//приводим его в соответствие

					newHeadPtr = newHeadPtr->next;//перемещаем указатель на него

					x = 0;//обнуляем счетчик количества вставок

					residue--;//уменьшаем residue на 1
				}
			}
			else
			{
				if (y == a)
				{
					break;
				}
				if (x == average)	//заполнили необходимое количество
				{
					newHeadPtr->next = creatFirstList();	//создаем новый элемент первого уровня

					newHeadPtr->next->prev = newHeadPtr;	//приводим его в соответствие

					newHeadPtr = newHeadPtr->next;	//перемщаем указатель на него

					x = 0;	//обнуляем счетчик количества вставок
				}
			}
		}
	}
	return newHead;
}
SecondList * creatElemSecondList()
{
	printf(">>>");//Please, input the element of Secondary List?\n
	char *tmpc = getInput();
	if (isExit(tmpc)) // если введен exit то выделяьт память и инициализировать новый элемент структуры не нужно.
		return NULL;
	SecondList *tmp = (SecondList*)malloc(sizeof(SecondList)); //выделяем память под элемент списка второго уровня
	tmp->content = tmpc;
	tmp->next=NULL;
	return tmp;
}
SecondList * creatElemSecListEmpty()
{
	char c[] = { "<empty element>" };
	SecondList *tmp = (SecondList*)malloc(sizeof(SecondList));
	tmp->content = (char*)malloc(sizeof(char)*(strlen(c) + 1));
	strcpy(tmp->content,c);
	tmp->next = NULL;
	return tmp;
}
SecondList * creatCleanElemSecList() 
{
	SecondList *tmp = (SecondList*)malloc(sizeof(SecondList));
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->indx = NULL;
	return tmp;
}
SecondList * copySecondList(SecondList *Elem)
{
	SecondList * tmp;
	tmp = (SecondList*)malloc(sizeof(SecondList));
	int bufsize = (strlen(Elem->content) + 1);
	tmp->content = (char *)malloc(sizeof(char)*bufsize);
	strcpy(tmp->content, Elem->content);
	//tmp->content = Elem->content;
	tmp->indx = Elem->indx;
	tmp->next = NULL;
	return tmp;
}
SecondList * findString(FirstList *head, char * string)
{
	SecondList *tmp = NULL;
	printf("Searching...\nRESULT:\n");
	for (FirstList * currentFirstList = head; currentFirstList != NULL; currentFirstList = currentFirstList->next)
	{
		for (SecondList * currentSecList = currentFirstList->headOFSecondList; currentSecList != NULL; currentSecList = currentSecList->next)
		{
			if (isEqual(currentSecList, string))
			{
				tmp = currentSecList;
				//showSecondList(currentSecList);
				//
			}
		}
	}

	return tmp;
}

void addToSecondList(SecondList * head, SecondList* paste)
{
	SecondList * current;															//создаем указатель на заголовок
	
	for (current = head; current->next != NULL; current = current->next);	//передвигаем указатель пока следующий после текущего элемент не будет ссылаться на NULL
	
	current->next = paste;													//копируем в указатель на следующий элемент (который ранее указывал на NULL) текущий элемент
}
void fillSecondList(SecondList * headOfSecondList, bool &isBreak)
{
	int i = 0;	//создаем счетчик
	SecondList * start = headOfSecondList;	//создаем указатель на заголовок
							
	printf("Please, input the title element of Secondary List?\n>>>");
	start->content = getInput();//считываем первый элемент(заголовок)
	i++;
	while (true)
	{	
		int isExit = 0;							//
		//printf("Continue input?Y(1)/N(0)\n");	// условие выхода из цикла заполнения
		//scanf("%d", &isExit);					//
		if (i > 3)						//
			break;								//

		SecondList * tmp = creatElemSecondList();
		if (tmp == NULL)
		{
			isBreak = true;
			break;
		}
		start->next = tmp;
		start = start->next;

		i++;
	}

}
void secondFillFirstList(FirstList * headOfFirstList)
{
	int i = 0;
	FirstList * tail = headOfFirstList;
	bool isBreak = false;
	while (true)
	{
		SecondList * tmp = creatElemSecondList();
		if (tmp == NULL)
		{
			isBreak = true;
			break;
		}
		else
		{
			tmp->indx = i;
			tail = addToTailOfLists(tail,tmp);
		}
		i++;
	}
}
void showFirstList(FirstList*head)
{
	int i = 0;
	printf("--------LIST------------------------------------------\n");
	printf("AllCount = %d\n", getcountsAllOfSecList(head));
	for (FirstList * current = head; current != NULL; current = current->next, i++)
	{
		printf("%dst contain = %d:\n", i, current->contain);
		showSecondList(current->headOFSecondList);
		printf("\n");
	}
}
void showSecondList(SecondList*head)
{
	for (SecondList * current = head; current != NULL; current = current->next)
	{
		//printf("%dst element of Secondary List (SecondList) is: %s\n",current->indx, current->content);
		printf(" [%s] ->", current->content);
	}
}
void showOneFirstList(FirstList * head)
{
	printf("Output elemnts of FirstList:\n");
	showSecondList(head->headOFSecondList);
}
bool isExit(const char * s)
{
	char exit[] = {"exit"};
	int len = strlen(s)+1;
	if ( len!= 5)
		return false;
	int i = 0;
	for (; s[i] != '\0'; i++)
	{
		if (s[i] != exit[i])
			break;
	}
	if (i == 4)
		return true;
	else
		return false;
}
void inputByNumber(FirstList * head, SecondList * paste, int numb)
{
	int countAllOfSecList = getcountsAllOfSecList(head);	// Завели переменную хранящую количество элементов в списке списков
	
	if (numb >= countAllOfSecList)							// захотели вставить элемент в самый конец
	{
		FirstList * tailPtr;// заводим указатель и устанавливаем его на заголовок первого уровня
		tailPtr = head;
		for (; tailPtr->next != NULL; tailPtr = tailPtr->next);//находим хвостовой элемент первого списка
		addToTailOfLists(tailPtr, paste);
	}
	
	else
	{
		//не в конец списка
		FirstList * FLptr;
		FLptr = findPtrFirstListForInput(head, numb);
		
		if (numb == FLptr->contain)	//проверяем индекс на его принадлежность концу списка второстепенных элементов
		{
			if (FLptr->next != NULL)
			{
				// проверяем длинну следующего списка, если она меньше текущего то вставляем в начало следующего
				if (FLptr->contain > FLptr->next->contain)
				{
					//если длинна следующего меньше текущего
					paste->next = FLptr->next->headOFSecondList; // устанавливаем указатель на след элемент на заголовок
					FLptr->next->headOFSecondList = paste;	//в качестве нового заголовка устанавливаем вставляемый элемент
					FLptr->next->contain++;
				}
				else
				{
					//проверяем на возможность "безболезненной" вставки
					if (FLptr->contain < FLptr->max)
					{
						addToTailOfLists(FLptr, paste);
					}
					else
					{
						FLptr = divisionFirstList(FLptr);//делим елемент на 2 новых элемента...
						addToTailOfLists(FLptr, paste);	//и вставляем элемент в конец
					}
				}
			}
			else
			{
				addToTailOfLists(FLptr, paste); //этого не может быть но все же...
				printf("WOWOWOWOWOWOWOW\nWOWOWOWOWOW\nWOWOWOWOWOWOW\n\n");
			}
			//
		}
		else
		{
			//вставка не в конец списка...
			if (FLptr->contain + 1 > FLptr->max)//если  при вставке произойдет переполнение
			{
				//разбиваем на два и устанавливаем указатель на первый из этих двух.
				FLptr = divisionFirstList(FLptr)->prev;
				//ищем в который из них хотим установить
				FLptr = findPtrFirstListForInput(FLptr, numb);
			}
			if (FLptr->contain + 1 <= FLptr->max) //переполнения не будет
			{
				if (numb == FLptr->contain)
				{
					addToTailOfLists(FLptr, paste);
				}
				else if (numb == 0)	//условие вставки в начало (идет замена заголовка)
				{
					//printf("I caught him\n");
					paste->next = FLptr->headOFSecondList;
					FLptr->headOFSecondList = paste;
					FLptr->contain++;
				}
				else if (numb!=0&&numb!=FLptr->contain)
				{
					SecondList * tmpSLptr;	// создали указатель на элемент второго уровня
					tmpSLptr = FLptr->headOFSecondList;
					for (int i = numb-1; i > 0; i--)
					{
						tmpSLptr = tmpSLptr->next;
					}
					paste->next = tmpSLptr->next;
					tmpSLptr->next = paste;
					FLptr->contain++;
				}
			}
										   
		}
		
	}

}
int delByIndex(FirstList *&head, int indx)
{
	int countAllOfSecList = getcountsAllOfSecList(head);	// Завели переменную хранящую количество элементов в списке списков

	if (indx<0 || indx>countAllOfSecList - 1)				//проверяем индекс на правильность (на существование)
		return -1;											// в случае отсутствия такого индекса возвращаем ощибку

	FirstList * FLptr;								//устанавливаем указатель на искомый элемент первого уровня
	FLptr = findPtrFirstListForDel(head, indx);		//и устанавливаем индекс

	//проверяем на то, что внутри этого списка элементов находится единственный элемент
	if (FLptr->contain == 1)		//&& indx == 0
	{
		//удаляем элемент второго уровня
		clearSecondList(FLptr->headOFSecondList);
		//Проверяем указывает ли временный указатель на первый элемент
		if (FLptr == head)
		{
			//плачевная ситуация когда необходимо удалить элемент первого уровня и он является загловком
			//необходимо убрать связь у следующего элемента с текущим
			if (FLptr->next != NULL)
			{
				FLptr->next->prev = NULL;
				// переводим ссылку на новое начало списка
				head = FLptr->next;
				// удаляем связь текущего элемента с новым заголовком
				FLptr->next = NULL;
			}
			else
			{
				free(FLptr);
				//clearFirstList(FLptr);
				return 0;
			}
			// очищаем список состоящий теперь из одного элемента
			/*free(FLptr->headOFSecondList->content);
			free(FLptr->headOFSecondList);
			free(FLptr);*/
			clearFirstList(FLptr);
			refreshIndex(head);
			return 0;
		}
		
		//проверку на заглавность удаляемого элемента проведена, значит все последующие будут не заглавными (у которых сущ предыд элементы)
		//если существует следующий элемент(то есть это середина), то приводим все связи в соответствие
		FirstList * tmp1, tmp2;
		if (FLptr->next != NULL)
		{
			
			FLptr->next->prev = FLptr->prev;
		}

		FLptr->prev->next = FLptr->next;
		
		free(FLptr);
	}
	else
	{
		SecondList * tmp, *tmp1;
		if (indx == 0)	//указали на первый элемент списка (то есть необходимо обновить указатель на начало)
		{
			tmp = FLptr->headOFSecondList;
			FLptr->headOFSecondList = tmp->next;
			//clearSecondList(tmp);
			free(tmp->content);
			free(tmp);
			FLptr->contain--;
			refreshIndex(head);
			return 0;
		}
		else
		{
			tmp = FLptr->headOFSecondList;
			for (int i = indx-1; i > 0; i--)	//установили указатель на предыдущий перед нужным
			{
				tmp = tmp->next;
			}
			tmp1 = tmp->next;
			tmp->next = tmp1->next;
			//clearSecondList(tmp1);
			free(tmp1->content);
			free(tmp1);
			FLptr->contain--;
			refreshIndex(head);
			return 0;
		}
	}

	

}
int getcountsAllOfSecList(FirstList * head)
{
	int tmp = 0;
	for (FirstList * current = head; current != NULL; current = current->next)
	{
		tmp += current->contain;
	}
	return tmp;
}
int getCountAllOfFirstList(FirstList * head)
{
	FirstList * tmp;
	tmp = head;
	int i = 0;
	for (; tmp != NULL; tmp = tmp->next)
	{
		i++;
	}
	return i;
}
void refreshIndex(FirstList * head)
{
	int i = 0;
	for (FirstList * currentFL = head; currentFL != NULL; currentFL = currentFL->next)
	{
		for (SecondList * currentSL = currentFL->headOFSecondList; currentSL != NULL; currentSL = currentSL->next)
		{
			currentSL->indx = i;
			i++;
		}
	}
}
void saveToFile(FirstList * head)
{
	FILE * fd = fopen("111.txt", "w+");
	fprintf(fd,"%d\n",head->max);
	for (FirstList * currentFL = head; currentFL != NULL; currentFL = currentFL->next)
	{
		fprintf(fd,"%d\n",currentFL->contain);
		for (SecondList * currentSL = currentFL->headOFSecondList; currentSL != NULL; currentSL = currentSL->next)
		{
			fprintf(fd,"%s\n",currentSL->content);
		}
		//fprintf(fd,"\n");
	}
	fclose(fd);
}
void loadFromFile(FirstList * head)
{
	FirstList * start;
	start = head;
	FILE *fd = fopen("111.txt", "r+");
	int i = 0;
	int max;
	fscanf(fd, "%d", &max);
	start->max = max;
	printf("load max = %d\n", max);
	int contain = 0;
	fscanf(fd, "%d", &contain);
	printf("Load contain %d\n", contain);
	if (contain == 0)
	{
	}
	else
	{
		while (true)
		{
			start->contain = 0;
			//printf("%d\n", contain);
			getc(fd); // считываем лишний '\n' из файла после цифры

			for (int k = 0; k < contain; k++)
			{
				char buf[255] = { 0 };
				char * returnableBuf;
				SecondList *tmp;
				tmp = creatCleanElemSecList();
				int j = 0;
				while (true)
				{
					char ch = getc(fd);
					if (ch == '\n')
						break;
					buf[j] = ch;
					j++;
				}

				int bufsize = (strlen(buf) + 1);
				returnableBuf = (char*)malloc(sizeof(char)*bufsize);
				strcpy(returnableBuf, buf);
				tmp->content = returnableBuf;
				tmp->indx = i++;
				addToTailOfLists(start,tmp);
				printf("Add %s\n", returnableBuf);
				//start->contain++;
			}
			contain = 0;
			fscanf(fd, "%d", &contain);
			if (contain == 0)
				break;
			else
			{
				start->next = creatFirstList();
				start->next->prev = start;
				start->next->max = max;
				start = start->next;
			}
			printf("Load contain %d\n", contain);

		}
	}
	printf("end read\n");
	fclose(fd);
}
int findIndexOfInput(FirstList * head, SecondList * paste)
{
	int i = 0;
	for (FirstList * currentFirstList = head; currentFirstList != NULL; currentFirstList = currentFirstList->next)
	{
		for (SecondList * currentSecondList = currentFirstList->headOFSecondList; currentSecondList != NULL; currentSecondList = currentSecondList->next)
		{
			switch (compare(paste, currentSecondList))
			{
			case 1:		//paste больше чем currentSecList
				i++; 
				break;	
			case 0:		//paste меньше чем currentSecList
				return i;
				break;
			case -1:	//они равны
				return i;
				break;
			}
		}
	}
	return i;
}
int compare(SecondList * first, SecondList * second)
{
	
	int fLen = strlen(first->content);
	int sLen = strlen(second->content);
	int i;
	for (i = 0; i < fLen&&i < sLen; i++)	//Проверяем на условие что код очередного символа первого элемента больше очередного символа второго элемента
	{
		char f, s;
		f = first->content[i];		
		s = second->content[i];
		if (f > s)						//если больше то возвращаем 1
			return 1;
		if (f < s)						//если меньше то возвращаем 0
			return 0;
	}
	//если цикл прошел полностью до условия выхода из цикла, то значит содержимое совпадает по кр мере до конца одной из строки
	//поэтому проверяем на предмет разности длин строк
	//при этом будем считать строку с большей длинной большей в принципе в этом сравнении
	if (fLen==sLen)	//условие равности содержимого
		return -1;
	if (fLen > sLen)	//условие если длинна первого содержимого больше чем второго
		return 1;
	else
		return 0;
}
void clearSecondList(SecondList * Elem)
{
	if (Elem->next != NULL)
		clearSecondList(Elem->next);
	free(Elem->content);
	free (Elem);
}
void clearFirstList(FirstList*head)
{
	FirstList * current;
	for (current=head; current ->next!= NULL; current = current->next)
	{
		if(current->headOFSecondList!=NULL)
			clearSecondList(current->headOFSecondList);
	}
	for (current; current->prev != NULL;)
	{
		FirstList * tmpPtr;
		tmpPtr = current->prev;
		free(current);
		current = tmpPtr;
	}
	free(current);
}
bool isEqual(SecondList * elem, char * c)
{
	int lenC = strlen(c);
	int lenSL = strlen(elem->content);
	int i = 0;
	for (; elem->content[i] != '\0'&&c[i] != '\0'; i++)
	{
		if (elem->content[i] != c[i])
			return false;
	}
	if (i == lenC)
		return true;

	return false;

}

//////////////////СЛУЖЕБНЫЕ ФУНКЦИИ///////////////////////////////
void printMenu(const char ** menu, int counOfMenuItem)
{
	printf("\n-----------------menu------------------\n");
	for (int i = 0; i < counOfMenuItem; i++)
		printf("%s\n",menu[i]);
}
int choiseFrom(int counOfChoise)
{
	int ch;
	while (true)
	{
		while (true)
		{
			std::cout << ">>>";
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin >> ch;
			if (std::cin.peek() == '\n')
			{
				std::cin.get();
				break;
			}
			else {
				std::cout << "You input not a number!!! Carefully..." << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
			}
		}

		if (ch == counOfChoise)
			return -1;
		if (ch < 1 || ch>counOfChoise)
		{
			std::cout << "Sorry, not valid menu item, try again" << std::endl;
		}
		else
			return ch;
	}
}
int getNumber(int from, int to)
{
	int ch;
	while (true)
	{
		while (true)
		{
			std::cout << ">>>";
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin >> ch;
			if (std::cin.peek() == '\n')
			{
				std::cin.get();
				break;
			}
			else {
				std::cout << "You input not a number!!! Carefully..." << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
			}
		}

		if (ch < from || ch>to)
		{
			std::cout << "Sorry, out of diapason from " <<from<<" to "<<to<<"!((("<< std::endl;
		}
		else
			return ch;
	}
}
char * getInput()
{
	char buf[255] = { 0 };
	char * returnableBuf;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	scanf("%[^\n]s", buf);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	int bufsize = (strlen(buf) + 1);
	returnableBuf = (char*)malloc(sizeof(char)*bufsize);
	strcpy(returnableBuf, buf);

	return returnableBuf;
}
void printTheFile()
{
	FILE *fd = fopen("111.txt", "r+");
	//int i = 0;
	int max;
	fscanf(fd, "%d", &max);
	printf("Max:%d\n", max);

	while (true)
	{
		int contain = 0;
		//char tmp[255];
		fscanf(fd, "%d", &contain);
		if (contain == 0)
			break;
		printf("%d\n", contain);
		getc(fd); // считываем лишний '\n' из файла после цифры

		for (int i = 0; i < contain; i++)
		{
			char buf[255] = { 0 };
			char * returnableBuf;

			int j = 0;
			while (true)
			{
				char ch = getc(fd);
				if (ch == '\n')
					break;
				buf[j] = ch;
				j++;
			}

			int bufsize = (strlen(buf) + 1);
			returnableBuf = (char*)malloc(sizeof(char)*bufsize);
			strcpy(returnableBuf, buf);
			printf("%s\n", returnableBuf);

		}
		printf("end of block\n");
	}
	printf("end read\n");
	fclose(fd);
}
void testing()
{
	system("cls");
	printf("Please, input count of Element (from 100 to 100 000)?\n");
	int n = getNumber(100, 100000);
	FirstList * head, *tmpHead;

	head = creatHeadFirstList();
	tmpHead = head;

	unsigned int start_time = clock();
	for (int i = 0; i < n; i++)
	{
		SecondList * tmp = creatElemSecListEmpty();
		tmpHead = addToTailOfLists(tmpHead, tmp);
	}

	unsigned int end_time = clock();
	unsigned int result = end_time - start_time;
	printf("Time to creat and input %d elements = %ld\n", n, result);

	system("pause");

	int a, b;
	start_time = clock();
	for (int i = 0; i < n; i++)
	{
		b = getcountsAllOfSecList(head);
		a = rand() % b;
		delByIndex(head, a);
	}
	end_time = clock();
	result = end_time - start_time;
	printf("Time to %d delete random element = %ld\n", n, result);
	system("pause");
}






