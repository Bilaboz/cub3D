/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:21:05 by rcarles           #+#    #+#             */
/*   Updated: 2022/06/13 13:47:10 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	int			j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *) str);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] && to_find[j] && str[i + j] == to_find[j]
				&& i + j < len)
			{
				j++;
			}
			if (to_find[j] == '\0')
				return ((char *) &str[i]);
		}
		i++;
	}
	return (NULL);
}
