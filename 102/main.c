/**
 * Project Euler Problem 102
 * Find number of triangles which contain origin.
 *
 * The idea behind this solution:
 * Triangle have three sides. Eash side is the line
 * or vector.
 * Origin is inside of triangle iff for each side it
 * is at the same side of the side line as the third
 * point.
 * 
 */
#include <stdio.h>

#include <euler/assert.h>

#define FILENAME "triangles.txt"
#define ORIGIN 0, 0

#define SGN(x) (x == 0 ? 0 : x > 0 ? 1 : -1)

static int
point_position(int xa, int ya, int xb, int yb, int xp, int yp)
{
	int s = (xb - xa)*(yp - ya) - (yb - ya)*(xp - xa);

	return SGN(s);
}

int
main(int argc, char* argv[])
{
	int count;
	FILE* fi = fopen(FILENAME, "rb");
	if(fi == NULL)
	{
		fprintf(stderr, "Can't open %s\n", FILENAME);
		return -1;
	}
	for(count = 0; !feof(fi);)
	{
		int x1, y1, x2, y2, x3, y3;
		int p0, z0, p1, z1, p2, z2;

		if(fscanf(fi, "%d,%d,%d,%d,%d,%d\n", &x1, &y1, &x2, &y2, &x3, &y3)!=6) FAIL("Can't read from " FILENAME);
		p0 = point_position(x1, y1, x2, y2, x3, y3);
		z0 = point_position(x1, y1, x2, y2, ORIGIN);
		p1 = point_position(x1, y1, x3, y3, x2, y2);
		z1 = point_position(x1, y1, x3, y3, ORIGIN);
		p2 = point_position(x2, y2, x3, y3, x1, y1);
		z2 = point_position(x2, y2, x3, y3, ORIGIN);

		if(p0 == z0 && p1 == z1 && p2 == z2) {
			count++;
		}
	}
	fclose(fi);
	printf("%d\n", count);
	return 0;
}

