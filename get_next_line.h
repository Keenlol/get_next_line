/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:13:04 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/14 15:44:18 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	read_and_stash(int fd, t_list **stash);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
void	free_stash(t_list *stash);

int		ft_strlen(const char *str);
t_list	*ft_lst_get_last(t_list *stash);
int		found_newline(t_list *stash);
void	add_to_stash(t_list **stash, char *buff, int readed);
void	generate_line(char **line, t_list *stash);

#endif
