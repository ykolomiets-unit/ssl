/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:36:47 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:36:54 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	bytes_to_low_order_words
(
	uint32_t *words,
	char *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < bytes_len)
	{
		words[i] = (uint32_t)bytes[j] | ((uint32_t)bytes[j + 1] << 8)
			| ((uint32_t)bytes[j + 2] << 16) | ((uint32_t)bytes[j + 3] << 24);
		i++;
		j += 4;
	}
}

void	low_order_words_to_bytes
(
	uint32_t *words,
	char *bytes,
	uint32_t bytes_len
)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	temp_word;

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
