#pragma once

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
void secondFillFirstList(FirstList * headOfFirstList);// используя fillSecondList() функция заполняет работает на уровне первого списка.
void showFirstList(FirstList*head);	// выводит на экран список первого уровня используя в цикле функцию вывода списка второго уровня
void showSecondList(SecondList*head);	/*	выводит на экран список второго уровня, в качестве аргумента принимает заголовок */
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
void printMenu(const char **, int);
int choiseFrom(int counOfChoise);
int getNumber(int, int);
char * getInput();	// функция считывает со строки консоли строку и возвращает указатель на нее в качестве результата
void printTheFile();
void testing();