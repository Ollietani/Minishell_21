/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:28:52 by myael             #+#    #+#             */
/*   Updated: 2021/12/02 20:16:12 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_amount(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		count++;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		amount;

	amount = ft_amount(n);
	string = malloc(sizeof(char) * (amount + 1));
	if (!string)
		return (NULL);
	*(string + amount) = '\0';
	if (n == 0)
		*string = '0';
	if (n < 0)
		*string = '-';
	amount--;
	while (amount)
	{
		if (n < 0)
			*(string + amount) = -(n % 10) + '0';
		else
			*(string + amount) = (n % 10) + '0';
		n /= 10;
		amount--;
	}
	if (n > 0)
		*string = n + '0';
	return (string);
}
