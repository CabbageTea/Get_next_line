#include "get_next_line.h"

int		ft_check_tmp(char **tmp, char **line, char *add, int mark, int x)
{
	x = ft_strlen(*tmp); 
	while (mark <= x)
	{
		if (tmp[0][mark] == '\n')  
		{
			add = ft_strsub(*tmp, 0, mark);
			*line = ft_strdup(add);
			*tmp = ft_strsub(*tmp, mark + 1, x - mark);
			return (1);
		}
		mark++;
	}
	mark = 0;
	return (mark);
}
int		ft_final(char *buf, char **tmp, char *add, char **line)
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
			if (*tmp != 0)
				add = ft_strjoin(*tmp, add);
			*line = ft_strdup(add);
			*tmp = ft_strsub(buf, i + 1, x - i);
			return (1);
		}
		i++;
	}
	add = ft_strjoin(*tmp, buf);
	*line = ft_strdup(add);
	return (0);
}

int		ft_check_buf(char *buf, char **tmp, char *add, char **line)
{
	int i;
	
	i = 0;
	while (i <= BUFF_SIZE)
	{
		if (buf[i] == '\n')
		{
			add = ft_strsub(buf, 0, i);
			if (*tmp != NULL)
				add = ft_strjoin(*tmp, add);
			*line = ft_strdup(add);
			*tmp = ft_strsub(buf, i + 1, BUFF_SIZE - i);
			return (1);
		}
		i++;
	}
	if (*tmp != NULL)
		*tmp = ft_strjoin(*tmp, buf);
	else
		*tmp = ft_strdup(buf);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*tmp;
	char		*add;

	add = NULL;
	if (tmp != NULL)
	{
		if (ft_check_tmp(&tmp, line, add, 0, 0 == 1))
			return (1);
	}
	ret  = read(fd, buf, BUFF_SIZE);
	if (ret == 0)
		return (0);
	buf[ret] = '\0';
	if (ret != BUFF_SIZE)
		return(ft_final(buf, &tmp, add, line));
	while (ft_check_buf(buf, &tmp, add, line) != 1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret != BUFF_SIZE)
			return (ft_final(buf, &tmp, add, line));
	}
	return (1);
}

/*int		main(int argc, char **argv)
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
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	if (argc == 2)
		close (fd);
} */
