/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:26:16 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:26:18 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	actsize;
	size_t	length;

	length = ft_strlen(src);
	if (dstsize == 0)
		return (length);
	actsize = dstsize - 1;
	while (actsize && *src)
	{
		*dst = *src;
		dst++;
		src++;
		actsize--;
	}
	*dst = '\0';
	return (length);
}
