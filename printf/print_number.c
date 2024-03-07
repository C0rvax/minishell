/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:52:12 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/23 13:18:30 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	print_number(int n)
{
	int		res;
	long	power;
	long	nbr;

	nbr = n;
	res = ft_nbrlen(n);
	if (nbr < 0)
	{
		print_putchar('-');
		nbr *= -1;
	}
	power = 1;
	while (power * 10 <= nbr)
		power *= 10;
	while (power)
	{
		print_putchar(nbr / power + '0');
		nbr = nbr % power;
		power /= 10;
	}
	return (res);
}
