/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chetphisuthgmail.com <chetphisuthgmail.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:28:26 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/21 21:03:11 by chetphisuth      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl[fd].head)
		start_gnl(&gnl[fd], fd);
	gnl[fd].len = 0;
	if (!read_next_line(&gnl[fd]))
		return (NULL);
	if (gnl[fd].last->len == -1 || !gnl[fd].len)
	{
		free_all(&gnl[fd]);
		return (NULL);
	}
	line = extract_line(&gnl[fd]);
	return (line);
}
