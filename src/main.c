/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 22:40:41 by taegor            #+#    #+#             */
/*   Updated: 2021/03/23 22:44:39 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		make_map(t_list **head, size_t size, t_all *all);

int		read_map(char *argv, t_all *all)
{
	char	*line;
	int		fd;
	t_list	*head;

	head = NULL;
	if ((fd = open(argv, O_RDONLY)) < 0)
	{
		perror("open");
		return (-1);
	}
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (make_map(&head, ft_lstsize(head), all) < 0)
		return (-1);
	close(fd);
	return (1);
}

int		make_map(t_list **head, size_t size, t_all *all)
{
	char		**map;
	int			i;
	t_list		*tmp;
	t_list		*tmp2;

	i = 0;
	tmp = *head;
	all->map = ft_calloc(sizeof(char*), size + 1);
	if (all->map == 0)
	{
		perror("ft_calloc");
		return (-1);
	}
	while (tmp)
	{
		all->map[i++] = tmp->content;
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	all->map[i] = NULL;
	return (1);
}

int		main(int argc, char *argv[])
{
	int		fd;
	t_all	all;

	if (argc < 2 || argc > 3)
	{
		handle_arg_errors(argc);
		return (-1);
	}
	if (argc == 3)
	{
		if (check_two_str(argv[2], "--save") == 1)
			all.save = 1;
		else
		{
			ft_printf("You have a bad second argument,try '--save' to make a screenshot\n");
			return (-1);
		}
	}
	if (read_map(argv[1], &all) < 0 || parse_map(&all) < 0)
		return (-1);
	if (find_only_plr(&all) < 0 || check_bounds2(&all, &all.brd) < 0)
		return (-1);
	if (show_map(&all) < 0)
		return (-1);
	return (1);
}
