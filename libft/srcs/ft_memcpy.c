/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:27:31 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:27:33 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp;
	char	*source;

	temp = (char *) dst;
	source = (char *) src;
	if (!dst && !src)
		return (NULL);
	while (n)
	{
		*temp = *source;
		source++;
		temp++;
		n--;
	}
	return (dst);
}
