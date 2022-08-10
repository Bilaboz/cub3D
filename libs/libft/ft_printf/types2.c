/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:26:46 by rcarles           #+#    #+#             */
/*   Updated: 2021/12/13 16:01:07 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/* Because of 25 lines per function limit */
static void	handle_str2(t_flags *flags, char *copy, size_t len)
{
	if (flags->minus && flags->number)
	{
		write_buf(copy, len);
		print_char(' ', flags->number - len);
	}
	else if (flags->number)
	{
		print_char(' ', flags->number - len);
		write_buf(copy, len);
	}
	else
		write_buf(copy, len);
}

void	handle_str(const char *s, t_flags *flags)
{
	size_t	len;
	char	*copy;
	int		is_null;

	is_null = 0;
	if (!s)
	{
		is_null = 1;
		copy = ft_strdup("(null)");
	}
	else
		copy = ft_strdup(s);
	if (!copy)
		return ;
	if (flags->dot)
	{
		if (flags->dot_nb <= (int) ft_strlen(copy) && !is_null)
			copy[flags->dot_nb] = '\0';
		else if (!flags->dot_nb
			|| (is_null && flags->dot_nb < (int) ft_strlen(copy)))
			copy[0] = '\0';
	}
	len = ft_strlen(copy);
	handle_str2(flags, copy, len);
	free(copy);
}

/* Because of 25 lines per function limit */
static void	handle_int2(t_flags *flags, int digits, int prefix, int nb)
{
	if (flags->zero && !flags->dot)
		print_char('0', flags->number - digits - prefix);
	ft_putnbr_buff(nb);
}

void	handle_int(int nb, t_flags *flags)
{
	int		prefix;
	int		digits;

	prefix = 0;
	digits = count_digits(nb, flags);
	if ((nb >= 0 && (flags->plus || flags->space)))
		prefix++;
	if ((!flags->zero && !flags->minus && flags->number)
		|| (flags->zero && flags->dot))
		print_char(' ', flags->number - digits - prefix);
	nb = process_prefix(flags, nb);
	if (flags->dot && flags->dot_nb)
	{
		print_char('0', flags->dot_nb - digits);
		digits += flags->dot_nb - digits + 1;
	}
	if (flags->minus && flags->number)
	{
		ft_putnbr_buff(nb);
		print_char(' ', flags->number - digits - prefix);
	}
	else
		handle_int2(flags, digits, prefix, nb);
}
