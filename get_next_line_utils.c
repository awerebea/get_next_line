/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:59:14 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/17 22:30:19 by awerebea         ###   ########.fr       */
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
	gnl->rest_of_line = NULL;
	gnl->rest_of_line_start = NULL;
	gnl->next = NULL;
	return (gnl);
}
