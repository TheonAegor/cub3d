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

int		read_map(int fd, t_all *all)
{
	char *line;
	t_list *head = NULL;

	while (get_next_line(fd, &line))
	{
//		printf ("here\n");
		ft_lstadd_back(&head, ft_lstnew(line));	
	}	
	ft_lstadd_back(&head, ft_lstnew(line));	
	make_map(&head, ft_lstsize(head), all);
}

int		make_map(t_list **head, size_t size, t_all *all)
{
	char **map;
	int i;
	t_list *tmp;

	i = 0;
//	printf ("here\n");
	tmp = *head;
	map = ft_calloc(sizeof(char*), size + 1);
	while(tmp)
	{
		map[i++] = tmp->content;
		tmp = tmp->next;
	}
	i = 0;
//	printf("here\n");
	while (map[i++])
		all->map[i] = map[i]; 
	return (1);
}

int main(int argc, char *argv[])
{
	int fd;
	t_all all;

	fd = open(argv[1], O_RDONLY);
	read_map(fd, &all); 
//	printf ("here\n");
	show_map(&all);
	return (1);
}