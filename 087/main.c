#include <stdio.h>
#include <string.h>

#include <euler/primes.h>

#define LIMIT 50000000
#define SQ4 85
#define SQ3 369
#define SQ2 7072
#define NUMPRIMES 10000

static int count=0;
static prime_list_t primes;

static int solutions[LIMIT];

static void rec(int *p, int idx)
{
  if(idx==3) {
    int p0=primes.primes[p[0]];
    int p1=primes.primes[p[1]];
    int p2=primes.primes[p[2]];
    u8 num = (p0*p0)+(p1*p1*p1)+(p2*p2*p2*p2);
    if(num>=LIMIT)return;
    if(!solutions[num])
      count++;
    solutions[num]++;
    return;
  }
  int i;
  for(i=0;i<primes.count;++i) {
    int pr=primes.primes[i];
    if(idx==2&&pr>SQ4) break;
    if(idx==1&&pr>SQ3) break;
    if(idx==0&&pr>SQ2) break;
    p[idx]=i;
    rec(p, idx+1);
  }

}

int
main(int argc, char* argv[])
{
  int p[3];

  memset(solutions,0, sizeof(solutions));
  primes_init_fill(&primes, NUMPRIMES);

  rec(p, 0);

  primes_free(&primes);
  printf("Total %d\n", count);
  return 0;
}
