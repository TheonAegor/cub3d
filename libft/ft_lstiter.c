/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:43:54 by taegor            #+#    #+#             */
/*   Updated: 2020/11/20 13:44:31 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	if (!f)
		return ;
	if (lst)
	{
		tmp = lst;
		while (tmp != NULL)
		{
			(*f)(tmp->content);
			tmp = tmp->next;
		}
	}
}
