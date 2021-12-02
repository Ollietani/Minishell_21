/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:26:04 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:15:27 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	length;
	size_t	a;
	char	*new;

	a = 0;
	if (!s)
		return (NULL);
	length = ft_strlen(s);
	new = malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	while (length)
	{
		new[a] = f(a, s[a]);
		a++;
		length--;
	}
	new[a] = '\0';
	return (new);
}
