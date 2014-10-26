#include <stdio.h>

int
main(int argc, char* argv[])
{
	unsigned long long h, p, t;

/*	for(h = 1, p = 1, t = 1; h < 100000; ++h)*/
	for(h = 143, p = 165, t = 285; h < 100000; ++h)
	{
		unsigned long long hex = h * (2 * h - 1);
		unsigned long long pen;
		unsigned long long tri;

		do {
			pen = p * (3 * p - 1) / 2;
			if(pen==hex) break;
			p++;
		} while(pen < hex);
		do {
			tri = t * (t + 1) / 2;
			if(tri==hex) break;
			t++;
		} while(tri < hex);
		if(h%1000==0)printf("%llu: %llu %llu %llu\n", h, tri, pen, hex);
		if((tri==pen)&&(tri==hex))
		{
			printf("%llu\n", hex);
		}
	}
	return 0;
}

