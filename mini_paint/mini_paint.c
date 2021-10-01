#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int		W;
int		H;
char	BC;
char	**TAB;

typedef struct s_dw
{
	char	t;
	float	x;
	float	y;
	float	r;
	char	c;
}	t_dw;

int	error(FILE *fd, int err)
{
	if (err == 2 && (err = 1))
		write(1, "Error: Operation file corrupted\n", 32);
	else if (err == 1)
		write(1, "Error: argument\n", 16);
	else
	{
		for (int i = 0; i < H; i++)
		{
			write(1, TAB[i], W);
			write(1, "\n", 1);
		}
	}
	if (fd)
		fclose(fd);
	return (err);
}

float square(float a)
{
	return (a * a);
}

float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = square(x1 - x2);
	dist_y = square(y1 - y2);
	return (dist_x + dist_y);
}

int in_circle(float x, float y, t_dw dw)
{
	float distance;
	float distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, dw.x, dw.y));
	distance = distance_sqrt - dw.r;
	if (distance <= 0.00000000)
	{
		if (distance <= -1.00000000)
			return (1); // Inside
		return (2);		// Border
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_dw	dw;
	FILE	*fd;
	int		sqr;
	int		res;

	fd = NULL;
	if (ac != 2)
		return (error(fd, 1));
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &W, &H, &BC)) == 3)
		{
			if (W > 0 && W <= 300 && H > 0 && H <= 300)
			{
				TAB = malloc(sizeof(char *) * H);
				for (int i = 0; i < H; i++)
				{
					TAB[i] = malloc(sizeof(char) * W);
					memset(TAB[i], BC, W);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %c", &dw.t, &dw.x, &dw.y, &dw.r, &dw.c);
					if (res == -1)
						return (error(fd, 0));
					if (res != 5 || dw.r <= 0 || (dw.t != 'c' && dw.t != 'C'))
						break ;
					for (int line = 0; line < H; line++)
					{
						for (int col = 0; col < W; col++)
						{
							sqr = in_circle(col, line, dw);
							if (sqr == 2 || ((sqr == 1 || sqr == 2) && dw.t == 'C'))
								TAB[line][col] = dw.c;
						}
					}
				}
			}
		}
	}
	return (error(fd, 2));
}

























