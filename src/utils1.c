/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:36:47 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:36:54 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	bytes_to_little_endian_words
(
	t_word *words,
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
		words[i] = (t_word)bytes[j] | ((t_word)bytes[j + 1] << 8)
			| ((t_word)bytes[j + 2] << 16) | ((t_word)bytes[j + 3] << 24);
		i++;
		j += 4;
	}
}

void	bytes_to_big_endian_words
(
	t_word *words,
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
		words[i] = ((t_word)bytes[j] << 24) | ((t_word)bytes[j + 1] << 16)
			| ((t_word)bytes[j + 2] << 8) | ((t_word)bytes[j + 3]);
		i++;
		j += 4;
	}
}

void	little_endian_words_to_bytes
(
	t_word *words,
	t_byte *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;
	t_word		temp_word;

	i = 0;
	j = 0;
	while (j < bytes_len)
	{
		temp_word = words[i];
		bytes[j] = temp_word & 0xff;
		bytes[j + 1] = (temp_word >> 8) & 0xff;
		bytes[j + 2] = (temp_word >> 16) & 0xff;
		bytes[j + 3] = (temp_word >> 24) & 0xff;
		i++;
		j += 4;
	}
}

void	big_endian_words_to_bytes
(
	t_word *words,
	t_byte *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;
	t_word		temp_word;

	i = 0;
	j = 0;
	while (j < bytes_len)
	{
		temp_word = words[i];
		bytes[j + 3] = temp_word & 0xff;
		bytes[j + 2] = (temp_word >> 8) & 0xff;
		bytes[j + 1] = (temp_word >> 16) & 0xff;
		bytes[j] = (temp_word >> 24) & 0xff;
		i++;
		j += 4;
	}
}
