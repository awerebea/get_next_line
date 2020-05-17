/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:58:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/17 13:58:43 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*result_ptr;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result_ptr = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (result_ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	start;

	start = (size_t)s;
	while (*s)
		s++;
	return ((size_t)s - start);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*dest_ptr;

	if (!(dest = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	dest_ptr = dest;
	while (*s)
		*dest++ = (char)*s++;
	*dest = '\0';
	return (dest_ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

t_list	*f_gnl_new(int fd)
{
	t_list		*gnl;

	if (!(gnl = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	gnl->fd = fd;
	gnl->next = NULL;
	return (gnl);
}

t_list		*f_search_gnl(int fd, t_list **gnl_list)
{
	t_list			*gnl_tmp;

	if (!*gnl_list)
	{
		*gnl_list = f_gnl_new(fd);
		return (*gnl_list);
	}
	gnl_tmp = *gnl_list;
	while (gnl_tmp->fd != fd && gnl_tmp->next)
		gnl_tmp = gnl_tmp->next;
	if (gnl_tmp->fd == fd)
		return (gnl_tmp);
	else
		gnl_tmp->next = f_gnl_new(fd);
	return (gnl_tmp->next);
}

int			f_read_line(int fd, t_list *gnl_work, char **line)
{
	const long long	buf_size = BUFFER_SIZE;
	long long		read_result;
	char			*buf_str;
	char			*eol_ptr;

	if (!(buf_str = (char*)(malloc(sizeof(char) * buf_size + 1))))
		return (-1);
	eol_ptr = NULL;
	while (!eol_ptr)
	{
		if ((read_result = read(fd, buf_str, buf_size)) < 0)
			return (-1);
		if (read_result == 0)
			return (0);
		buf_str[read_result] = '\0';
		if((eol_ptr = ft_strchr(buf_str, '\n')) != NULL)
		{
			*eol_ptr = '\0';
			gnl_work->rest_of_line = ft_strdup(++eol_ptr);
		}
		if (read_result > 0)
			*line = ft_strjoin(*line, buf_str);
	}
	free(buf_str);
	return (1);
}

int			f_check_rest_of_line(int fd, t_list *gnl_work, char **line)
{
	char			*eol_ptr;

	eol_ptr = NULL;
	if (!(*line = (char*)malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	if (gnl_work->rest_of_line)
	{
		if ((eol_ptr = ft_strchr(gnl_work->rest_of_line, '\n')) != NULL)
		{
			gnl_work->rest_of_line_start = gnl_work->rest_of_line;
			*eol_ptr = '\0';
			++eol_ptr;
			if (*eol_ptr)
				gnl_work->rest_of_line = eol_ptr;
			else
				gnl_work->rest_of_line = NULL;
			*line = ft_strdup(gnl_work->rest_of_line_start);
			return (1);
		}
		else
			*line = ft_strdup(gnl_work->rest_of_line);
	}
	return (f_read_line(fd, gnl_work, line));
}

int			get_next_line(int fd, char **line)
{
	static t_list	*gnl_list;
	t_list			*gnl_work;
	const long long	buf_size = BUFFER_SIZE;
	char			read_chk[1];

	if (fd < 0 || !line || buf_size < 1 || ((read(fd, read_chk, 0) < 0)))
		return (-1);
	gnl_work = f_search_gnl(fd, &gnl_list);
	return (f_check_rest_of_line(fd, gnl_work, line));
}
