#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
unsigned a, b;
pthread_mutex_t m;

unsigned gcdk(unsigned a, unsigned b)
{
	if (a == 0 || b == 0)
		return 0;

	if (a == b)
		return a;

	if (a > b)
		return gcdk(a-b, b);
	return gcdk(a, b-a);
}

void check_gcd(unsigned a_in, unsigned b_in, unsigned gcd)
{
	unsigned guessed_gcd = gcdk(a_in,b_in);

	assert(gcd>=guessed_gcd);
}



void* dec_a(void* arg)
{
	(void)arg;

	while(a!=b)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);
	
	}


	return 0;
}

void* dec_b(void* arg)
{
	(void)arg;

	while(a!=b)
	{
		pthread_mutex_lock(&m);
		if(b>a)
			b=b-a;
		pthread_mutex_unlock(&m);
	}

	return 0;
}



unsigned start(unsigned a_in, unsigned b_in)
{
	a=a_in;
	b=b_in;

	pthread_t t1, t2;

	pthread_create(&t1, 0, dec_a, 0);
	pthread_create(&t2, 0, dec_b, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return a;
}



int main()
{
  // for testing with small unwinding bounds
	srand(time(NULL));
  unsigned a_in=rand();//__VERIFIER_nondet_uint(); //=8;
  unsigned b_in=rand();//__VERIFIER_nondet_uint(); //=6;

  // __VERIFIER_assume(a_in>0);
  // __VERIFIER_assume(b_in>0);
  check_gcd(a_in, b_in, start(a_in, b_in));
  return 0;
}