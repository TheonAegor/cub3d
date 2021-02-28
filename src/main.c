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

//создаем односвязный список и вставляем в него каждую строку карты
//передаем список в функцию make_map
int		read_map(int fd, t_all *all)
{
	char *line;
	t_list *head = NULL;

	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));	
//		printf("%s\n", head);
	}	
	ft_lstadd_back(&head, ft_lstnew(line));	
	make_map(&head, ft_lstsize(head), all);
//	printf ("here\n");
}

//в двемерный массив вставляем строки
//а потом в двумерный массив структуры вставляем строки
int		make_map(t_list **head, size_t size, t_all *all)
{
	char **map;
	int i;
	t_list *tmp;

	i = 0;
//	printf ("here\n");
	tmp = *head;
	all->map = ft_calloc(sizeof(char*), size + 1);
	while(tmp)
	{
//		printf("%s\n", tmp);
		all->map[i++] = tmp->content;
		tmp = tmp->next;
	}
	all->map[i] = NULL;
/*
	i = 0;
	while (map[i])
	{
		all->map[i] = map[i]; 
		//printf("map[i]= %s\n", all->map[i]);
		i++;
	}
*/
	return (1);
}

int main(int argc, char *argv[])
{
	int fd;
	t_all all;

	all.map = ft_calloc(sizeof(char *), 100);
	fd = open(argv[1], O_RDONLY);
	read_map(fd, &all); 
	show_map(&all);
//	printf ("here\n");
	return (1);
}
