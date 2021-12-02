/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:25:59 by myael             #+#    #+#             */
/*   Updated: 2021/11/25 17:30:35 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				a;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 || !str2)
		return (0);
	if (n == 0)
		return (0);
	while (n && (*str1 == *str2) && (*str1 != '\0' || *str2 != '\0'))
	{
		str1++;
		str2++;
		n--;
	}
	if (n > 0)
		a = *str1 - *str2;
	else
		a = *(str1 - 1) - *(str2 - 1);
	return (a);
}
