#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REF 1000
#define MAX_FRAMES 7

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

  /* Generate random page reference string (0–9) */
  srand(time(NULL));
  printf("Reference String:\n");
  for (int i = 0; i < pages; i++)
  {
    page[i] = rand() % 10;
    printf("%d ", page[i]);
  }

  int frame[frames];
  int faults = 0;
  int index = 0; // Points to next frame to replace (FIFO order)

  // Initialize frames as empty
  for (int i = 0; i < frames; i++)
    frame[i] = -1;

  for (int i = 0; i < pages; i++)
  {
    int found = 0;

    // Check for page hit
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] == page[i])
      {
        found = 1;
        break;
      }
    }

    // If page not found → Page Fault
    if (!found)
    {
      frame[index] = page[i];
      index = (index + 1) % frames; // Circular replacement
      faults++;
    }

    // Display frame status
    printf("\nFrames: ");
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
  }

  printf("\n\nTotal Page Faults = %d\n", faults);

  return 0;
}