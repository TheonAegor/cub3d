#include "cub3d.h"

int	check_two_str(char *str1, char *str2)
{
	int i;

	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return(-1);
		i++;
	}
	return (1);
}
