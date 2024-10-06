/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:13:00 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/06 17:08:19 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

////////////////////////

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);

}

int	found_newline(t_list *stash)
{
	size_t	i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	i = 0;
	current = ft_lst_get_last(stash);
	while (current -> content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	add_to_stash(t_list **stash, char *buff, int read_cursor)
{
	size_t	i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (read_cursor + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < read_cursor)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	generate_line(char **line, t_list *stash)
{
	size_t 	i;
	size_t	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return ;
}

/////////////////////

void	extract_line(t_list *stash, char **line)
{
	size_t	i;
	size_t	j;

	if (!stash)
		return ;
	generate_line(line, stash);
	if (!*line)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	read_and_stash(int fd, t_list **stash, int *read_cursor)
{
	char	*buff;

	while (!found_newline(*stash) && *read_cursor != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);		
		*read_cursor = read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && *read_cursor == 0) || *read_cursor == -1)
		{
			free(buff);
			return ;
		}
		buff[*read_cursor] = '\0';
		add_to_stash(stash, buff, *read_cursor);
		free(buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;
	int				read_cursor;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_cursor = 1;
	line = NULL;

	read_and_stash(fd, &stash, &read_cursor);
	if (stash == NULL)
		return (NULL);
	
	extract_line(stash, &line);
	return (line);
}

///////////////////

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int		fd;
	char	*thing;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		thing = get_next_line(fd);
		if (!thing)
			break;
		printf("here : %s",thing);
		free(thing);
	}
}
