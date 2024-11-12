#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the linked list node
struct		objCode
{
	char	lab[20];
	char	obNu[20];
	char	loc[20];
	struct objCode *next; // Pointer to the next node
};

void	main(void)
{
	char label[20], opcode[20], operand[20], name[20];
	char op[20], nu[20];
	struct objCode *head = NULL, *current;
	bool flag;
	char hex[3];
	int len;

	int locctr, startAddr, prgLen;
	int lc; // Declare lc only once
	FILE *f1, *f2, *f3, *f4;
	f1 = fopen("input.txt", "r");
	f2 = fopen("optab.txt", "r");
	f4 = fopen("output.txt", "w+");
	f3 = fopen("symtab.txt", "w+");
	head = NULL, current = NULL;
	struct objCode *newNode, *temp; // Declare newNode and temp only once
	// Read the first line of the input file
	fscanf(f1, "%s %s %s", label, opcode, operand);
	if (strcmp(opcode, "START") == 0)
	{
		locctr = atoi(operand);
		startAddr = locctr;
		strcpy(name, label);
	}
	fscanf(f1, "%s %s %s", label, opcode, operand);
	while (strcmp(opcode, "END") != 0)
	{
		if (strcmp(label, "--") == 0)
		{
			flag = false;
			fseek(f2, 0, SEEK_SET);
			while (!feof(f2))
			{
				fscanf(f2, "%s %s", op, nu);
				if (strcmp(op, opcode) == 0)
				{
					flag = true;
					break ;
				}
			}
			if (flag)
			{
				// Allocate a new node for the linked list
				newNode = (struct objCode *)malloc(sizeof(struct objCode));
				strcpy(newNode->lab, operand);
				strcpy(newNode->obNu, nu);
				strcpy(newNode->loc, "");
				newNode->next = NULL;
				// Insert the new node into the linked list
				if (head == NULL)
				{
					head = newNode;
				}
				else
				{
					current->next = newNode;
				}
				current = newNode;
				locctr += 3;
			}
			else
			{
				printf("No such opcode exiting...\n");
				return ;
			}
		}
		else
		{
			temp = head;
			while (temp != NULL)
			{
				if (strcmp(label, temp->lab) == 0)
				{
					sprintf(temp->loc, "%d", locctr);
					break ;
				}
				temp = temp->next;
			}
			if (strcmp(opcode, "BYTE") == 0)
			{
				char obj[20] = ""; // Initialize to an empty string
				for (int k = 0, l = 2; l < strlen(operand) - 1; l++, k++)
				{
					sprintf(hex, "%02X", operand[l]);
					strcat(obj, hex);
				}
				newNode = (struct objCode *)malloc(sizeof(struct objCode));
				strcpy(newNode->lab, opcode);
				strcpy(newNode->obNu, "*");
				strcpy(newNode->loc, obj);
				newNode->next = NULL;
				if (head == NULL)
				{
					head = newNode;
				}
				else
				{
					current->next = newNode;
				}
				current = newNode;
				len = strlen(operand) - 3;
				locctr += len;
			}
			else if (strcmp(opcode, "WORD") == 0)
			{
				newNode = (struct objCode *)malloc(sizeof(struct objCode));
				strcpy(newNode->lab, opcode);
				strcpy(newNode->obNu, "*");
				sprintf(newNode->loc, "%06d", atoi(operand));
				newNode->next = NULL;
				if (head == NULL)
				{
					head = newNode;
				}
				else
				{
					current->next = newNode;
				}
				current = newNode;
				locctr += 3;
			}
			else if (strcmp(opcode, "RESB") == 0)
			{
				lc = atoi(operand); // Use the previously declared lc variable
				locctr += lc;
			}
			else if (strcmp(opcode, "RESW") == 0)
			{
				lc = atoi(operand); // Reuse the previously declared lc variable
				locctr += (3 * lc);
			}
		}
		fscanf(f1, "%s %s %s", label, opcode, operand);
	}
	prgLen = locctr - startAddr;
	fprintf(f4, "H^%s^%d\nT^%06d^%d", name, startAddr, startAddr, prgLen);
	temp = head;
	while (temp != NULL)
	{
		if (strcmp(temp->obNu, "*") != 0)
		{
			fprintf(f3, "%s %s\n", temp->lab, temp->loc);
			fprintf(f4, "^%s%s", temp->obNu, temp->loc);
		}
		else
		{
			fprintf(f4, "^%s", temp->loc);
		}
		temp = temp->next;
	}
	fprintf(f4, "\nE^%06d", startAddr);
	// Print the linked list contents to the console for verification
	temp = head;
	while (temp != NULL)
	{
		printf("%s %s %s\n", temp->lab, temp->obNu, temp->loc);
		temp = temp->next;
	}
	// Free the memory allocated for the linked list
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return;
}