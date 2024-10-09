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

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*(str++))
		count++;
	return (count);
}

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
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	add_to_stash(t_list **stash, char *buff, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < readed)
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
	int 	i;
	int		len;

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

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current->next);
		free(current);
		current = next;
	}
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!stash || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (!(clean_node->content))
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

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

void	read_and_stash(int fd, t_list **stash)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buff);
			return ;
		}
		buff[readed] = '\0';
		add_to_stash(stash, buff, readed);
		free(buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;

	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	
	extract_line(stash, &line);

	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

///////////////////

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int		fd;
	char	*thing;

	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		printf("error opening the file\n");
		return (0);
	}
	printf("read sucess!\n");
	while (1)
	{
		thing = get_next_line(fd);
		if (!thing)
			break;
		printf("here : %s",thing);
		free(thing);
	}
}
