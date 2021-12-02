/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:26:30 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:15:54 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*newstr;
	char		*new;

	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	new = newstr;
	while (s1 && *s1)
	{
		*newstr = *s1;
		newstr++;
		s1++;
	}
	while (s2 && *s2)
	{
		*newstr = *s2;
		newstr++;
		s2++;
	}
	*newstr = '\0';
	return (new);
}
