/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:03:35 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/23 13:19:27 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(unsigned int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	print_unsigned(unsigned int n)
{
	unsigned int	i;
	unsigned long	power;

	i = ft_nbrlen(n);
	power = 1;
	while (power * 10 <= n)
		power *= 10;
	while (power)
	{
		print_putchar(n / power + '0');
		n = n % power;
		power /= 10;
	}
	return (i);
}
