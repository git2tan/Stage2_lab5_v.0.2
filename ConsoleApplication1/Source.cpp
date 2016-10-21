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
void creatHeadSecondList(FirstList * elem);	/*	функция выделяет память под заголовк второго уровня и размещает его в первом*/
SecondList * creatElemSecondList();				/*	функция выделяет память под элемент типа SecondList и заполняет его*/
char * getInput();	// функция считывает со строки консоли строку и возвращает указатель на нее в качестве результата
void addToSecondList(SecondList * head, SecondList* paste);	// функция добавляет к (СУЩЕСТВУЮЩЕМУ ЭЛЕМЕНТУ) списку второго уровня элемент в конец списка.
void fillSecondList(SecondList * headOfSecondList, bool &isBreak);	/*	функция получает на вход указатель на заголовок списка второго уровня и и ссылку на переменную-флаг указывающую на
												то, что последнее введенное слово было "exit", а значит нужно прекратить ввод. Заполняет список. 
												Подразумевается, что по указателю который передается уже была выделена память ранее.*/
void firstFillFirstList(FirstList * headOfFirstList); // используя fillSecondList() функция заполняет работает на уровне первого списка.
void secondFillFirstList(FirstList * headOfFirstList);
void showFirstList(FirstList*head);	// выводит на экран список первого уровня используя в цикле функцию вывода списка второго уровня
void showSecondList(SecondList*head);	/*	выводит на экран список второго уровня, в качестве аргумента принимает заголовок */
void showOneFirstList(FirstList * head);
bool isExit(const char *);	// проверяет передаваемую строку на совпадение со словом "exit"
FirstList * addToTailOfLists(FirstList * headFistList, SecondList * paste); /*добавляет элемент в конец списка списков 
																				возвращает указатель на новый хвост*/
void inputByNumber(FirstList * head, SecondList * paste, int numb);
int getcountsAllOfSecList(FirstList * head);
FirstList * findPtrFirstListForInput(FirstList * head, int &number); //возвращает указатель на элемент списка первого уровня по номеру для вставки
FirstList * divisionFirstList(FirstList * head);//делит на два и возвращает указатель на второй
void refreshIndex(FirstList * head);//обновляет индексы


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	FirstList * head;
	head = creatHeadFirstList();
	printf("Now we begin to first fill the list of list. Input elem or input \"exit\" for break input\n");

	secondFillFirstList(head);
	
	showFirstList(head);
	/*int tmp = 4;
	showOneFirstList(findPtrFirstListForInput(head,tmp));
	printf("You want input by index = %d\n",tmp);*/
	while (true)
	{
		int numb;
		SecondList *tmpElem;
		printf("Input indx and string\n");
		scanf("%d", &numb);
		tmpElem = creatElemSecondList();
		if (tmpElem == NULL)
			break;
		inputByNumber(head, tmpElem, numb);
		refreshIndex(head);
		showFirstList(head);
	}
	system("pause");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FirstList * creatHeadFirstList()
{
	FirstList * head = (FirstList*)malloc(sizeof(FirstList));
	head->next = head->prev = NULL;
	head->headOFSecondList = NULL;
	head->contain = 0;
	head->max = 5;
	//head->counts = 0;
	
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
void creatHeadSecondList(FirstList * elem)
{
	SecondList*tmp = (SecondList*)malloc(sizeof(SecondList));
	elem->headOFSecondList = tmp; //выделили память по указанному адресу необходимого размера
	tmp->content = NULL;
	tmp->next = NULL;
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
void firstFillFirstList(FirstList * headOfFirstList)
{
	int i = 0; //создаем переменную хранящую глобальный порядоковый номер конечного элемента (строки)
	//headOfFirstList = creatHeadFirstList();
	FirstList * start = headOfFirstList;
	creatHeadSecondList(headOfFirstList);
	printf("Now we begin to first fill the list of list\n");
	while (true)	//создаем цикл условием выхода в котором будет желание пользователя прекратить ввод элементов
	{
		bool isBreak = false;
		fillSecondList(start->headOFSecondList, isBreak);
		if (isBreak)
		{
			break;
		}
		int isExit0 = 0;
		printf("Do you want stop the input? Or continue and creat new element of FirstList? Continue(1)/stop(0)\n>>>");
		scanf("%d", &isExit0);

		if (isExit0 == 0)
		{
			break;
		}
		start->next = creatFirstList();	//	создаем новый элемент списка первого уровня
		start->next->prev = start;	//	приводим в соответствие указатели на предыдущий элемент у вновь созданного
		creatHeadSecondList(start->next);	//	выделяем память по адресу списка второго уровня (под заголовок)
		start = start->next;		//	перемещаем указатель на следующий элемент первого уровня
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
	printf("AllCount = %d\n", getcountsAllOfSecList(head));
	for (FirstList * current = head; current != NULL; current = current->next, i++)
	{
		printf("Print %dst First List (FirstList), contain = %d:\n", i, current->contain);
		showSecondList(current->headOFSecondList);
		printf("\n");
	}
}
void showSecondList(SecondList*head)
{
	
	for (SecondList * current = head; current != NULL; current = current->next)
	{
		printf("%dst element of Secondary List (SecondList) is: %s\n",current->indx, current->content);
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
FirstList * addToTailOfLists(FirstList * TailFirstList, SecondList * paste)
{
	FirstList * tail = TailFirstList;
	
	if ((tail->contain + 1) > tail->max)
	{
		tail->next = creatFirstList();
		tail->next->prev = tail;
		
		//алгоритм добавления новогого элемента FirstList с разделением составляющих на два
		int half = tail->contain / 2;
		
		SecondList * tmph=tail->headOFSecondList;
		for (int i = half-1; i > 0; i--)
			tmph = tmph->next;
		
		tail->next->headOFSecondList = tmph->next;
		tmph->next = NULL;	//

		tail->next->contain = tail->contain / 2 + tail->contain % 2;
		tail->contain = half;
		

		tail = tail->next;
		
	}
	if (tail->contain==0)
	{
		tail->headOFSecondList = paste;
		tail->contain++;

	}
	else
	{
		SecondList * tmp;
		for (tmp = tail->headOFSecondList; tmp->next != NULL;tmp=tmp->next);
		tmp->next = paste;

		tail->contain++;
	}
	return tail;
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
			if (FLptr->contain + 1 < FLptr->max) //переполнения не будет
			{
				if (numb == FLptr->contain)
				{
					addToTailOfLists(FLptr, paste);
				}
				else
				{
					SecondList * tmpSLptr;
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

int getcountsAllOfSecList(FirstList * head)
{
	int tmp = 0;
	for (FirstList * current = head; current != NULL; current = current->next)
	{
		tmp += current->contain;
	}
	return tmp;
}
FirstList * findPtrFirstListForInput(FirstList * head, int &number)
{
	FirstList * tmp;
	tmp = head;
	int sum=0;
	for (; tmp->next != NULL; tmp = tmp->next)
	{
		if (number <= tmp->contain)
			break;
		number -= tmp->contain;
	}
	return tmp;
}
FirstList * divisionFirstList(FirstList * head)
{
	FirstList * tail;
	tail = creatFirstList();
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

	return tail;
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




