#include <stdio.h>
#include <memory.h>

#include <euler/config.h>

#define NUMSLOTS 100000

static u1 cubes[NUMSLOTS][10];
static u1 counts[NUMSLOTS];
static ULL smalls[NUMSLOTS];

int
main(int argc, char* argv[])
{
  ULL i;
  int done = 0;
  int j;

  memset(cubes, 0, sizeof(cubes));
  memset(counts, 0, sizeof(counts));
  memset(smalls, 0, sizeof(smalls));

  for(i = 0; !done && i < NUMSLOTS; i++)
    {
      u1 decomposed[10] = {0};
      ULL cube = i * i * i;

      //decompose
      while(cube != 0)
	{
	  decomposed[cube % 10]++;
	  cube /= 10;
	}

      // find match
      for(j = 0; j < NUMSLOTS; ++j)
	{
	  if(counts[j] == 0)
	    {
	      memcpy(cubes[j], decomposed, sizeof(decomposed));
	      counts[j]++;
	      smalls[j] = i * i * i;
	      break;
	    }
	  if(!memcmp(cubes[j], decomposed, sizeof(decomposed)))
	    {
	      counts[j]++;
	      if(counts[j] == 5)
		{
		  printf( ULLFMT "\n", smalls[j]);
		  done = 1;
		}
	    }
	}
    }

  return 0;
}
