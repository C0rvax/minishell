/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:16:07 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/23 18:13:56 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ifforest(char c, va_list arg);
int		print_putchar(char c);
int		print_putstr(char *s);
int		print_number(int n);
int		print_unsigned(unsigned int n);
int		print_hex(unsigned int nbr, int mode);
int		print_pointer(size_t ptr);

#endif
