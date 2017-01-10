// flips.cpp : Defines the entry point for the console application.
//
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

double f(int, int *i, int *hist);

int main(int argc, char** argv )
{
	int hist[1000];
	time_t timer;
        int flips = 0;
	for (int i=0; i< 1000; i++)
		hist[i] = 0;
	if (argc > 1)
		flips = atoi(argv[1]);
	else
		flips = 1000000000;
	int resultsCnt = 0;
	int headsInARow = 0;
	time(&timer);
	srand(timer);
	int start = timer;
	printf("Probability of heads: %f\n", f(flips, &headsInARow, hist));
	time(&timer);
	int elapsedSeconds = timer - start;
	elapsedSeconds = (elapsedSeconds == 0) ? 1 : elapsedSeconds;
	printf("Seconds: %d, Flips per second: %d\n", elapsedSeconds, flips / elapsedSeconds);		
	printf("Longest run of heads: %d\n", headsInARow);
	printf("[");
	for (int i=999; i>0; i--)
	{
		if (hist[i]>0)
		{
			printf("(%d,%d)",i,hist[i]);
		}
	}
	printf("]\n");
	return 0;
}

double f(int flips, int *headsInARow, int *hist)
{
	int heads = 0;
	int currentRun = 0;
	for (int i = 0; i < flips; i++)
	{
		int flip = rand() % 2;
		if (flip == 1)
		{
			heads++;
			currentRun += 1;
		}
		else
		{
			if (currentRun > 2)
			{
			    hist[currentRun]++;
			    *headsInARow = (*headsInARow < currentRun) ? currentRun : *headsInARow;
			}
			currentRun = 0;
		}
	}	
	if (currentRun)
	{
		*headsInARow = (*headsInARow < currentRun) ? currentRun : *headsInARow;
		hist[currentRun]++;
	}

	return heads / (double) flips;
}

