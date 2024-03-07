/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:42 by aduvilla          #+#    #+#             */
/*   Updated: 2023/12/04 15:50:10 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	arg;

	if (!s)
		return (-1);
	va_start(arg, s);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == '\0')
			return (va_end(arg), -1);
		else if (s[i] == '%')
		{
			i++;
			count = count + ifforest(s[i], arg);
		}
		else
			count = count + print_putchar(s[i]);
		i++;
	}
	va_end(arg);
	return (count);
}
