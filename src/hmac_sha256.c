/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:44:59 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 17:24:49 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmac_sha256.h"

static void	pad_with_zero
(
	t_byte *key,
	uint32_t key_len,
	t_byte result[SHA256_BLOCK_SIZE]
)
{
	uint32_t		i;

	i = 0;
	while (i < key_len)
	{
		result[i] = key[i];
		i++;
	}
	while (i < SHA256_BLOCK_SIZE)
	{
		result[i] = 0;
		i++;
	}
}

static void	io_pad
(
	t_byte key[SHA256_BLOCK_SIZE],
	t_byte k_ipad[SHA256_BLOCK_SIZE],
	t_byte k_opad[SHA256_BLOCK_SIZE]
)
{
	int		i;

	i = 0;
	while (i < SHA256_BLOCK_SIZE)
	{
		k_ipad[i] = key[i] ^ 0x36;
		k_opad[i] = key[i] ^ 0x5c;
		i++;
	}
}

void		hmac_sha256(t_hmac_params *params,
				t_byte result[SHA256_DIGEST_SIZE])
{
	t_sha256_ctx	sha256_ctx;
	t_byte			k_ipad[SHA256_BLOCK_SIZE];
	t_byte			k_opad[SHA256_BLOCK_SIZE];
	t_byte			temp_key[SHA256_BLOCK_SIZE];

	if (params->key_length > SHA256_BLOCK_SIZE)
		sha256_buffer(params->key, params->key_length, temp_key);
	else
		pad_with_zero(params->key, params->key_length, temp_key);
	io_pad(temp_key, k_ipad, k_opad);
	sha256_init(&sha256_ctx);
	sha256_update(&sha256_ctx, k_ipad, SHA256_BLOCK_SIZE);
	sha256_update(&sha256_ctx, params->message, params->message_length);
	sha256_final(&sha256_ctx, result);
	sha256_init(&sha256_ctx);
	sha256_update(&sha256_ctx, k_opad, SHA256_BLOCK_SIZE);
	sha256_update(&sha256_ctx, result, SHA256_DIGEST_SIZE);
	sha256_final(&sha256_ctx, result);
}
