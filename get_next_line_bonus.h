/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:42:55 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/18 17:29:43 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

/*
** fd - file descriptor
** rmndr - remainder of readed line from last iteration of GNL function
** rmndr_strt - pointer to start of 'rmndr' string
** line_bckp - back up of pointer of 'line' string for cleaning memory
*/

typedef struct	s_list
{
	int				fd;
	char			*rmndr;
	char			*rmndr_start;
	char			*line_bckp;
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);
t_list			*f_gnl_new(int fd);
t_list			*f_search_gnl(int fd, t_list **g_head);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
