#include "get_next_line.h"
#include <stdio.h>

int		ft_check_tmp(char *tmp, char **line, int mark, int x)
{
	ft_putstr("\nin check_tmp\n");
	x = ft_strlen(tmp);
	while (mark <= x)
	{
		if (tmp[mark] == '\n')
		{
			add = ft_strsub(tmp, 0, mark); //this might have to be mark - 1, v might have to be + 1
			*line = ft_strdup(add);
			tmp = ft_strsub(tmp, mark + 2, x - mark);
			return (1);
		}
		mark++;
	}
	//we're going to leave tmp alone. Since we strdup when we do *line
	mark = 0;
	return (mark);
}
//ft_final will not always return 0, remember that tmp is not always empty, and buf can have several '\n's, so put them in tmp, and return 1. 
int		ft_final(char *buf, char *tmp, char *add, char **line)
{
	int i;
	int x;

	i = 0;
	x = ft_strlen(buf);
	while (i <= x)
	{
		if (buf[i] == '\n')
		{
			add = ft_strsub(buf, 0, i);
			if (tmp[0] != '\0')
				add = ft_strjoin(add, tmp);
			*line = ft_strdup(add);
			tmp = ft_strsub(tmp, i + 2, x - i);
			return (1);
		}
	}
	add = ft_strjoin(buf, tmp);
	*line = ft_strdup(add);
	return (0);
}

int		ft_check_buf(char *buf, char *tmp, char *add, char **line)
{
	int i;
	
	i = 0;
	while (i <= BUFF_SIZE)
	{
		if (buf[i] == '\n')
		{
			add = ft_strsub(buf, 0, i);
			if (tmp[0] != '\0')
				add = ft_strjoin(add, tmp);
			*line = ft_strdup(add);
			tmp = ft_strsub(tmp, i + 2, BUFF_SIZE - i);
			return (1);
		}
		i++;
	}
	tmp = ft_strjoin(tmp, buf);
	return (i);
}


int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*tmp;
	char		*add;

	add = NULL;
	mark = 0;
	ft_putstr("\nThis is the saved tmp :");
	ft_putstr(tmp);
	if (tmp != NULL)
	{
		if (ft_check_tmp(tmp, line, 0, 0) = 1)
			return (1);
	}
	ft_putstr("\npart 1\n");
	ret  = read(fd, buf, BUFF_SIZE);
	ft_putstr(" ret : ");
	ft_putnbr(ret);
	if (ret != BUFF_SIZE)
		return(ft_final(buf, tmp, add, line)); //maybe make this loop within itself until it reaches the end?
	ft_putstr("\nnot final\n");
	//at this point, we have checked for \n in tmp, we aren't at the end of the file, tmp may not be empty. 
	while (ft_check_buf(buf, tmp, add, line) != 1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret != BUFF_SIZE)
			return (ft_final(buf, tmp, add, line));
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int			fd;
	char		*line;
	int			x;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putstr("\nthis is in the main's loop\n");
		ft_putstr(line);
		free(line);
	}
	ft_putstr(line);
	if (argc == 2)
		close (fd);
}
