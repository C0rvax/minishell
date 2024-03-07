/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifforest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:30:44 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/30 15:51:36 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ifforest(char c, va_list arg)
{
	int	i;

	i = 0;
	if (c == 'c')
		i = print_putchar(va_arg(arg, int));
	else if (c == 's')
		i = print_putstr(va_arg(arg, char *));
	else if (c == 'p')
		i = print_pointer(va_arg(arg, size_t));
	else if (c == 'd' || c == 'i')
		i = print_number(va_arg(arg, int));
	else if (c == 'u')
		i = print_unsigned(va_arg(arg, unsigned int));
	else if (c == 'x')
		i = print_hex(va_arg(arg, unsigned int), 0);
	else if (c == 'X')
		i = print_hex(va_arg(arg, unsigned int), 1);
	else if (c == '%')
		i = print_putchar('%');
	else
	{
		i += print_putchar('%');
		i += print_putchar(c);
	}
	return (i);
}
