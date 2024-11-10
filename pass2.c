#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	main(void)
{
	char location[20], label[20], opcode[20], operand[20], obj[20];
	char optabcode[20], opaddr[20];
	char symname[20], symaddr[20];
	int pgmsize = 23;
	int length = 30;
	int startaddr;

	FILE *finput, *foptab, *fsymtab, *fassemlist, *fobj;
	finput = fopen("input.txt", "r");
	foptab = fopen("optab.txt", "r");
	fsymtab = fopen("symtab.txt", "r");
	fassemlist = fopen("fassemlist.txt", "w");
	fobj = fopen("object.txt", "w");

	fscanf(finput, "%s %s %s %s", location, label, opcode, operand);
	startaddr = atoi(operand);

	fprintf(fassemlist, " %s %s %s\n", label, opcode, operand);
	fprintf(fobj, "H%s^%06d^%06d\n", label, atoi(operand), pgmsize);
	fprintf(fobj, "T%06d^%d^", atoi(operand), length);

	while (fscanf(finput, "%s %s %s %s", location, label, opcode, operand) == 4)
	{
		if (strcmp(opcode, "END") != 0)
		{
			if (strcmp(label, "-") == 0)
			{
				rewind(foptab);
				while (fscanf(foptab, "%s %s", optabcode, opaddr) == 2)
				{
					if (strcmp(optabcode, opcode) == 0)
					{
						rewind(fsymtab);
						while (fscanf(fsymtab, "%s %s", symaddr, symname) == 2)
						{
							if (strcmp(symname, operand) == 0)
							{
								fprintf(fassemlist, "%s %s %s %s %s\n",
									location, label, opcode, operand,
									strcat(opaddr, symaddr));
								fprintf(fobj, "%s^", opaddr);
								break ;
							}
						}
						break ;
					}
				}
			}
			else
			{
				fprintf(fassemlist, "%s %s %s %s ", location, label, opcode,
					operand);

				if (strcmp(opcode, "BYTE") == 0)
				{
					for (int i = 1; i < strlen(operand); i++)
					{
						if (operand[i] != '\'')
						{
							fprintf(fassemlist, "%X", operand[i]);
							fprintf(fobj, "%X", operand[i]);
						}
					}
				}
				else if (strcmp(opcode, "WORD") == 0)
				{
					fprintf(fassemlist, "%06d", atoi(operand));
					fprintf(fobj, "%06d", atoi(operand));
				}

				if (strcmp(opcode, "RESB") != 0 && strcmp(opcode, "RESW") != 0)
				{
					fprintf(fassemlist, "\n");
					fprintf(fobj, "^");
				}
			}
		}
		else
		{
			fprintf(fassemlist, "\nE%06d", startaddr);
		}
	}
	fclose(finput);
	fclose(foptab);
	fclose(fsymtab);
	fclose(fassemlist);
	fclose(fobj);
}