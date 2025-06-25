/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:53:12 by vtian             #+#    #+#             */
/*   Updated: 2025/05/30 17:14:15 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;

	if (!f || !del)
		return (NULL);
	map = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new);
		lst = lst->next;
	}
	return (map);
}
