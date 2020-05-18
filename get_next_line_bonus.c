/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:58:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/18 17:48:57 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	f_exit(char *buf, int fd, t_list **g_head, int exit_code)
{
	t_list		*g_tmp;
	t_list		*g_tmp_2;

	free(buf);
	g_tmp = *g_head;
	if (g_tmp->fd == fd)
		*g_head = g_tmp->next;
	else
	{
		while (g_tmp->next->fd != fd)
			g_tmp = g_tmp->next;
		g_tmp_2 = g_tmp->next;
		g_tmp->next = g_tmp->next->next;
		free(g_tmp_2->line_bckp);
		free(g_tmp_2->rmndr);
		free(g_tmp_2->rmndr_start);
		free(g_tmp_2);
	}
	(void)buf;
	(void)fd;
	(void)*g_head;
	return (exit_code == 0 ? 0 : -1);
}

static int	f_chk_buf(char *buf, t_list *g_curr, t_list **g_head)
{
	char			*eol_ptr;

	eol_ptr = NULL;
	if ((eol_ptr = ft_strchr(buf, '\n')) != NULL)
	{
		*eol_ptr++ = '\0';
		if (!(g_curr->rmndr = ft_strdup(eol_ptr)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
	}
	return (eol_ptr ? 1 : 0);
}

static int	f_read_line(char *buf, t_list *g_curr, t_list **g_head, char **line)
{
	long long		result;

	if (!(buf = (char*)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (f_exit(buf, g_curr->fd, g_head, -1));
	result = 0;
	while (!result)
	{
		if ((result = read(g_curr->fd, buf, BUFFER_SIZE)) < 0)
			return (f_exit(buf, g_curr->fd, g_head, -1));
		if (result == 0)
			return (f_exit(buf, g_curr->fd, g_head, 0));
		buf[result] = '\0';
		result = f_chk_buf(buf, g_curr, g_head);
		g_curr->line_bckp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		free(g_curr->line_bckp);
		g_curr->line_bckp = NULL;
	}
	free(buf);
	return (1);
}

static int	f_chk_rmndr(char *buf, t_list *g_curr, t_list **g_head, char **line)
{
	char			*eol_ptr;

	eol_ptr = NULL;
	(void)buf;
	if (!(*line = ft_strdup("")))
		return (f_exit(buf, g_curr->fd, g_head, -1));
	if (*(g_curr)->rmndr)
	{
		g_curr->rmndr_start = g_curr->rmndr;
		if ((eol_ptr = ft_strchr(g_curr->rmndr, '\n')) != NULL)
		{
			*eol_ptr++ = '\0';
			g_curr->rmndr = eol_ptr;
		}
		g_curr->line_bckp = *line;
		if (!(*line = ft_strdup(g_curr->rmndr_start)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		free(g_curr->line_bckp);
		if (eol_ptr)
			return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*g_head;
	t_list			*g_curr;
	const long long	buf_size = BUFFER_SIZE;
	char			*buf;
	char			read_chk[1];

	buf = NULL;
	if (BUFFER_SIZE < 1)
		return (-1);
	if (fd < 0 || !line || buf_size < 1 || ((read(fd, read_chk, 0) < 0)))
		return (-1);
	if (!(g_curr = f_search_gnl(fd, &g_head)))
		return (-1);
	if (f_chk_rmndr(buf, g_curr, &g_head, line))
		return (1);
	return (f_read_line(buf, g_curr, &g_head, line));
}
