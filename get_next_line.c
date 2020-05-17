/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:58:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/17 23:10:54 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		f_exit(int fd, t_list **gnl_list, int exit_code)
{
	t_list		*gnl_tmp;
	t_list		*gnl_tmp_2;

	gnl_tmp = *gnl_list;
	if (gnl_tmp->fd == fd)
		*gnl_list = gnl_tmp->next;
	else
	{
		while (gnl_tmp->next->fd != fd)
			gnl_tmp = gnl_tmp->next;
		gnl_tmp_2 = gnl_tmp->next;
		gnl_tmp->next = gnl_tmp->next->next;
		free(gnl_tmp_2->rest_of_line_bckp);
		free(gnl_tmp_2->rest_of_line_start);
		free(gnl_tmp_2);
	}
	return (exit_code == 0 ? 0 : -1);
}

t_list	*f_search_gnl(int fd, t_list **gnl_list)
{
	t_list			*gnl_tmp;

	if (!*gnl_list)
	{
		if (!(*gnl_list = f_gnl_new(fd)))
			return (NULL);
		return (*gnl_list);
	}
	gnl_tmp = *gnl_list;
	while (gnl_tmp->fd != fd && gnl_tmp->next)
		gnl_tmp = gnl_tmp->next;
	if (gnl_tmp->fd == fd)
		return (gnl_tmp);
	else
	{
		if (!(gnl_tmp->next = f_gnl_new(fd)))
			return (NULL);
		return (gnl_tmp->next);
	}
}

int		f_read_line(int fd, t_list *gnl_work, t_list **gnl_list, char **line)
{
	const long long	buf_size = BUFFER_SIZE;
	long long		read_result;
	char			*buf_str;
	char			*eol_ptr;

	if (!(buf_str = (char*)(malloc(sizeof(char) * buf_size + 1))))
		return (f_exit(fd, gnl_list, -1));
	eol_ptr = NULL;
	while (!eol_ptr)
	{
		if ((read_result = read(fd, buf_str, buf_size)) < 0)
			return (f_exit(fd, gnl_list, -1));
		if (read_result == 0)
			return (f_exit(fd, gnl_list, 0));
		buf_str[read_result] = '\0';
		if((eol_ptr = ft_strchr(buf_str, '\n')) != NULL)
		{
			*eol_ptr = '\0';
			if (!(gnl_work->rest_of_line = ft_strdup(++eol_ptr)))
				return (f_exit(fd, gnl_list, -1));
		}
		if (!(*line = ft_strjoin(*line, buf_str)))
			return (f_exit(fd, gnl_list, -1));
	}
	free(buf_str);
	return (1);
}

int		f_chk_the_rest(int fd, t_list *gnl_work, t_list **gnl_list, char **line)
{
	char			*eol_ptr;

	eol_ptr = NULL;
	if (!(*line = (char*)malloc(sizeof(char) * 1)))
		return (f_exit(fd, gnl_list, -1));
	**line = '\0';
	if (gnl_work->rest_of_line)
	{
		if (gnl_work->rest_of_line_bckp == NULL)
			gnl_work->rest_of_line_bckp = gnl_work->rest_of_line;
		gnl_work->rest_of_line_start = gnl_work->rest_of_line;
		if ((eol_ptr = ft_strchr(gnl_work->rest_of_line, '\n')) != NULL)
		{
			*eol_ptr++ = '\0';
			gnl_work->rest_of_line = eol_ptr;
			if (!(*line = ft_strdup(gnl_work->rest_of_line_start)))
				return (f_exit(fd, gnl_list, -1));
			return (1);
		}
		if(!(*line = ft_strdup(gnl_work->rest_of_line_start)))
			return (f_exit(fd, gnl_list, -1));
		/* free(gnl_work->rest_of_line_bckp); */
		/* gnl_work->rest_of_line = NULL;      */
		/* gnl_work->rest_of_line_bckp = NULL; */
	}
	return (f_read_line(fd, gnl_work, gnl_list, line));
}

int		get_next_line(int fd, char **line)
{
	static t_list	*gnl_list;
	t_list			*gnl_work;
	const long long	buf_size = BUFFER_SIZE;
	char			read_chk[1];

	if (fd < 0 || !line || buf_size < 1 || ((read(fd, read_chk, 0) < 0)))
		return (-1);
	if(!(gnl_work = f_search_gnl(fd, &gnl_list)))
		return (-1);
	return (f_chk_the_rest(fd, gnl_work, &gnl_list, line));
}
