#include "cub3d.h"

static char *my_itoa(unsigned long nbr, int base)
{
	int len;
	char *p;
	unsigned long tmp;	

	tmp = nbr;
	len = 0;
	if (nbr == 0)
		len++;
	while (tmp)
	{
		len++;
		tmp /= base;
	}
	p = ft_calloc(sizeof(char), (len + 1));
	while (len > 0)
	{
		p[len - 1] = nbr % base;
		if (nbr % base > 9)
			p[len - 1] += 'a' - 10;
		else
			p[len - 1] += '0';
		len--;
		nbr /= base;
	}
	return (p);
}

static int my_strjoin(char **str1, char **str2)
{
	int i;
	int j;
	char *p;

	p = ft_calloc(sizeof(char), (ft_strlen(*str1) + ft_strlen(*str2) + 1));
	i = 0;
	if (*str1 != 0)
		while (str1[0][i])
		{
			p[i] = str1[0][i];
			i++;
		}
	j = 0;
	if (*str2 != 0)
		while (str2[0][j])
		{
			p[j + i] = str2[0][j];
			j++;
		}
	p[j+i] = '\0';
	if (*str1 != 0)
		free (*str1);
	if (*str2 != 0)
		free(*str2);
	*str1 = p;
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
	printf("res%lu\n", res);
/*	
	printf("b=%s\n",tmp = my_itoa(ft_atoi(&rgb[i]), 16));
	tmp = my_itoa(ft_atoi(&rgb[i]), 16);
	my_strjoin(&res, &tmp);
//	printf("reeees=%s\n", res);
	*/
	return (res);
}
