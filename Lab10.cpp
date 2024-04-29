#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define GROUP 6
#define MAX_STRING_LENGTH 130
typedef struct list
{
	char 	surname[50];
	char	name[50];
	char	date[11];
	int		marks[5];
	int		rate;
	list* next;
}list;
void struct_print(list* m);
void define_and_delete(list** head);
void insert_node(list** head, list* student);
void clean(list* poin);
void struct_input(list* head, FILE* name);
int main(void)
{
	char banned[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9','!','@', '#', '$', '%', '^', '&', '*', '(', ')','-', '_','+','=','[',']', '{', '}', ':',';', '|','/','?','.','"',','};
	FILE* exam;
	char masiv[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	if(fopen_s(&exam, "list.txt", "r"))
	{
		printf("Can't open the file");
		return 0;
	}
	list* head=NULL;
	for (int i = 0; i < GROUP; i++)
	{
		list* p0 = (struct list*)malloc(sizeof(list));
		fscanf_s(exam, "%s %s %s", p0->surname, 50, p0->name, 50, p0->date, 11);
		
		for (int j = 0; j < 5; j++)
		{
			fscanf_s(exam, "%d", &p0->marks[j]);
			p0->rate += p0->marks[j];
		}
		insert_node(&head,p0);
	}
	printf("Do you want to input an information about other student?( Y- if yes. Other letters will continue the program without this part...)\n");
	char lett;
	scanf_s("%c", &lett, 2);
	int num_of_stud = GROUP;
		while (lett == 'Y' || lett == 'y')
		{
			list* X = (list*)malloc(sizeof(list));
			num_of_stud++;
			printf("\nplease, input the data about your student...");
			scanf_s("%s %s %s", X->surname, 50, X->name, 50, X->date, 11);
			printf("\nplease, input his/her marks...");
			int  m = 0, r = 0, q=0;
			for (int j = 0; j < 5; j++)
			{
				scanf_s("%d", &(X->marks[j]));
				X->rate += X->marks[j];
				if (X->marks[j] > 0 && X->marks[j] < 6 && X->marks[j]!='\n')
					q++;
			} 
			if (q!=5)
			{
				printf("Non-correct data, try again...\n");
				break;
			}
			for (int i = 0; i < 50; i++)
			{

				for (int j = 0; j < 36; j++)
				{
					if (X->surname[i] == banned[j])
					{
						m++;
					}
				}
			}
			if (m != 0)//перевірка на коректність
			{

				printf("Non-correct data, try again...\n");
				
				break;
			}
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 26; j++)
				{
					if (X->name[i] == banned[j])
					{
						m++;
					}
				}

			}
			if (m != 0)//перевірка на коректність
			{
				printf("Non-correct data, try again...");
				break;

			}
			for (int i=0;i<11;i++)
			{
				for (int j = 0; j < 11; j++)
				{
					if (X->date[i] == masiv[j])
					{
						r++;
					}
				}
			}
			if(r!=8)//перевірка на коректність
			{
					printf("Non-correct data, try again...");
					break;
			}

			if ((X->date[2] != '.') || (X->date[5] != '.'))//перевірка на коректність
			{
				printf("Non-correct data, try again...");
				break;
			}
			else
			{
				insert_node(&head, X);
				printf("Do you want to input an information about other student?\n");
				rewind(stdin);
				scanf_s("%c", &lett, 2);
			}
		}
		FILE* journal;
		char name[50];
		printf("\n in which file will go saved results?(.txt)\n");
		scanf_s("%s", name, 50);
		fopen_s(&journal, name, "w+");
	define_and_delete(&head);
	struct_print(head);
	struct_input(head, journal);
	clean(head);
	fclose(exam);
	fclose(journal);
	return 0;
}
void struct_input(list* head, FILE* name)
{
	fprintf(name, "\n%s %s %s ", head->surname, head->name, head->date);

	for (int j = 0; j < 5; j++)
	{
		fprintf(name, "%d ", head->marks[j]);
	}
	if (head->next == NULL)
		return;
	struct_input(head->next, name);
}
void struct_print(list* head)
{
	printf("\n%s %s %s ", head->surname, head->name, head->date);

	for (int j = 0; j < 5; j++)
	{
			printf("%d ", head->marks[j]);
	}
	if (head->next == NULL)
			return;
		struct_print(head->next);
}
void define_and_delete(list** head)
{
	list* local=*head;
	list* prev = NULL;
	int step = 0;
	while(local!=NULL)
	{
		int amount = 0;
		for (int j = 0; j < 5; j++)
		{
			if (local->marks[j] == 2)
				amount++;
		}

		if (amount == 2)
		{

			if (local==*(head))
			{
				(*head) = (*head)->next;
				free(local);
				local = (*head);
			}
			else
			{
				prev->next = local ->next;
				free(local);
				local = prev->next;
			}
		}
		else
		{
			prev = local;
			local = local->next;
		}
	}
}
void insert_node(list** head, list* student)
{

	if (!(*head))
	{
		(*head) = student;
		(*head)->next = NULL;
	}	
	else
	{
		if ((*head)->rate<student->rate) 
		{//додавання в початок списку
			student->next = *head;
			*head=student;
			return;
		}
		list* current = *head;
		while (current->next) {
			if ((current->rate > student->rate) && (student -> rate > current->next->rate))
			{
				student->next=current->next;
				current->next = student;
				return;
			}
			else 
			{
				current = current->next;
			}
		}
		current->next = student;
	}
	student->next = NULL;
}
void clean(list* poin)
{
	if (poin == NULL)
		return;
	clean(poin->next);
	free(poin);
}
