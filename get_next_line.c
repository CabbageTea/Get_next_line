#include "get_next_line.h"
#include <stdio.h>

int		ft_check_tmp(char **tmp, char **line, char *add, int mark, int x)
{
//	ft_putstr("\nin check_tmp\n");
	x = ft_strlen(*tmp);
	ft_putnbr(x);
	ft_putstr("\nHeymydude\n");
	while (mark <= x)
	{
		ft_putstr("\nam I getting to the loop?");
		if (*tmp[mark] == '\n') 
		{
			ft_putstr("\nI don't think I should be here");
			add = ft_strsub(*tmp, 0, mark); //this might have to be mark - 1, v might have to be + 1 ///THIS IS THE SEG FAULT
			*line = ft_strdup(add);
			*tmp = ft_strsub(*tmp, mark + 2, x - mark);
			ft_putnbr(1);
			return (1);
		}
		mark++;
	}

//	we're going to leave tmp alone. Since we strdup when we do *line
	mark = 0;
	return (mark);
}
//ft_final will not always return 0, remember that tmp is not always empty, and buf can have several '\n's, so put them in tmp, and return 1. 
int		ft_final(char *buf, char **tmp, char *add, char **line, int final)
{
	int i;
	int x;

	i = 0;
	final = 1;
	x = ft_strlen(buf);
	ft_putstr("\nIN FINAL\n");
	while (i <= x)
	{
		if (buf[i] == '\n')
		{
			add = ft_strsub(buf, 0, i);
			if (*tmp[0] != '\0')
				add = ft_strjoin(*tmp, add);
			*line = ft_strdup(add);
			*tmp = ft_strsub(*tmp, i + 1, x - i);
			return (1);
		}
		i++;
	}
//	ft_putstr("Final finished loop");
	add = ft_strjoin(*tmp, buf);
	*line = ft_strdup(add); 
//	ft_putstr("\nfinal returns 0\n");
	return (0);
}

int		ft_check_buf(char *buf, char **tmp, char *add, char **line)
{
	int i;
	
	i = 0;
//	ft_putstr("\nin check buf\n");
	while (i <= BUFF_SIZE)
	{
		if (buf[i] == '\n')
		{
	//		ft_putstr("\n");
//			ft_putstr("This is BUF");
	//		ft_putstr(buf);
			add = ft_strsub(buf, 0, i);
	//		ft_putstr(add);
	//		ft_putstr("4444");
			if (*tmp != NULL)
				add = ft_strjoin(*tmp, add);
			*line = ft_strdup(add);
			*tmp = ft_strsub(buf, i + 1, BUFF_SIZE - i);/////////
	//		ft_putstr("2222");
//			ft_putstr(*tmp);
			return (1);
		}
		i++;
	}
	if (*tmp != NULL)
		*tmp = ft_strjoin(*tmp, buf);
	else
		*tmp = ft_strdup(buf);
	//	ft_putstr("\nYYYYYYYYYY");
//	ft_putstr("\nThis is check_buf's saved tmp");
//	ft_putstr(*tmp);
	return (0);
}


int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*tmp;
	char		*add;
    static int	final;

	add = NULL;
	ft_putstr("\nThis is the saved tmp :");
//	ft_putstr(tmp);
	if (final == 1)
	{
		ft_putstr("\nIN FINAL\n");
		return (ft_check_tmp(&tmp, line, add, 0, 0));
	}

	if (tmp != NULL)
	{
		ft_putstr("\nTMP IS NOT NULL\n");
		if (ft_check_tmp(&tmp, line, add, 0, 0 == 1))
			return (1);
	}
//	ft_putstr("\npart 1\n");
	ret  = read(fd, buf, BUFF_SIZE);
	//ft_putstr("\nThis is BUFFFF :");
	//ft_putstr(buf);
	//ft_putstr(" ret : ");
	//ft_putnbr(ret);
	if (ret != BUFF_SIZE)
		return(ft_final(buf, &tmp, add, line, final)); //maybe make this loop within itself until it reaches the end?
//	ft_putstr("\nnot final\n");
	//at this point, we have checked for \n in tmp, we aren't at the end of the file, tmp may not be empty. 
	while (ft_check_buf(buf, &tmp, add, line) != 1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret != BUFF_SIZE)
			return (ft_final(buf, &tmp, add, line, final));
//		ft_putstr("\ngets past ft_final\n");
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int			fd;
	char		*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
//		ft_putstr("\nthis is in the main's loop\n");
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	ft_putstr(line);
	if (argc == 2)
		close (fd);
}
