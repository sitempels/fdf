/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:57:19 by stempels          #+#    #+#             */
/*   Updated: 2025/04/08 22:18:07 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_point **lst, void (*del)(int))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		temp = current;
		current = current -> next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
