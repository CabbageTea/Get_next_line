#include <unistd.h>
#include "get_next_line.h"
#define BUF_SIZE 1000;

int		get_next_line(const int fd, char **line)
{
	char buf[BUF_SIZE + 1];
	int mark;
	int ret;
	static char *tmp;
	char *add;

	mark = 0;
	while ((tmp[mark] != '\0') && (tmp[mark] != '\n'))
		mark++;
	if (tmp[mark] == '\n')
	{
		add = ft_strsub(tmp, 0, mark - 1); //this needs to be function. 
		ft_strjoin(*line, add);
		tmp = ft_strsub(tmp, mark + 1, BUF_SIZE - mark);
		return (1);
	}
	ret = read(fd, buf, BUF_SIZE);
	if (ret != BUF_SIZE)
		ft_final;
	mark = 0;
	ft_strjoin(*line, tmp);
	while (mark <= BUF_SIZE)
	{
		if (buf[mark] == '\n')
		{
			add = ft_strsub(buf, 0, mark - 1); //keep the -1. if mark is one we don't want it in line anyway
			ft_strjoin(*line, add);
			tmp = st_strsub(buf, mark + 1, BUF_SIZE - mark);
			return (1);
		}
		tmp[mark] = buf[mark];
		mark++;
	}
	get_next_line(fd, **line);
	return (-1);
}





			
	






