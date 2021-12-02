/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:25:32 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:25:34 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	int			a;
	size_t		length;

	a = 0;
	length = ft_strlen(s);
	if (start > length)
		len = 0;
	if ((length - start) < len)
		len = length - start;
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (len)
	{
		substr[a] = s[start];
		start++;
		a++;
		len--;
	}
	substr[a] = '\0';
	return (substr);
}
