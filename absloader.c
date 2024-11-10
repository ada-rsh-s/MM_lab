#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	main(void)
{
	char name[20], pgmname[20], line[50], starttext[20];
	int textaddr;
	FILE *finput, *fout;
	finput = fopen("input.txt", "r");
	fout = fopen("out.txt", "w");
	fscanf(finput, "%s", line);
	int i = 2;
	for (; i <= 7; i++)
	{
		pgmname[i - 2] = line[i];
	}
	pgmname[i - 2] = '\0';
	printf("Enter the program name");
	scanf("%s", name);
	if (strcmp(pgmname, name) == 0)
	{
		while (fscanf(finput, "%s", line) !=EOF)
		{
			if (line[0] == 'T')
			{
				for (int i = 2; i <= 7; i++)
				{
					starttext[i - 2] = line[i];
				}
				starttext[i - 2] = '\0';
				textaddr = atoi(starttext);
				int j = 12;
				while (line[j] != '$')
				{
					if (line[j] != '^')
					{
						fprintf(fout, "%d\t %c%c\n", textaddr, line[j], line[j
							+ 1]);
						textaddr++;
						j += 2;
					}
					else
					{
						j++;
					}
				}
			}
		}
	}
	else
	{
		printf("SORRY MAN !");
	}

	fclose(finput);
	fclose(fout);
}