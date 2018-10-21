/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:36:47 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:36:54 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	little_endian_dword_to_bytes
(
	t_dword value,
	t_byte bytes[8]
)
{
	bytes[0] = value & 0xff;
	bytes[1] = (value >> 8) & 0xff;
	bytes[2] = (value >> 16) & 0xff;
	bytes[3] = (value >> 24) & 0xff;
	bytes[4] = (value >> 32) & 0xff;
	bytes[5] = (value >> 40) & 0xff;
	bytes[6] = (value >> 48) & 0xff;
	bytes[7] = (value >> 56) & 0xff;
}

void	big_endian_dword_to_bytes
(
	t_dword value,
	t_byte bytes[8]
)
{
	bytes[7] = value & 0xff;
	bytes[6] = (value >> 8) & 0xff;
	bytes[5] = (value >> 16) & 0xff;
	bytes[4] = (value >> 24) & 0xff;
	bytes[3] = (value >> 32) & 0xff;
	bytes[2] = (value >> 40) & 0xff;
	bytes[1] = (value >> 48) & 0xff;
	bytes[0] = (value >> 56) & 0xff;
}
