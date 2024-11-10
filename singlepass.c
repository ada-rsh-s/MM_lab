#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	main(void)
{  
	FILE *finput, *foptab, *fsym, *fout, *fobj;
	finput = fopen("input.txt", "r");
	foptab = fopen("optab.txt", "r");
	fsym = fopen("symtab.txt", "w");
	fout = fopen("out.txt", "w+");
	fobj = fopen("obj.txt", "w");

	char label[20], opcode[20], operand[20];
	char optabcode[20], opaddr[20];
	char symlabel[20], symaddr[20];
	char pgmname[10];
	char outopcode[20], outlabel[20], outopaddr[20];
	int straddr, locctr, opcodeexist = 0;

	fscanf(finput, "%s %s %s", label, opcode, operand);
	strcpy(pgmname, label);

	straddr = (int)strtol(operand, NULL, 16);
	locctr = straddr;

	while (fscanf(finput, "%s %s %s", label, opcode, operand))
	{
		opcodeexist = 0;
		if (strcmp(opcode, "END") != 0)
		{
			if (strcmp(label, "-") == 0)
			{
				rewind(foptab);
				while (fscanf(foptab, "%s %s", optabcode, opaddr) == 2)
				{
					if (strcmp(optabcode, opcode) == 0)
					{
						opcodeexist = 1;
						break ;
					}
				}
				if (opcodeexist == 0)
				{
					printf("Error: Opcode %s not found in optab.\n", opcode);
					break ;
				}
				else
				{
					fprintf(fout, "%s %s %s", opcode, operand, opaddr);
				}
				locctr += 3;
			}
			else
			{
				fprintf(fsym, "%s %X\n", label, locctr);
				if (strcmp(opcode, "WORD") == 0)
					locctr += 3;
				else if (strcmp(opcode, "RESW") == 0)
					locctr += (atoi(operand) * 3);
				else if (strcmp(opcode, "RESB") == 0)
					locctr += atoi(operand);
				else if (strcmp(opcode, "BYTE") == 0)
					locctr += strlen(operand) - 3;

				rewind(fout);
				while (fscanf(fout, "%s %s %s", outopcode, outlabel, outopaddr))
				{
					if (strcmp(outlabel, label) == 0)
					{
						fprintf(fout,"%X", locctr);
					}
				}
			}
		}
		
	}
}