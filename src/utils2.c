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

void	bytes_to_big_endian_dwords
(
	t_dword *words,
	t_byte *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < bytes_len)
	{
		words[i] = ((t_dword)bytes[j] << 56) | ((t_dword)bytes[j + 1] << 48)
			| ((t_dword)bytes[j + 2] << 40) | ((t_dword)bytes[j + 3] << 32)
			| ((t_dword)bytes[j + 4] << 24) | ((t_dword)bytes[j + 5] << 16)
			| ((t_dword)bytes[j + 6] << 8) | ((t_dword)bytes[j + 7]);
		i++;
		j += 8;
	}
}

void	big_endian_dwords_to_bytes
(
	t_dword *words,
	t_byte *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;
	t_dword		temp_word;

	i = 0;
	j = 0;
	while (j < bytes_len)
	{
		temp_word = words[i];
		bytes[j + 7] = temp_word & 0xff;
		bytes[j + 6] = (temp_word >> 8) & 0xff;
		bytes[j + 5] = (temp_word >> 16) & 0xff;
		bytes[j + 4] = (temp_word >> 24) & 0xff;
		bytes[j + 3] = (temp_word >> 32) & 0xff;
		bytes[j + 2] = (temp_word >> 40) & 0xff;
		bytes[j + 1] = (temp_word >> 48) & 0xff;
		bytes[j] = (temp_word >> 56) & 0xff;
		i++;
		j += 8;
	}
}

void	filter_str(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\t' || *buffer == '\n')
			*buffer = ' ';
		buffer++;
	}
}
