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

struct SL
{
	SL * next;
	char * content;
};
struct FL
{
	FL * next;
	FL * prev;
	SL * headOFSL;
};

FL * creatHeadFL(); /*	функция возвращает указатель на память выделенную под созданный первый элемент списка первого уровня
						в этой функции мы выделяем память только под элемент первого уровня. 
						Ссылку на элемент второго уровня заNULLяем. Также ссылки на следущий и предыдущий элемент также приравниваем к NULL*/
FL * creatFL();		/*	функция выделяет память под очередной элемент списка первого уровня и возвращает указатель на него*/
void creatHeadSL(FL * elem);	/*	функция выделяет память под заголовк второго уровня и размещает его в первом*/
SL * creatElemSL();				/*	функция выделяет память под элемент типа SL и заполняет его*/
char * getInput();	// функция считывает со строки консоли строку и возвращает указатель на нее в качестве результата
void addToSL(SL * head, SL* paste);	// функция добавляет к (СУЩЕСТВУЮЩЕМУ ЕЛЕМЕНТУ) списку второго уровня елемент в конец списка.
void fillSL(SL * headOfSL);	// функция получает на вход указатель на заголовок списка второго уровня и начинает заполнять его
							// подразумевается, что по указателю который передается уже была выделена память ранее.
void firstFillFL(FL * headOfFL); // используя fillSL() функция заполняет работает на уровне первого списка.
void showFL(FL*head);
void showSL(SL*head);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	FL * head;
	head = creatHeadFL();
	firstFillFL(head);
	showFL(head);
	system("pause");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FL * creatHeadFL()
{
	FL * head = (FL*)malloc(sizeof(FL));
	head->next = head->prev = NULL;
	head->headOFSL = NULL;
	return head;
}
FL * creatFL()
{
	FL * tmp = (FL*)malloc(sizeof(FL));
	tmp->headOFSL = NULL;
	tmp->next = tmp->prev = NULL;
	return tmp;
}

void creatHeadSL(FL * elem)
{
	SL*tmp = (SL*)malloc(sizeof(SL));
	elem->headOFSL = tmp; //выделили память по указанному адресу необходимого размера
	tmp->content = NULL;
	tmp->next = NULL;
}
SL * creatElemSL()
{
	SL *tmp = (SL*)malloc(sizeof(SL)); //выделяем память под элемент списка второго уровня
	
	printf("Please, input the element of Secondary List?\n>>>");
	tmp->content = getInput();
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
void addToSL(SL * head, SL* paste)
{
	SL * current;															//создаем указатель на заголовок
	
	for (current = head; current->next != NULL; current = current->next);	//передвигаем указатель пока следующий после текущего элемент не будет ссылаться на NULL
	
	current->next = paste;													//копируем в указатель на следующий элемент (который ранее указывал на NULL) текущий элемент
}

void fillSL(SL * headOfSL)
{
	int i = 0;	//создаем счетчик
	SL * start = headOfSL;	//создаем указатель на заголовок
							
	printf("Please, input the title element of Secondary List?\n>>>");
	start->content = getInput();//считываем первый элемент(заголовок)

	while (true)
	{	
		int isExit = 0;							//
		printf("Continue input?Y(1)/N(0)\n");	// условие выхода из цикла заполнения
		scanf("%d", &isExit);					//
		if (isExit == 0)						//
			break;								//

		start->next = creatElemSL();			
		start = start->next;

		i++;
	}
}

void firstFillFL(FL * headOfFL)
{
	int i = 0; //создаем переменную хранящую глобальный порядоковый номер конечного элемента (строки)
	//headOfFL = creatHeadFL();
	FL * start = headOfFL;
	creatHeadSL(headOfFL);
	printf("Now we begin to first fill the list of list\n");
	while (true)	//создаем цикл условием выхода в котором будет желание пользователя прекратить ввод элементов
	{
		fillSL(start->headOFSL);

		int isExit0 = 0;
		printf("Do you want stop the input? Or continue and creat new element of FL? Continue(1)/stop(0)\n>>>");
		scanf("%d", &isExit0);

		if (isExit0 == 0)
		{
			break;
		}
		start->next = creatFL();	//	создаем новый элемент списка первого уровня
		start->next->prev = start;	//	приводим в соответствие указатели на предыдущий элемент у вновь созданного
		creatHeadSL(start->next);	//	выделяем память по адресу списка второго уровня (под заголовок)
		start = start->next;		//	перемещаем указатель на следующий элемент первого уровня
	}
}

void showFL(FL*head)
{
	int i = 0;
	for (FL * current = head; current != NULL; current = current->next, i++)
	{
		printf("Print %dst First List (FL):\n", i);
		showSL(current->headOFSL);
		printf("\n");
	}
}
void showSL(SL*head)
{
	int i = 0;
	for (SL * current = head; current != NULL; current = current->next)
	{

		printf("%dst element of Secondary List (SL) is: %s\n",i, current->content);
		i++;
	}
}
