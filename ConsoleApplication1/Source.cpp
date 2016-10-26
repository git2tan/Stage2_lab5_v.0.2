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
int delByIndex(FirstList * &, int);
int getcountsAllOfSecList(FirstList * head);	//������� ����� ���������� ��������� ������� ������
int getCountAllOfFirstList(FirstList * head);	// ������� ���������� ��������� ������� ������
FirstList * findPtrFirstListForInput(FirstList * head, int &number); //���������� ��������� �� ������� ������ ������� ������ �� ������ ��� �������
FirstList * findPtrFirstListForDel(FirstList * head, int &number);	/*���������� ��������� �� ������� ������ ������� ������ �� ������ ��� ��������*/
FirstList * divisionFirstList(FirstList * head);//����� �� ��� � ���������� ��������� �� ������
void refreshIndex(FirstList * head);//��������� �������
void saveToFile(FirstList * head); // ���������� ������� ��������� � ����
void printTheFile();
void loadFromFile(FirstList * head);//��������� ���������� ��������� �� �����
SecondList * copySecondList(SecondList *Elem);// ������� ��������� �� ����� ������� ������������� �� Elem
int findIndexOfInput(FirstList * head, SecondList *); //���� ������ ������� �� �������������� ������ �������
int compare(SecondList*, SecondList*); /*���������� ���������� ���� ��������� ������� ������*/
FirstList * creatSortOfFirstList(FirstList * head);	/*������ ����� ������ ������� � ��������� ���������� �������� 
													(�� ������� ������ �� ������) ��������� ������ ������� ������*/
void clearSecondList(SecondList *);	/*���������� ������� ������ �� ��� ������ ������� ������*/
void clearFirstList(FirstList*);	/*������� ������*/
FirstList * balance(FirstList*);	/*������������*/
SecondList * findString(FirstList *, char * string);	/*����� �� ������ �������*/
bool isEqual(SecondList * elem, char * c);	/*���������� ���������� �������� �������� � ��������� �� ������*/
void testing();


/*��������� ������� � ���������� ��� ���������� ����*/
const int countMenuItem1 = 12;
const char * menu1[countMenuItem1] = {	
							//{"0.Show List of List"},
							{"1.Clear and Input new List from keyboard"},
							{"2.Clear and Load List from file"},
							{"3.Search string in the List"},
							{"4.Save DataBase to file"},
							{"5.Balancing"},					//
							{"6.Insert by indx"},				//
							{"7.Insert to sort List"},			//�� �����������
							{"8.Delete by indx"},				//�� �����������
							{"9.Sort"},
							{"10.Testing..."},					//�� �����������
							{"11.Save and exit"},
							{"12.Exit without saving"} };
const int countMenuItem0 = 3;
const char * menu0[countMenuItem0] = { {"1.Input new List from keyboard"}, {"2.Load from file"}, {"3.Exit"} };
void printMenu(const char **, int);
int choiseFrom(int counOfChoise);
int getNumber(int, int);
//void display1();	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
			showSecondList(tmpSecList);
			system("pause");
			free(tmp);
			break;
		case 4:		//4.Save DataBase to file
			saveToFile(head);
			break;
		case 5:		//5.Balancing
			balance(head);
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
			if (isSuccess == -1)
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
			void testing();
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
	printf("Result is:\n");
	
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
SecondList * creatCleanElemSecList() 
{
	SecondList *tmp = (SecondList*)malloc(sizeof(SecondList));
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->indx = NULL;
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
		printf("%dst element of Secondary List (SecondList) is: %s\n",current->indx, current->content);
		//printf("[%d]-[%s] ", current->indx, current->content);
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
			if (FLptr->contain + 1 <= FLptr->max) //������������ �� �����
			{
				if (numb == FLptr->contain)
				{
					addToTailOfLists(FLptr, paste);
				}
				else if (numb == 0)	//������� ������� � ������ (���� ������ ���������)
				{
					//printf("I caught him\n");
					paste->next = FLptr->headOFSecondList;
					FLptr->headOFSecondList = paste;
					FLptr->contain++;
				}
				else if (numb!=0&&numb!=FLptr->contain)
				{
					SecondList * tmpSLptr;	// ������� ��������� �� ������� ������� ������
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
	int countAllOfSecList = getcountsAllOfSecList(head);	// ������ ���������� �������� ���������� ��������� � ������ �������

	if (indx<0 || indx>countAllOfSecList - 1)				//��������� ������ �� ������������ (�� �������������)
		return -1;											// � ������ ���������� ������ ������� ���������� ������

	FirstList * FLptr;								//������������� ��������� �� ������� ������� ������� ������
	FLptr = findPtrFirstListForDel(head, indx);		//� ������������� ������

	//��������� �� ��, ��� ������ ����� ������ ��������� ��������� ������������ �������
	if (FLptr->contain == 1)		//&& indx == 0
	{
		//������� ������� ������� ������
		clearSecondList(FLptr->headOFSecondList);
		//��������� ��������� �� ��������� ��������� �� ������ �������
		if (FLptr == head)
		{
			//��������� �������� ����� ���������� ������� ������� ������� ������ � �� �������� ���������
			//���������� ������ ����� � ���������� �������� � �������
			FLptr->next->prev = NULL;
			// ��������� ������ �� ����� ������ ������
			head = FLptr->next;
			// ������� ����� �������� �������� � ����� ����������
			FLptr->next = NULL;
			// ������� ������ ��������� ������ �� ������ ��������
			/*free(FLptr->headOFSecondList->content);
			free(FLptr->headOFSecondList);
			free(FLptr);*/
			clearFirstList(FLptr);
			refreshIndex(head);
			return 0;
		}
		
		//�������� �� ����������� ���������� �������� ���������, ������ ��� ����������� ����� �� ���������� (� ������� ��� ������ ��������)
		//���� ���������� ��������� �������(�� ���� ��� ��������), �� �������� ��� ����� � ������������
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
		if (indx == 0)	//������� �� ������ ������� ������ (�� ���� ���������� �������� ��������� �� ������)
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
			for (int i = indx-1; i > 0; i--)	//���������� ��������� �� ���������� ����� ������
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
	FirstList * tmp;							//������� ��������� ��������� � ������������� ��� �� ������
	tmp = head;									//
	for (; tmp->next != NULL; tmp = tmp->next)	//��������� � ����� �� �������� �����
	{
		if (number < tmp->contain)
			break;
		number -= tmp->contain;					//������ ��� �� ������� ����� �������� ���������� ������������ 
												//��������� � ������ �� ������� ������� ������
												//�.�. ������� ��������� �� ����������� ������� � ������ ������������ ����� ������
	}
	return tmp;
}
FirstList * divisionFirstList(FirstList * head)
{
	//������� ����� ������� ���� FirstList
	FirstList * tail;
	tail = creatFirstList();
	if (head->next != NULL)
	{
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
	}
	else
	{
		tail->prev = head;
		head->next = tail;

		//������� ���������, � ������ ��� �� �������� ������������� ������
		int half = head->contain / 2;
		SecondList * tmp = head->headOFSecondList;
		for (int i = half - 1; i > 0; i--)
			tmp = tmp->next;

		tail->headOFSecondList = tmp->next;
		tmp->next = NULL;
		tail->contain = half+ head->contain%2;
		head->contain = half;

	}

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
void printTheFile()
{
	FILE *fd = fopen("111.txt", "r+");
	//int i = 0;
	int max;
	fscanf(fd, "%d", &max);
	printf("Max:%d\n",max);
	
	while (true)
	{
		int contain = 0;
		//char tmp[255];
		fscanf(fd, "%d",&contain);
		if (contain == 0)
			break;
		printf("%d\n",contain);
		getc(fd); // ��������� ������ '\n' �� ����� ����� �����
		
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
			printf("%s\n",returnableBuf);

		}
		printf("end of block\n");
	}
	printf("end read\n");
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
			getc(fd); // ��������� ������ '\n' �� ����� ����� �����

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
int findIndexOfInput(FirstList * head, SecondList * paste)
{
	int i = 0;
	for (FirstList * currentFirstList = head; currentFirstList != NULL; currentFirstList = currentFirstList->next)
	{
		for (SecondList * currentSecondList = currentFirstList->headOFSecondList; currentSecondList != NULL; currentSecondList = currentSecondList->next)
		{
			switch (compare(paste, currentSecondList))
			{
			case 1:		//paste ������ ��� currentSecList
				i++; 
				break;	
			case 0:		//paste ������ ��� currentSecList
				return i;
				break;
			case -1:	//��� �����
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
	for (i = 0; i < fLen&&i < sLen; i++)	//��������� �� ������� ��� ��� ���������� ������� ������� �������� ������ ���������� ������� ������� ��������
	{
		char f, s;
		f = first->content[i];		
		s = second->content[i];
		if (f > s)						//���� ������ �� ���������� 1
			return 1;
		if (f < s)						//���� ������ �� ���������� 0
			return 0;
	}
	//���� ���� ������ ��������� �� ������� ������ �� �����, �� ������ ���������� ��������� �� �� ���� �� ����� ����� �� ������
	//������� ��������� �� ������� �������� ���� �����
	//��� ���� ����� ������� ������ � ������� ������� ������� � �������� � ���� ���������
	if (fLen==sLen)	//������� �������� �����������
		return -1;
	if (fLen > sLen)	//������� ���� ������ ������� ����������� ������ ��� �������
		return 1;
	else
		return 0;
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
			printf("Input\"%s\" by indx = %d\n",currentSecList->content, numb);
			SecondList * tmp = copySecondList(currentSecList);

			inputByNumber(headNew, tmp, numb);
			printf("read \"%s\" complite!\n",tmp->content);
			
		}
	}
	refreshIndex(headNew);
	return headNew;
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
FirstList * balance(FirstList*head)
{
	FirstList * headPtr, * newHead, * newHeadPtr;
	headPtr = head;
	newHead = creatHeadFirstList();
	newHeadPtr = newHead;
	int a = getcountsAllOfSecList(headPtr);
	int b = getCountAllOfFirstList(headPtr);
	int average = a / b;
	int residue = a % b;
	int x = 0;//������� ���������� �������
	for (headPtr;headPtr!=NULL;headPtr=headPtr->next)
	{
		for (SecondList * current = headPtr->headOFSecondList; current != NULL; current = current->next)
		{
				addToTailOfLists(newHeadPtr,copySecondList(current));
				x++;	//����������� ������� ���������� �������
			
			if (residue > 0)
			{
				if (x == average + 1)	//��������� ����������� ����������
				{
					newHeadPtr->next = creatFirstList();	//������� ����� ������� ������� ������
					
					newHeadPtr->next->prev = newHeadPtr;	//�������� ��� � ������������

					newHeadPtr = newHeadPtr->next;//���������� ��������� �� ����

					x = 0;//�������� ������� ���������� �������

					residue--;//��������� residue �� 1
				}
			}
			else
			{
				if (x == average)	//��������� ����������� ����������
				{
					newHeadPtr->next = creatFirstList();	//������� ����� ������� ������� ������

					newHeadPtr->next->prev = newHeadPtr;	//�������� ��� � ������������

					newHeadPtr = newHeadPtr->next;	//��������� ��������� �� ����

					x = 0;	//�������� ������� ���������� �������
				}
			}
		}
	}
	return newHead;
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
				showSecondList(currentSecList);
			}
		}
	}
	
	return tmp;
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
void testing()
{
	system("cls");
	printf("Please, input count of Element (from 100 to 10 000)?\n");
	int n = getNumber(100, 10000);

}


//////////////////��������� �������///////////////////////////////
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






