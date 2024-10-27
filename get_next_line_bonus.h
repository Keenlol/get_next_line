/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctongpa <ctongpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:28:17 by ctongpa           #+#    #+#             */
/*   Updated: 2024/10/27 14:11:24 by ctongpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_link
{
	char			content[BUFFER_SIZE + 1];
	ssize_t			len;
	struct s_link	*next;
}	t_link;

typedef struct s_gnl
{
	struct s_link	*head;
	struct s_link	*last;
	int				fd;
	int				eof;
	ssize_t			len;
	size_t			offset;
}	t_gnl;

char	*get_next_line(int fd);
void	start_gnl(t_gnl *gnl, int fd);
int		read_next_line(t_gnl *gnl);
int		read_file(t_gnl *gnl);
char	*extract_line(t_gnl *gnl);
int		free_all(t_gnl *gnl);

#endif
