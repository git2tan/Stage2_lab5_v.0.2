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

FirstList * creatHeadFirstList(); /*	������� ���������� ��������� �� ������ ���������� ��� ��������� ������ ������� ������ ������� ������
								  � ���� ������� �� �������� ������ ������ ��� ������� ������� ������.
								  ������ �� ������� ������� ������ ��NULL���. ����� ������ �� �������� � ���������� ������� �����
								  ������������ � NULL*/
FirstList * creatFirstList();		/*	������� �������� ������ ��� ��������� ������� ������ ������� ������ � ���������� ��������� �� ����*/
FirstList * addToTailOfLists(FirstList * headFistList, SecondList * paste); /*��������� ������� � ����� ������ �������
																			���������� ��������� �� ����� �����*/
FirstList * findPtrFirstListForInput(FirstList * head, int &number); //���������� ��������� �� ������� ������ ������� ������ �� ������ ��� �������
FirstList * findPtrFirstListForDel(FirstList * head, int &number);	/*���������� ��������� �� ������� ������ ������� ������ �� ������ ��� ��������*/
FirstList * divisionFirstList(FirstList * head);//����� �� ��� � ���������� ��������� �� ������
FirstList * creatSortOfFirstList(FirstList * head);	/*������ ����� ������ ������� � ��������� ���������� ��������
													(�� ������� ������ �� ������) ��������� ������ ������� ������*/
FirstList * balance(FirstList*);	/*������������*/
SecondList * creatElemSecondList();				/*	������� �������� ������ ��� ������� ���� SecondList � ��������� ���*/
SecondList * creatElemSecListEmpty();	/*������� ������� � �������� ��� ���� ������ � ���������������� �� ��������� (������)*/
SecondList * copySecondList(SecondList *Elem);// ������� ��������� �� ����� ������� ������������� �� Elem
SecondList * findString(FirstList *, char * string);	/*����� �� ������ �������*/
void addToSecondList(SecondList * head, SecondList* paste);	// ������� ��������� � (������������� ��������) ������ ������� ������ ������� � ����� ������.
void secondFillFirstList(FirstList * headOfFirstList);// ��������� fillSecondList() ������� ��������� �������� �� ������ ������� ������.
void showFirstList(FirstList*head);	// ������� �� ����� ������ ������� ������ ��������� � ����� ������� ������ ������ ������� ������
void showSecondList(SecondList*head);	/*	������� �� ����� ������ ������� ������, � �������� ��������� ��������� ��������� */
bool isExit(const char *);	// ��������� ������������ ������ �� ���������� �� ������ "exit"
void inputByNumber(FirstList * head, SecondList * paste, int numb);
int delByIndex(FirstList * &, int);		//������� �� ������ ������� ������� �� �������
int getcountsAllOfSecList(FirstList * head);	//������� ����� ���������� ��������� ������� ������
int getCountAllOfFirstList(FirstList * head);	// ������� ���������� ��������� ������� ������
void refreshIndex(FirstList * head);//��������� �������
void saveToFile(FirstList * head); // ���������� ������� ��������� � ����
void loadFromFile(FirstList * head);//��������� ���������� ��������� �� �����
int findIndexOfInput(FirstList * head, SecondList *); //���� ������ ������� �� �������������� ������ �������
int compare(SecondList*, SecondList*); /*���������� ���������� ���� ��������� ������� ������*/
void clearSecondList(SecondList *);	/*���������� ������� ������ �� ��� ������ ������� ������*/
void clearFirstList(FirstList*);	/*������� ������*/
bool isEqual(SecondList * elem, char * c);	/*���������� ���������� �������� �������� � ��������� �� ������*/

//////////////////��������� ��������� �������///////////////////////////////
void printMenu(const char **, int);
int choiseFrom(int counOfChoise);
int getNumber(int, int);
char * getInput();	// ������� ��������� �� ������ ������� ������ � ���������� ��������� �� ��� � �������� ����������
void printTheFile();
void testing();