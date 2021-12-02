/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:27:26 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:27:28 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (src > dst)
	{
		while (len)
		{	
			*dest = *source;
			dest++;
			source++;
			len--;
		}
	}
	if (src < dst)
	{
		while (len)
		{
			*(dest + len - 1) = *(source + len - 1);
			len--;
		}
	}
	return (dst);
}
