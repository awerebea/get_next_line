/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:42:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/17 23:11:12 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/*
** fd - file descriptor
** rmndr - remainder of readed line from last iteration of GNL function
** rmndr_strt - pointer to start of 'rmndr' string
** line_bckp - back up of pointer of 'line' string for cleaning memory
*/

typedef struct	s_list
{
	int				fd;
	char			*rest_of_line;
	char			*rest_of_line_start;
	char			*rest_of_line_bckp;
	struct s_list	*next;
}				t_list;

t_list			*f_search_gnl(int fd, t_list **gnl_list);
t_list			*f_gnl_new(int fd);
int				get_next_line(int fd, char **line);
int				f_read_line(int fd, t_list *gnl_work, t_list **gnl_list, \
				char **line);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
int				f_chk_the_rest(int fd, t_list *gnl_work, t_list **gnl_list, \
				char **line);

#endif
