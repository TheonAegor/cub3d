/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:47:52 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 17:26:03 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;
	t_list	*tmp;

	if (*lst && del && lst)
	{
		last = *lst;
		while (last)
		{
			tmp = last->next;
			ft_lstdelone(last, del);
			last = tmp;
		}
		*lst = NULL;
	}
}
