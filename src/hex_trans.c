#include "cub3d.h"

int		check_hex(t_all *all)
{
	if (check_chars(all->floor_c) == -1)
	{
		handle_hex_err2(-1, all);
		return (-1);
	}
	if (check_chars(all->ceil_c) == -1)
	{
		handle_hex_err2(-2, all);
		return (-1);
	}
	if (check_commas(all->floor_c, all) < 0 || check_commas(all->ceil_c, all) < 0)
		return (-1);
	return (1);
}

int		check_commas(char *str, t_all *all)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	if (counter < 2)
	{
		handle_hex_err2(-3, all);
		return (-1);
	}
	if (counter > 2)
	{
		handle_hex_err2(-4, all);
		return (-1);
	}
	return (1);
}

int		check_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_strchr("0123456789, \0\t", str[i])))
			return (-1);
		i++;
	}
	return (1);
}

unsigned to_hex(char *rgb)
{
	int i;
	unsigned long res;

	i = 0;
//	printf("r=%d\n", r);
	res = ft_atoi(&rgb[i])<<16;
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	res += ft_atoi(&rgb[i])<<8;
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	res += ft_atoi(&rgb[i]);
	return (res);
}
