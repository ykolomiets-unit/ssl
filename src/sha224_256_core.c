/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_256_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:18:35 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:18:47 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_256.h"
#include "utils.h"
#include "libft.h"

void	sha224_256_init
(
	t_sha256_ctx *ctx,
	t_word start_value[8]
)
{
	int				i;

	ctx->count = 0;
	i = 0;
	while (i < 8)
	{
		ctx->state[i] = start_value[i];
		i++;
	}
	ft_bzero(ctx->buffer, SHA256_BLOCK_SIZE);
}

void	sha224_256_final
(
	t_sha256_ctx *ctx
)
{
	static t_byte	padding[] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0 };
	t_byte			bits_amount[8];
	uint32_t		index;
	uint32_t		pad_len;

	big_endian_dword_to_bytes(ctx->count, bits_amount);
	index = (ctx->count / 8) % 64;
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	sha256_update(ctx, padding, pad_len);
	sha256_update(ctx, bits_amount, 8);
}
