#include <stdio.h>

int	main(void)
{
	int	found;
	int	replace = -1, least_recently_used;
	int	last_use;

	int i, j, k, ref_str[20], frames[20], ref_length, frame_length, PF = 0,
		PH = 0;
	printf("Enter the length of the reference string: ");
	scanf("%d", &ref_length);
	printf("Enter the reference string: ");
	for (i = 0; i < ref_length; i++)
	{
		scanf("%d", &ref_str[i]);
	}
	printf("Enter the number of frames: ");
	scanf("%d", &frame_length);
	for (i = 0; i < frame_length; i++)
	{
		frames[i] = -1;
	}
	printf("\nThe Page Replacement process is \n");
	for (i = 0; i < ref_length; i++)
	{
		found = 0;
		for (j = 0; j < frame_length; j++)
		{
			if (ref_str[i] == frames[j])
			{
				found = 1;
				PH++;
				break ;
			}
		}
		if (!found)
		{
			replace = -1, least_recently_used = i;
			for (j = 0; j < frame_length; j++)
			{
				last_use = -1;
				for (k = i - 1; k >= 0; k--)
				{
					if (frames[j] == ref_str[k])
					{
						last_use = k;
						break ;
					}
				}
				if (last_use == -1)
				{ // This frame was never used
					replace = j;
					break ;
				}
				if (last_use < least_recently_used)
				{
					least_recently_used = last_use;
					replace = j;
				}
			}
			frames[replace] = ref_str[i];
			PF++;
		}
		for (j = 0; j < frame_length; j++)
			printf("\t%d", frames[j]);
		if (found)
			printf("\tPH No. %d\n", PH);
		else
			printf("\tPF No. %d\n", PF);
	}
	printf("\nThe number of page faults using LRU algorithm: %d\n", PF);
	printf("\nThe number of page hits using LRU algorithm: %d\n", PH);
}
