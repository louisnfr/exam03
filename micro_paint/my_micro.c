#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
	float	w;
	float	h;
	char	c;
}	t_dw;

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

int in_rect(float x, float y, t_dw dw)
{
	if ((((x < dw.x) || (dw.x + dw.w < x)) || (y < dw.y)) || (dw.y + dw.h < y))
		return (0);
	if (((x - dw.x < 1.00000000) || ((dw.x + dw.w) - x < 1.00000000)) ||
		((y - dw.y < 1.00000000 || ((dw.y + dw.h) - y < 1.00000000))))
		return (2);
	return (1);
}

int	main(int ac, char **av)
{
	t_dw	dw;
	FILE 	*fd;
	int		res;
	int		rect;

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
					res = fscanf(fd, "\n%c %f %f %f %f %c", &dw.t, &dw.x, &dw.y, &dw.w, &dw.h, &dw.c);
					if (res == -1)
						return (error(fd, 0));
					else if (res != 6 || dw.w <= 0 || dw.h <= 0 || (dw.t != 'r' && dw.t != 'R'))
						break ;
					for (int line = 0; line < H; line++)
					{
						for (int col = 0; col < W; col++)
						{
							rect = in_rect(col, line, dw);
							if ((rect == 2 && dw.t == 'r') || ((rect == 1 || rect == 2) && dw.t == 'R'))
								TAB[line][col] = dw.c;
						}
					}
				}
			}
		}
	}
	return (error(fd, 2));
}

