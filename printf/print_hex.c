/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:50:54 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/23 13:18:00 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned int nbr, int mode)
{
	char			*basel;
	char			*baseu;
	unsigned long	power;
	int				count;

	basel = "0123456789abcdef";
	baseu = "0123456789ABCDEF";
	count = 0;
	power = 1;
	while (power * 16 <= nbr)
		power *= 16;
	while (power)
	{
		if (mode == 1)
			count += print_putchar(baseu[nbr / power]);
		else
			count += print_putchar(basel[nbr / power]);
		nbr = nbr % power;
		power /= 16;
	}
	return (count);
}
