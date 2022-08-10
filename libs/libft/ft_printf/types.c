/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:52:30 by rcarles           #+#    #+#             */
/*   Updated: 2021/12/13 16:02:24 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	handle_char(char c, t_flags *flags)
{
	if (flags->number)
	{
		if (flags->minus)
		{
			write_buf(&c, 1);
			print_char(' ', flags->number - 1);
		}
		else
		{
			print_char(' ', flags->number - 1);
			write_buf(&c, 1);
		}
	}
	else
		write_buf(&c, 1);
}

void	handle_unsigned(unsigned int nb, t_flags *flags)
{
	int		digits;

	digits = count_digits_unsigned_base(nb, 10);
	if (!flags->minus && !flags->zero)
		print_char(' ', flags->number - digits);
	if (flags->dot && flags->dot_nb)
	{
		print_char('0', flags->dot_nb - digits);
		digits += flags->dot_nb - digits;
	}
	if (flags->minus && flags->number)
	{
		ft_putnbr_unsigned(nb);
		print_char(' ', flags->number - digits);
	}
	else
	{
		if (flags->zero)
			print_char('0', flags->number - digits);
		ft_putnbr_unsigned(nb);
	}
}

void	handle_ptr(void *ptr, t_flags *flags)
{
	unsigned long	value;
	int				digits_nb;

	value = (unsigned long) ptr;
	digits_nb = count_digits_unsigned_base(value, 16) + 2;
	if (!ptr)
		digits_nb = 3;
	if (!flags->minus && flags->number)
		print_char(' ', flags->number - digits_nb);
	if (!ptr)
		return (write_buf("0x0", 3));
	write_buf("0x", 2);
	if (flags->minus)
	{
		ft_putnbr_hex(value, "0123456789abcdef");
		print_char(' ', flags->number - digits_nb);
	}
	else
		ft_putnbr_hex(value, "0123456789abcdef");
}

void	handle_hex(unsigned int nb, t_flags *flags, char *base)
{
	int		hashtag;
	int		digits_nb;

	digits_nb = count_digits_unsigned_base(nb, 16);
	hashtag = process_hashtag(flags, nb);
	if (!flags->minus && !flags->zero && flags->number)
		print_char(' ', flags->number - digits_nb - hashtag);
	if (flags->dot && flags->dot_nb)
	{
		print_char('0', flags->dot_nb - digits_nb);
		if (flags->dot_nb - digits_nb > 0)
			digits_nb += flags->dot_nb - digits_nb;
	}
	if (flags->minus && flags->number)
	{
		ft_putnbr_hex(nb, base);
		print_char(' ', flags->number - digits_nb - hashtag);
	}
	else
	{
		if (flags->zero)
			print_char('0', flags->number - digits_nb - hashtag);
		ft_putnbr_hex(nb, base);
	}
}
