/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:28:31 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/27 14:40:35 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	start_gnl(t_gnl *gnl, int fd)
{
	gnl->head = NULL;
	gnl->last = NULL;
	gnl->fd = fd;
	gnl->eof = 0;
	gnl->len = 0;
	gnl->offset = 0;
}

int	read_file(t_gnl *gnl)
{
	if (!gnl->head)
	{
		gnl->head = (t_link *)malloc(sizeof(t_link));
		if (!gnl->head)
			return (0);
		gnl->last = gnl->head;
	}
	else if (!gnl->eof)
	{
		gnl->last->next = (t_link *)malloc(sizeof(t_link));
		if (!gnl->last->next)
			return (free_all(gnl));
		gnl->last = gnl->last->next;
	}
	else
		return (1);
	gnl->last->next = NULL;
	gnl->last->len = read(gnl->fd, gnl->last->content, BUFFER_SIZE);
	if (gnl->last->len <= 0)
		gnl->eof = 1;
	return (1);
}

int	read_next_line(t_gnl *gnl)
{
	t_link	*tmp;
	int		i;

	if (!gnl->head && !read_file(gnl))
		return (0);
	if (gnl->last->len == -1)
		return (1);
	tmp = gnl->head;
	while (1)
	{
		i = (gnl->len + gnl->offset) % BUFFER_SIZE;
		if (i > tmp->len - 1)
			return (1);
		gnl->len++;
		if (tmp->content[i] == '\n')
			return (1);
		if (i == BUFFER_SIZE - 1)
		{
			if (!read_file(gnl))
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

char	*extract_line(t_gnl *gnl)
{
	t_link	*tmp;
	char	*line;
	int		i;

	line = (char *)malloc(sizeof(char) * (gnl->len + 1));
	if (!line)
	{
		free_all(gnl);
		return (NULL);
	}
	i = 0;
	while (i < gnl->len)
	{
		line[i++] = gnl->head->content[gnl->offset++];
		if ((ssize_t)gnl->offset == gnl->head->len)
		{
			tmp = gnl->head;
			gnl->head = gnl->head->next;
			free(tmp);
			gnl->offset = 0;
		}
	}
	line[gnl->len] = '\0';
	return (line);
}

int	free_all(t_gnl *gnl)
{
	t_link	*tmp;

	while (gnl->head)
	{
		tmp = gnl->head->next;
		free(gnl->head);
		gnl->head = tmp;
	}
	start_gnl(gnl, gnl->fd);
	return (0);
}
