/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:28:26 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/27 14:22:26 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl[MAX_FD];
	char			*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
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
