/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yo.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dglaser <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:52:47 by dglaser           #+#    #+#             */
/*   Updated: 2017/11/01 19:53:45 by dglaser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>
int		ft_final(char *buf, char *tmp, char *add, char **line)
{
	ft_putstr("\nin ft_final\n"); //remember that this just means you read less than BUFFSIZE . There could be multiple \n's, 
	add = ft_strjoin(tmp, buf);
	ft_putstr(add);
	*line = ft_strdup(add);
	ft_putstr("\n this one is line :"); //this is where it fucks up - EDIT WORKS NOW
	ft_putstr(*line);
	return (0);
}
//ADD SOME CASES FOR -1 
//MAKE IT ACTUALLY RETURN 1 OR 0 WHEN IT'S DONE 
int		get_next_line(const int fd, char **line)
{
	char buf[BUFF_SIZE + 1];
	int mark;
	int ret;
	static char *tmp;
	char *add;

	add = NULL;
	mark = 0;
	ft_putstr(tmp); //so this worked.

	ft_putstr("\npart1\n");
	if (tmp != NULL)
	{
		while ((tmp[mark] != '\0') && (tmp[mark] != '\n'))
			mark++;
		ft_putstr("\npart2\n");
		ft_putstr(tmp);
		if (tmp[mark] == '\n')
		{
			add = ft_strsub(tmp, 0, mark - 1); //turn this into a function 
			ft_strjoin(*line, add);
			tmp = ft_strsub(tmp, mark + 1, BUFF_SIZE - mark);
			ft_putstr("Okay, this one actually should print");
			return (1);
		}
		else
			ft_strjoin(*line, tmp);
		free(tmp);
	}
	ft_putstr("\npart3\n");
	ret = read(fd, buf, BUFF_SIZE);
	ft_putstr("\nread\n");
	ft_putnbr(ret);

	if (ret != BUFF_SIZE)
		return(ft_final(buf, tmp, add, line));
	ft_putstr("\nnot final\n");
	mark = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(buf)));	
	while (mark <= BUFF_SIZE)
	{
		ft_putstr("\nin the first part\n");
		if (buf[mark] == '\n')
		{
			ft_putstr("\nin the loop\n");
			add = ft_strsub(buf, 0, mark - 1); //keep the -1. if mark is one we don't want it in line anyway
			ft_strjoin(*line, add);
			tmp = ft_strsub(buf, mark + 1, BUFF_SIZE - mark);
			return (1);
		}
		ft_putchar('\n');
		tmp[mark] = buf[mark];
		ft_putstr("...");
		mark++;
	}
	ft_putstr("looping again");
	get_next_line(fd, line);
	return (-1);
}
int		main(int argc, char **argv)
{
	int		fd;
	char 	*line;
	int x;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	x = get_next_line(fd, &line);
	printf("this is what x is %d", x);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putstr("\nyo, is this even working?\n");
		ft_putstr(line);
		free(line);
	}
	ft_putstr(line);
	if (argc == 2)
		close(fd);
}
