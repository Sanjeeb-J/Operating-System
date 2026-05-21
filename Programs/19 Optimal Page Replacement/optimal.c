#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REF 1000
#define MAX_FRAMES 7

/* Function to generate reference string */
void generateReferenceString(int page[], int pages)
{
  srand(time(NULL));
  printf("Reference String:\n");

  for (int i = 0; i < pages; i++)
  {
    page[i] = rand() % 10;
    printf("%d ", page[i]);
  }
  printf("\n");
}

/* Function to perform Optimal Page Replacement */
void optimalPageReplacement(int page[], int pages, int frames)
{
  int frame[MAX_FRAMES];
  int faults = 0;

  /* Initialize frames */
  for (int i = 0; i < frames; i++)
    frame[i] = -1;

  for (int i = 0; i < pages; i++)
  {
    int found = 0;

    /* Check for page hit */
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] == page[i])
      {
        found = 1;
        break;
      }
    }

    /* Page fault */
    if (!found)
    {
      int index = -1, farthest = -1;

      for (int j = 0; j < frames; j++)
      {
        if (frame[j] == -1)
        {
          index = j;
          break;
        }
      }

      if (index == -1)
      {

        for (int j = 0; j < frames; j++)
        {
          int k;

          for (k = i + 1; k < pages; k++)
          {
            if (frame[j] == page[k])
            {
              if (k > farthest)
              {
                farthest = k;
                index = j;
              }
              break;
            }
          }

          /* If page not used again */
          if (k == pages)
          {
            index = j;
            break;
          }
        }
      }
      /* If empty frame exists */

      frame[index] = page[i];
      faults++;
    }

    /* Display frames */
    printf("Frames: ");
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
    printf("\n");
  }

  printf("\nTotal Page Faults = %d\n", faults);
}

/* Main Function */
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: %s <reference_string_length> <number_of_frames(1-7)>\n", argv[0]);
    return 1;
  }

  int pages = atoi(argv[1]);
  int frames = atoi(argv[2]);

  if (frames < 1 || frames > 7)
  {
    printf("Number of frames must be between 1 and 7\n");
    return 1;
  }

  int page[MAX_REF];

  generateReferenceString(page, pages);
  optimalPageReplacement(page, pages, frames);

  return 0;
}