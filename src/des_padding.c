/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:40:19 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:40:21 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void		des_add_padding(int filled, t_byte block[DES_BLOCK_SIZE])
{
	int	value;

	value = DES_BLOCK_SIZE - filled;
	while (filled < DES_BLOCK_SIZE)
	{
		block[filled] = value;
		filled++;
	}
}
