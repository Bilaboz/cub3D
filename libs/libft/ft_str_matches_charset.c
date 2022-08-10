/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_matches_charset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:32:13 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/16 20:35:56 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		char_is_in_str(char c, char *str);

int	ft_str_matches_charset(char *str, char *charset)
{
	while (*str)
	{
		if (!char_is_in_str(*str, charset))
			return (0);
		str++;
	}
	return (1);
}
