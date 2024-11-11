#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct		objCode
{
	char	lab[20];
	char	obNu[20];
	char	loc[20];
};

void	main(void)
{
	char label[20], opcode[20], operand[20], name[20];
	char op[20], nu[20];
	int locctr, startAddr, prgLen;

	FILE *f1, *f2, *f3, *f4;
	f1 = fopen("input.txt", "r");
	f2 = fopen("optab.txt", "r");
	f4 = fopen("output.txt", "w+");
	f3 = fopen("symtab.txt", "w+");

	struct objCode objs[20];

	fscanf(f1, "%s %s %s", label, opcode, operand);
	if (strcmp(opcode, "START") == 0)
	{
		locctr = atoi(operand);
		startAddr = locctr;
		strcpy(name, label);
	}

	int si = 0;
	fscanf(f1, "%s %s %s", label, opcode, operand);
	while (strcmp(opcode, "END") != 0)
	{
		if (strcmp(label, "--") == 0)
		{
			bool flag = false;
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
				strcpy(objs[si].lab, operand);
				strcpy(objs[si].obNu, nu);
				strcpy(objs[si].loc, "****");
				locctr += 3;
				si++;
			}
			else
			{
				printf("No such opcode exiting...");
				return ;
			}
		}
		else
		{
			int j = 0;

			while (j < si)
			{
				if (strcmp(label, objs[j].lab) == 0)
				{
					sprintf(objs[j].loc, "%d", locctr);
					break ;
				}
				j++;
			}
			if (strcmp(opcode, "BYTE") == 0)
			{
				char obj[20];
				for (int k = 0, l = 2; l < strlen(operand) - 1; l++, k++)
				{
					char hex[3];
					sprintf(hex, "%02X", operand[l]);
					strcat(obj, hex);
				}
				strcpy(objs[si].lab, opcode);
				strcpy(objs[si].obNu, "*");
				strcpy(objs[si].loc, obj);
				si++;
				int len = strlen(operand) - 3;
				locctr += len;
			}
			else if (strcmp(opcode, "WORD") == 0)
			{
				strcpy(objs[si].lab, opcode);
				strcpy(objs[si].obNu, "*");
				sprintf(objs[si].loc, "%06d", atoi(operand));
				si++;
				locctr += 3;
			}
			else if (strcmp(opcode, "RESB") == 0)
			{
				int lc = atoi(operand);
				locctr += lc;
			}
			else if (strcmp(opcode, "RESW") == 0)
			{
				int lc = atoi(operand);
				locctr += (3 * lc);
			}
		}
		fscanf(f1, "%s %s %s", label, opcode, operand);
	}

	prgLen = locctr - startAddr;
	fprintf(f4, "H^%s^%d\nT^%06d^%d", name, startAddr, startAddr, prgLen);
	for (int i = 0; i < si; i++)
	{
		if (strcmp(objs[i].obNu, "*") != 0)
		{
			fprintf(f3, "%s %s\n", objs[i].lab, objs[i].loc);
			fprintf(f4, "^%s%s", objs[i].obNu, objs[i].loc);
			continue ;
		}
		fprintf(f4, "^%s", objs[i].loc);
	}
	fprintf(f4, "\nE^%06d", startAddr);

	for (int i = 0; i < si; i++)
	{
		printf("%s %s %s\n", objs[i].lab, objs[i].obNu, objs[i].loc);
	}

	return ;
}