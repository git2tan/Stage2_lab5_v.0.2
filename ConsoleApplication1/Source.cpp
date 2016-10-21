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
void creatHeadSecondList(FirstList * elem);	/*	������� �������� ������ ��� �������� ������� ������ � ��������� ��� � ������*/
SecondList * creatElemSecondList();				/*	������� �������� ������ ��� ������� ���� SecondList � ��������� ���*/
char * getInput();	// ������� ��������� �� ������ ������� ������ � ���������� ��������� �� ��� � �������� ����������
void addToSecondList(SecondList * head, SecondList* paste);	// ������� ��������� � (������������� ��������) ������ ������� ������ ������� � ����� ������.
void fillSecondList(SecondList * headOfSecondList, bool &isBreak);	/*	������� �������� �� ���� ��������� �� ��������� ������ ������� ������ � � ������ �� ����������-���� ����������� ��
												��, ��� ��������� ��������� ����� ���� "exit", � ������ ����� ���������� ����. ��������� ������. 
												���������������, ��� �� ��������� ������� ���������� ��� ���� �������� ������ �����.*/
void firstFillFirstList(FirstList * headOfFirstList); // ��������� fillSecondList() ������� ��������� �������� �� ������ ������� ������.
void secondFillFirstList(FirstList * headOfFirstList);
void showFirstList(FirstList*head);	// ������� �� ����� ������ ������� ������ ��������� � ����� ������� ������ ������ ������� ������
void showSecondList(SecondList*head);	/*	������� �� ����� ������ ������� ������, � �������� ��������� ��������� ��������� */
void showOneFirstList(FirstList * head);
bool isExit(const char *);	// ��������� ������������ ������ �� ���������� �� ������ "exit"
FirstList * addToTailOfLists(FirstList * headFistList, SecondList * paste); /*��������� ������� � ����� ������ ������� 
																				���������� ��������� �� ����� �����*/
void inputByNumber(FirstList * head, SecondList * paste, int numb);
int getcountsAllOfSecList(FirstList * head);
FirstList * findPtrFirstListForInput(FirstList * head, int &number); //���������� ��������� �� ������� ������ ������� ������ �� ������ ��� �������
FirstList * divisionFirstList(FirstList * head);//����� �� ��� � ���������� ��������� �� ������
void refreshIndex(FirstList * head);//��������� �������


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
	elem->headOFSecondList = tmp; //�������� ������ �� ���������� ������ ������������ �������
	tmp->content = NULL;
	tmp->next = NULL;
}
SecondList * creatElemSecondList()
{
	printf(">>>");//Please, input the element of Secondary List?\n
	char *tmpc = getInput();
	if (isExit(tmpc)) // ���� ������ exit �� �������� ������ � ���������������� ����� ������� ��������� �� �����.
		return NULL;
	SecondList *tmp = (SecondList*)malloc(sizeof(SecondList)); //�������� ������ ��� ������� ������ ������� ������
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
	SecondList * current;															//������� ��������� �� ���������
	
	for (current = head; current->next != NULL; current = current->next);	//����������� ��������� ���� ��������� ����� �������� ������� �� ����� ��������� �� NULL
	
	current->next = paste;													//�������� � ��������� �� ��������� ������� (������� ����� �������� �� NULL) ������� �������
}
void fillSecondList(SecondList * headOfSecondList, bool &isBreak)
{
	int i = 0;	//������� �������
	SecondList * start = headOfSecondList;	//������� ��������� �� ���������
							
	printf("Please, input the title element of Secondary List?\n>>>");
	start->content = getInput();//��������� ������ �������(���������)
	i++;
	while (true)
	{	
		int isExit = 0;							//
		//printf("Continue input?Y(1)/N(0)\n");	// ������� ������ �� ����� ����������
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
	int i = 0; //������� ���������� �������� ���������� ����������� ����� ��������� �������� (������)
	//headOfFirstList = creatHeadFirstList();
	FirstList * start = headOfFirstList;
	creatHeadSecondList(headOfFirstList);
	printf("Now we begin to first fill the list of list\n");
	while (true)	//������� ���� �������� ������ � ������� ����� ������� ������������ ���������� ���� ���������
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
		start->next = creatFirstList();	//	������� ����� ������� ������ ������� ������
		start->next->prev = start;	//	�������� � ������������ ��������� �� ���������� ������� � ����� ����������
		creatHeadSecondList(start->next);	//	�������� ������ �� ������ ������ ������� ������ (��� ���������)
		start = start->next;		//	���������� ��������� �� ��������� ������� ������� ������
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
		
		//�������� ���������� �������� �������� FirstList � ����������� ������������ �� ���
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
	int countAllOfSecList = getcountsAllOfSecList(head);	// ������ ���������� �������� ���������� ��������� � ������ �������
	
	if (numb >= countAllOfSecList)							// �������� �������� ������� � ����� �����
	{
		FirstList * tailPtr;// ������� ��������� � ������������� ��� �� ��������� ������� ������
		tailPtr = head;
		for (; tailPtr->next != NULL; tailPtr = tailPtr->next);//������� ��������� ������� ������� ������
		addToTailOfLists(tailPtr, paste);
	}
	else
	{
		//�� � ����� ������
		FirstList * FLptr;
		FLptr = findPtrFirstListForInput(head, numb);
		
		if (numb == FLptr->contain)	//��������� ������ �� ��� �������������� ����� ������ �������������� ���������
		{
			if (FLptr->next != NULL)
			{
				// ��������� ������ ���������� ������, ���� ��� ������ �������� �� ��������� � ������ ����������
				if (FLptr->contain > FLptr->next->contain)
				{
					//���� ������ ���������� ������ ��������
					paste->next = FLptr->next->headOFSecondList; // ������������� ��������� �� ���� ������� �� ���������
					FLptr->next->headOFSecondList = paste;	//� �������� ������ ��������� ������������� ����������� �������
					FLptr->next->contain++;
				}
				else
				{
					//��������� �� ����������� "��������������" �������
					if (FLptr->contain < FLptr->max)
					{
						addToTailOfLists(FLptr, paste);
					}
					else
					{
						FLptr = divisionFirstList(FLptr);//����� ������� �� 2 ����� ��������...
						addToTailOfLists(FLptr, paste);	//� ��������� ������� � �����
					}
				}
			}
			else
			{
				addToTailOfLists(FLptr, paste); //����� �� ����� ���� �� ��� ��...
				printf("WOWOWOWOWOWOWOW\nWOWOWOWOWOW\nWOWOWOWOWOWOW\n\n");
			}
			//
		}
		else
		{
			//������� �� � ����� ������...
			if (FLptr->contain + 1 > FLptr->max)//����  ��� ������� ���������� ������������
			{
				//��������� �� ��� � ������������� ��������� �� ������ �� ���� ����.
				FLptr = divisionFirstList(FLptr)->prev;
				//���� � ������� �� ��� ����� ����������
				FLptr = findPtrFirstListForInput(FLptr, numb);
			}
			if (FLptr->contain + 1 < FLptr->max) //������������ �� �����
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
	//�������� � ����������� ��������� � ���� ������

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




