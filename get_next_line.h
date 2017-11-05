/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dglaser <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:52:22 by dglaser           #+#    #+#             */
/*   Updated: 2017/11/04 23:06:48 by dglaser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  	GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H

# define	BUFF_SIZE 1000


#include	"libft/libft.h"
# include	<unistd.h>
# include	<stdlib.h>
# include	<fcntl.h>

int		get_next_line(int fd, char **line);

#endif
