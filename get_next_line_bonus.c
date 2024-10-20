/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:28:26 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/20 17:50:16 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl.head)
		start_gnl(&gnl, fd);
	gnl.len = 0;
	if (!read_next_line(&gnl))
		return (NULL);
	if (gnl.last->len == -1 || !gnl.len)
	{
		free_all(&gnl);
		return (NULL);
	}
	line = extract_line(&gnl);
	return (line);
}
