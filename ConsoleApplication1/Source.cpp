#define _CRT_SECURE_NO_WARNINGS
/*�� ���������� ������ ��������������� ��������� ������ ������������ ����� ������� �������� ������������������ 
��������� (��������, �����) �� ����������� ������� �������� (���������� � �����, ������� � �������� �� ����������� ������, 
����������, �������� �����, ������� � ����������� �������, ���������� � �������� �� ���������� �����, ������������ 
(������������ - ������������ ������������ �������� ������ ������� ������). ���������� ��������� ������ ����� ��� ������. 

�� ������ ������ �������������� ����������� ����������� ��������� ������: ��� ������������ ��� ����������� �������, 
��������������� ��������� �������� � ������� �������. ��� ���������� ������ ���������� ��������� ����������� ��������� 
������� ������ ��������� � �� ������������ (���������� ������� ��������). ������� ��� ���������� 
����������� (�������-���������������, ������������).

������ - ������ ������� �������� ���������� ������������ ������. ������� ������ ������� ������ ��������
��������� �� ������. (��������� �������� ��������� � ������ ����������� � ������ 
������������ ����� �������� � ���������� �������).*/

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

FL * creatHeadFL(); /*	������� ���������� ��������� �� ������ ���������� ��� ��������� ������ ������� ������ ������� ������
						� ���� ������� �� �������� ������ ������ ��� ������� ������� ������. 
						������ �� ������� ������� ������ ��NULL���. ����� ������ �� �������� � ���������� ������� ����� ������������ � NULL*/
FL * creatFL();		/*	������� �������� ������ ��� ��������� ������� ������ ������� ������ � ���������� ��������� �� ����*/
void creatHeadSL(FL * elem);	/*	������� �������� ������ ��� �������� ������� ������ � ��������� ��� � ������*/
SL * creatElemSL();				/*	������� �������� ������ ��� ������� ���� SL � ��������� ���*/
char * getInput();	// ������� ��������� �� ������ ������� ������ � ���������� ��������� �� ��� � �������� ����������
void addToSL(SL * head, SL* paste);	// ������� ��������� � (������������� ��������) ������ ������� ������ ������� � ����� ������.
void fillSL(SL * headOfSL);	// ������� �������� �� ���� ��������� �� ��������� ������ ������� ������ � �������� ��������� ���
							// ���������������, ��� �� ��������� ������� ���������� ��� ���� �������� ������ �����.
void firstFillFL(FL * headOfFL); // ��������� fillSL() ������� ��������� �������� �� ������ ������� ������.
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
	elem->headOFSL = tmp; //�������� ������ �� ���������� ������ ������������ �������
	tmp->content = NULL;
	tmp->next = NULL;
}
SL * creatElemSL()
{
	SL *tmp = (SL*)malloc(sizeof(SL)); //�������� ������ ��� ������� ������ ������� ������
	
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
	SL * current;															//������� ��������� �� ���������
	
	for (current = head; current->next != NULL; current = current->next);	//����������� ��������� ���� ��������� ����� �������� ������� �� ����� ��������� �� NULL
	
	current->next = paste;													//�������� � ��������� �� ��������� ������� (������� ����� �������� �� NULL) ������� �������
}

void fillSL(SL * headOfSL)
{
	int i = 0;	//������� �������
	SL * start = headOfSL;	//������� ��������� �� ���������
							
	printf("Please, input the title element of Secondary List?\n>>>");
	start->content = getInput();//��������� ������ �������(���������)

	while (true)
	{	
		int isExit = 0;							//
		printf("Continue input?Y(1)/N(0)\n");	// ������� ������ �� ����� ����������
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
	int i = 0; //������� ���������� �������� ���������� ����������� ����� ��������� �������� (������)
	//headOfFL = creatHeadFL();
	FL * start = headOfFL;
	creatHeadSL(headOfFL);
	printf("Now we begin to first fill the list of list\n");
	while (true)	//������� ���� �������� ������ � ������� ����� ������� ������������ ���������� ���� ���������
	{
		fillSL(start->headOFSL);

		int isExit0 = 0;
		printf("Do you want stop the input? Or continue and creat new element of FL? Continue(1)/stop(0)\n>>>");
		scanf("%d", &isExit0);

		if (isExit0 == 0)
		{
			break;
		}
		start->next = creatFL();	//	������� ����� ������� ������ ������� ������
		start->next->prev = start;	//	�������� � ������������ ��������� �� ���������� ������� � ����� ����������
		creatHeadSL(start->next);	//	�������� ������ �� ������ ������ ������� ������ (��� ���������)
		start = start->next;		//	���������� ��������� �� ��������� ������� ������� ������
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
