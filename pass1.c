#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	main(void)
{
	char	label[20], opcode[20], operand[20];
	char	optabcode[20], opaddr[20];
	char	symlabel[20], symaddr[20];

	int straddr, locctr, opcodeexist;
	FILE *finput, *foptab, *fsym, *fout;
	finput = fopen("input.txt", "r");
	foptab = fopen("optab.txt", "r");
	fsym = fopen("symtab.txt", "w");
	fout = fopen("output.txt", "w");
	fscanf(finput, "%s %s %s", label, opcode, operand);
	fprintf(fout, "%s %s %s\n", label, opcode, operand);
	straddr = (int)strtol(operand, NULL, 16);
	locctr = straddr;
	while (fscanf(finput, "%s %s %s", label, opcode, operand) == 3)
	{
		opcodeexist = 0;
		if (strcmp(opcode, "END") != 0)
		{
			if (strcmp(label, "-") == 0)
			{
				strcpy(label, " ");
				fprintf(fout, "%X %s %s %s\n", locctr, label, opcode, operand);
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
				locctr += 3;
			}
			else
			{
				fprintf(fout, "%X %s %s %s\n", locctr, label, opcode, operand);
				fprintf(fsym, "%s %X\n", label, locctr);
				if (strcmp(opcode, "WORD") == 0)
					locctr += 3;
				else if (strcmp(opcode, "RESW") == 0)
					locctr += (atoi(operand) * 3);
				else if (strcmp(opcode, "RESB") == 0)
					locctr += atoi(operand);
				else if (strcmp(opcode, "BYTE") == 0)
					locctr += strlen(operand) - 3;
			}
		}
		else
		{
			fprintf(fout, "  %s %X", opcode, straddr);
		}
	}
	printf("Program length is: %d", locctr - straddr);
	fclose(finput);
	fclose(foptab);
	fclose(fsym);
	fclose(fout);
}
