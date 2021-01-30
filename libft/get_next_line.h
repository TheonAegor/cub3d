/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:37:32 by taegor            #+#    #+#             */
/*   Updated: 2021/01/30 16:40:16 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

size_t				ftstrlcpy(char *dst, const char *src, size_t size);
int					get_next_line(int fd, char **line);
char				*ftstrdup(const char *s);
char				*ftstrjoin(char *s1, char *s2);
int					ftstrlen(char *s);
char				*ftsubstr(char *s, unsigned int start, size_t len);
void				*ftcalloc(size_t nmemb, size_t size);
char				*ftstrchr(char *s, int c);

#endif
