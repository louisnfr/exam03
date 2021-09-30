#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int		W;
int		H;
char	BC;
char	**TAB;

typedef struct s_draw
{
	char	t;
	float	x;
	float	y;
	float	r;
	char	c;	
}	t_draw;

int	error(FILE *fd, int err)
{
	if (err == 2 && (err = 1))
		write(1, "Error: Operation file corrupted\n", 33);
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

int	main(int ac, char **av)
{
	t_draw	draw;
	FILE	*fd;
	float	sqr;
	int		res;

	fd = NULL;
	if (ac != 2)
		return (error(fd, 1));
	if (fd = fopen(av[1], "r"))
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
					res = fscanf(fd, "\n%c %f %f %f %c", &draw.t, &draw.x, &draw.y, &draw.r, &draw.c);
					if (res == -1)
						return (error(fd, 0));
					else if (res != 5 || draw.r <= 0 || (draw.t != 'c' && draw.t != 'C'))
						break ;
					for (int line = 0; line < H; line++)
					{
						for (int col = 0; col < W; col++)
						{
							sqr = sqrtf((col - draw.x) * (col - draw.x) + (line - draw.y) * (line - draw.y));
							if (sqr <= draw.r)
								TAB[line][col] = draw.c;
						}
					}
				}
			}
		}
	}
	return (error(fd, 2));
}







