/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:51:12 by alorain           #+#    #+#             */
/*   Updated: 2022/07/05 15:51:26 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(void **ptr1, void **ptr2)
{
	void	*temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
