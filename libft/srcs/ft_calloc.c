/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:29:26 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:15:42 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	void	*temp;

	pointer = malloc((count) * size);
	if (!pointer)
		return (NULL);
	temp = pointer;
	ft_memset(pointer, 0, (size * count));
	return (temp);
}
