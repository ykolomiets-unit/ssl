/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:53:23 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 17:25:16 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pbkdf2.h"
#include "hmac_sha256.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

static t_byte	*allocate(t_byte *salt, uint32_t salt_length,
							uint32_t block_num)
{
	t_byte		*salt_and_block_num;

	salt_and_block_num = (t_byte *)malloc(salt_length + sizeof(block_num));
	if (salt_and_block_num == NULL)
	{
		ft_printf("Memory allocation failed");
		exit(1);
	}
	ft_memcpy(salt_and_block_num, salt, salt_length);
	big_endian_words_to_bytes(&block_num, salt_and_block_num + salt_length,
								sizeof(block_num));
	return (salt_and_block_num);
}

static void		xor_blocks(t_byte b1[HMAC_SHA256_OUTPUT_LEN],
					t_byte b2[HMAC_SHA256_OUTPUT_LEN])
{
	uint32_t	i;

	i = 0;
	while (i < HMAC_SHA256_OUTPUT_LEN)
	{
		b1[i] ^= b2[i];
		i++;
	}
}

static void		f(t_pbkdf2_params params, uint32_t block_num,
					t_byte block[HMAC_SHA256_OUTPUT_LEN])
{
	t_byte			*salt_and_block_num;
	t_byte			temp_block[HMAC_SHA256_OUTPUT_LEN];
	t_hmac_params	hmac_params;
	uint32_t		i;

	salt_and_block_num = allocate(params.salt, params.salt_length, block_num);
	hmac_params.key = params.password;
	hmac_params.key_length = params.password_length;
	hmac_params.message = salt_and_block_num;
	hmac_params.message_length = params.salt_length + sizeof(block_num);
	hmac_sha256(&hmac_params, block);
	ft_memcpy(temp_block, block, HMAC_SHA256_OUTPUT_LEN);
	hmac_params.message = temp_block;
	hmac_params.message_length = HMAC_SHA256_OUTPUT_LEN;
	i = 1;
	while (i < params.iteration_count)
	{
		hmac_sha256(&hmac_params, temp_block);
		xor_blocks(block, temp_block);
		i++;
	}
	free(salt_and_block_num);
}

void			pbkdf2(t_pbkdf2_params params, t_byte *dk, uint32_t dk_len)
{
	uint32_t	l;
	uint32_t	r;
	uint32_t	i;
	t_byte		block[HMAC_SHA256_OUTPUT_LEN];

	l = dk_len / HMAC_SHA256_OUTPUT_LEN;
	r = dk_len % HMAC_SHA256_OUTPUT_LEN;
	i = 0;
	while (i < l)
	{
		f(params, i + 1, block);
		ft_memcpy(dk + i * HMAC_SHA256_OUTPUT_LEN, block,
					HMAC_SHA256_OUTPUT_LEN);
		i++;
	}
	if (r)
	{
		f(params, i + 1, block);
		ft_memcpy(dk + i * HMAC_SHA256_OUTPUT_LEN, block, r);
	}
}
