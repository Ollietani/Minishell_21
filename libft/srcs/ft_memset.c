/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:27:19 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:27:21 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	symbol;
	char			*str;

	str = (char *)b;
	symbol = c;
	while (len)
	{
		*str = symbol;
		str++;
		len--;
	}
	return (b);
}
