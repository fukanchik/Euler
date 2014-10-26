#include <stdio.h>
#include <stdlib.h>

#include <euler/assert.h>

#define INFILE "matrix.txt" 

#define min(x,y) (x)<(y)?(x):(y)

static int matrix[]=
{
	131, 673, 234, 103,  18,
	201,  96, 342, 965, 150,
	630, 803, 746, 422, 111,
	537, 699, 497, 121, 956,
	805, 732, 524,  37, 331
};

static int
M(int *matrix, const int w, int h, int x, int y)
{
	int mr, mb;
	if(x+1>w) mr = 0;
	else mr = matrix[y*w+x];
	if(y+1>=h) mb = 0;
	else mb = matrix[(y+1)*w+x-1];
	if(mr==0)mr=mb;
	if(mb==0)mb=mr;
	return min(mr, mb);
}

static int
M2(int *matrix, const int w, int h, int x, int y)
{
	int mr, mb;
	if(x+1>w) mr = 0;
	else mr = matrix[y*w+x+1];
	if(y+1>=h) mb = 0;
	else mb = matrix[(y+1)*w+x];
	if(mr==0)mr=mb;
	if(mb==0)mb=mr;
	return min(mr, mb);
}

static int
find_path(int *matrix, const int w, int h)
{
	int x = w - 1;
	int y = h;
	int j;

	for(;x>0;--x)
	{
		y = h - 1;
		for(j=x;j<=w;++j)
		{	
			//int val = matrix[y * w + j - 1];
			matrix[y * w + j - 1] += M(matrix, w, h, j, y);
			y--;
		}
	}
	y = h-2;
	for(;y>0;--y)
	{
		x = 0;
		for(j=y;j>=0;--j)
		{
			//int val = matrix[j * w + x];
			matrix[j * w + x] += M2(matrix, w, h, x, j);
			++x;
		}
	}
	matrix[0]+=min(matrix[1], matrix[w]);

	return matrix[0];
}

static int mat2[80*80];
int
main(int argc, char* argv[])
{
	FILE *fi = fopen("matrix.txt", "r");
	int i;
	for(i=0;i<80*80;++i)
		if(fscanf(fi, "%d,", &mat2[i]) != 1) FAIL("Can't read number from "INFILE);
	fclose(fi);
	printf("%d\n", find_path(matrix, 5, 5));
	if(1)printf("%d\n", find_path(mat2, 80, 80));
	return 0;
}

