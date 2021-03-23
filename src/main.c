#include "cub3d.h"

int		make_map(t_list **head, size_t size, t_all *all);

void printt(char **strs)
{
	int i = 0;

	while (strs[i])
	{
		ft_putendl_fd(strs[i++], 1);
	}
}

/*
 * создаем односвязный список и вставляем в него каждую строку карты
 * передаем список в функцию make_map
*/
int		read_map(char *argv, t_all *all)
{
	char *line;
	int fd;
	t_list *head = NULL;

	if((fd = open(argv, O_RDONLY)) < 0)
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

/*
 * в двемерный массив вставляем строки
 * а потом в двумерный массив структуры вставляем строки
*/
int		make_map(t_list **head, size_t size, t_all *all)
{
	char **map;
	int i;
	t_list *tmp;
	t_list *tmp2;

	i = 0;
	tmp = *head;
	all->map = ft_calloc(sizeof(char*), size + 1);
	if (all->map == 0)
	{
		perror("ft_calloc");
		return (-1);
	}
	while(tmp)
	{
		all->map[i++] = tmp->content;
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	all->map[i] = NULL;
	return (1);
}

int main(int argc, char *argv[])
{
	int fd;
	t_all all;
//	int i;

	if(read_map(argv[1], &all) < 0)
		return (-1);
	if (parse_map(&all) < 0)
		return (-1);
	if (find_only_plr(&all) < 0)
		return (-1);
//	printf("x%f,y%f\n", all.plr.x, all.plr.y);
	if (check_bounds2(&all, &all.brd) < 0)
		return(-1);
	if(show_map(&all) < 0)
	{
		perror("show_map");
		return (-1);
	}
	/*
	*/

	return (1);
}
