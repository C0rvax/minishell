/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:48:33 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/27 14:38:56 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hexp(size_t n, int count)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		count += print_hexp(n / 16, count);
	count += print_putchar(base[n % 16]);
	return (count);
}

int	print_pointer(size_t ptr)
{
	int	i;

	if (!ptr)
		return (print_putstr("(nil)"));
	i = print_putstr("0x");
	i += print_hexp(ptr, 0);
	return (i);
}
