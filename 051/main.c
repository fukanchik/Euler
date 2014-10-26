#include <stdio.h>
#include <string.h>
#include <euler/config.h>
#include <euler/primes.h>

#define MAXPRIME 1000000

#define NGROUPS 100
struct prime_list_t primes;
int groups[NGROUPS];

int numlen(ULL i)
{
  int len = 0;

  while(i > 0) {
    len++;
    i /= 10;
  }
  return len;
}

void numtobuf(int prime, int *buf, int len)
{
  int i;
  for(i=0;prime>0;++i) {
    buf[i]=prime%10;
    prime=prime/10;
  }
}

int
find_groups(struct prime_list_t* primes, int pos, int prime, void *arg)
{
  int *groups = (int*)arg;
  int len = numlen(prime);

  groups[1]=0;
  if(groups[len] == 0) {
    groups[len]=pos;
  }

  if(len >= NGROUPS) return 1;

  return 0;
}

struct search
{
  int len;

  int slotslen;
  int *slots;
  int digit;

  int count;
  int *fixedpos, *fixed, fixedlen;
};

int
filter_out(struct prime_list_t * primes, int pos, int prime, void * arg)
{
  struct search *s = (struct search*)arg;
  int i;
  
  int buf[s->len];
  numtobuf(prime, buf, s->len);

  for(i=0;i<s->fixedlen;++i) {
    if(buf[s->fixedpos[i]] != s->fixed[s->fixedpos[i]]) return 0;
  }
  for(i=0; i < s->slotslen;++i) {
    if(buf[s->slots[i]] != s->digit) {
      return 0;
    }
  }
  s->count++;

  return 0;
}

int
main(int argc, char *argv[])
{
  int len, j;

  primes_init_fill(&primes, MAXPRIME);

  primes_for_each_extra(0, MAXPRIME, &primes, find_groups, groups);

  int maxcount=0;
  int maxfixed[6];

#define SLOTSLEN 3
  for(len = 5; len < 6; ++len) {
    for(j=groups[len];j<groups[len+1];++j) {
      struct search s;
      int prime = primes.primes[j];
      //KNOWN: int slots[SLOTSLEN]={1,2};
      //int fixedpos[3]={0,3,4};
      int slots[SLOTSLEN]={0,1,4};
      int fixedpos[2]={2,3};
      int fixed[5];
      int i;

      numtobuf(prime, fixed, 5);

      s.slotslen=SLOTSLEN;
      s.slots = slots;
      s.len=len;
      s.fixedpos=fixedpos;
      s.fixed=fixed;
      s.fixedlen=s.len-s.slotslen;
      s.count=0;

      for(i=0;i<=9;++i) {
	s.digit = i;
	primes_for_each_extra(groups[len], groups[len+1], &primes, filter_out, &s);
      }
      if(s.count>maxcount) {
	memcpy(maxfixed, fixed, len*sizeof(int));
	maxcount=s.count;
      }
    }
  }

  printf("maxcount=%d [%d%d%d%d%d]\n", maxcount, maxfixed[0], maxfixed[1], maxfixed[2], maxfixed[3], maxfixed[4]);

  return 0;
}
