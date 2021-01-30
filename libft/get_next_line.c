/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:34:50 by taegor            #+#    #+#             */
/*   Updated: 2021/01/30 16:44:43 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

static int	fill_reminder(char **p_n, char **line, char **reminder)
{
	char		*tmp;

	if (!(*line = ftcalloc(sizeof(char), (1))))
		return (-1);
	if (*reminder)
	{
		if ((*p_n = ftstrchr(*reminder, '\n')))
		{
			*p_n[0] = '\0';
			tmp = *line;
			*line = ftstrdup(*reminder);
			free(tmp);
			tmp = *reminder;
			*reminder = ftstrdup(++(*p_n));
			free(tmp);
			return (1);
		}
		tmp = *line;
		*line = ftstrdup(*reminder);
		free(tmp);
	}
	*p_n = NULL;
	return (0);
}

static int	do_gnl(char **p_n, int fd, char **line, char **reminder)
{
	char		*buf;
	int			bytes_was_read;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || !(buf = ftcalloc(sizeof(char), BUFFER_SIZE + 1)))
		return (-1);
	while (!(*p_n) && (bytes_was_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_was_read] = '\0';
		if ((*p_n = ftstrchr(buf, '\n')))
		{
			**p_n = '\0';
			if (*reminder)
			{
				tmp = *reminder;
				*reminder = ftstrdup(++(*p_n));
				free(tmp);
			}
			else
				*reminder = ftstrdup(++(*p_n));
		}
		*line = ftstrjoin(*line, buf);
	}
	free_and_null(&buf);
	return (bytes_was_read);
}

int			get_next_line(int fd, char **line)
{
	char		*p_n;
	static char	*reminder;
	int			res;
	int			is_ok;

	if ((res = fill_reminder(&p_n, line, &reminder)) == -1)
	{
		free_and_null(&reminder);
		return (-1);
	}
	else if (res == 1)
		return (1);
	if ((is_ok = do_gnl(&p_n, fd, line, &reminder)) == 0)
	{
		free_and_null(&reminder);
		return (0);
	}
	if (is_ok == -1)
	{
		free_and_null(&reminder);
		return (-1);
	}
	return (1);
}
