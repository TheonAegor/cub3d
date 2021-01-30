#include "cub3d.h"

void printt(char **strs)
{
	int i = 0;

	while (strs[i])
	{
		ft_putendl_fd(strs[i++], 1);
	}
}

char	**make_map(t_list **head, size_t size)
{
	char **map;
	int i;
	t_list *tmp;

	i = 0;
	tmp = *head;
	map = ft_calloc(sizeof(char*), size + 1);
//	printf ("here\n");
	while(tmp)
	{
		map[i++] = tmp->content;
		tmp = tmp->next;
	}
	return (map);
}

int main(int argc, char *argv[])
{
	int fd;
	char *line;
	t_list *head;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
//		printf("line:%s\n", line);
		ft_lstadd_back(&head, ft_lstnew(line));	
	}
	ft_lstadd_back(&head, ft_lstnew(line));	
	show_map(make_map(&head, ft_lstsize(head)));
	return (1);
}
