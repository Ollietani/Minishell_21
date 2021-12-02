/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:26:35 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:16:24 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	char	*pointer;
	int		a;

	a = 0;
	pointer = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!pointer)
		return (NULL);
	temp = pointer;
	while (*s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	*temp = '\0';
	return (pointer);
}
