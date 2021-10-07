#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int	main(int ac, char **av)
{
	t_dw	dw;
	FILE	*fd;
	int		res;
	int		sqr;
	
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
					else if (res != 5 || dw.r <= 0 || (dw.t != 'c' && dw.t != 'C'))
						break ;
					for (int line = 0; line < H; line++)
					{
						for (int col = 0; col < W; col++)
						{
							sqr = sqrtf(powf(col - dw.x, 2) + powf(line - dw.y, 2));
							if (sqr <= dw.r)
								if ((sqr + 1 > dw.r && dw.t == 'c') || dw.t == 'C')
									TAB[line][col] = dw.c;
						}
					}
				}
			}
		}
	}
	return (error(fd, 2));
}
