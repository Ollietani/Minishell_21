/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:28:23 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:28:26 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		(*lst)->content = NULL;
		if ((*lst)->amb_data)
			free((*lst)->amb_data);
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	*lst = NULL;
}
