/* te.c: error message control, input line count */
# include "t.h"

void
error(char *s)
{
	fprintf(stderr, "\n%s:%d: %s\n", ifile, iline, s);
	fprintf(stderr, "tbl quits\n");
	exit(1);
}


char	*
gets1(char *s, int size)
{
	char	*p, *ns;
	int	nbl;

	iline++;
	ns = s;
	p = fgetln(tabin, &nbl);
	while (p == 0) {
		if (swapin() == 0)
			return(0);
		p = fgetln(tabin, &nbl);
	}
	if(p != 0 && p[nbl-1] == '\n')
		nbl--;
	if(nbl >= size)
		error("input buffer too small");
	p[nbl] = 0;
	strcpy(s, p);
	s += nbl;
	for (nbl = 0; *s == '\\' && s > ns; s--)
		nbl++;
	if (linstart && nbl % 2) /* fold escaped nl if in table */
		gets1(s + 1, size - (s-ns));

	return(p);
}


# define BACKMAX 500
char	backup[BACKMAX];
char	*backp = backup;

void
un1getc(int c)
{
	if (c == '\n')
		iline--;
	*backp++ = c;
	if (backp >= backup + BACKMAX)
		error("too much backup");
}


int
get1char(void)
{
	int	c;
	if (backp > backup)
		c = *--backp;
	else
		c = fgetc(tabin);
	if (c == 0) /* EOF */ {
		if (swapin() == 0)
			error("unexpected EOF");
		c = fgetc(tabin);
	}
	if (c == '\n')
		iline++;
	return(c);
}


