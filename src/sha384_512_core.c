/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 22:57:53 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/24 22:57:54 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384_512.h"
#include "libft.h"

#define ZEROES 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

void	sha384_512_init
(
	t_sha512_ctx *ctx,
	t_dword start_value[8]
)
{
	int				i;

	ctx->count[0] = 0;
	ctx->count[1] = 0;
	i = 0;
	while (i < 8)
	{
		ctx->state[i] = start_value[i];
		i++;
	}
	ft_bzero(ctx->buffer, 128);
}

void	sha384_512_final
(
	t_sha512_ctx *ctx
)
{
	static t_byte	padding[] = { 0x80, ZEROES, ZEROES, ZEROES, ZEROES,
		ZEROES, ZEROES, ZEROES, ZEROES, ZEROES, ZEROES, ZEROES, ZEROES,
		0, 0, 0, 0, 0, 0, 0};
	t_byte			bits_amount[16];
	uint32_t		index;
	uint32_t		pad_len;

	big_endian_dword_to_bytes(ctx->count[1], bits_amount);
	big_endian_dword_to_bytes(ctx->count[0], bits_amount + 8);
	index = (ctx->count[0] / 8) % 128;
	pad_len = (index < 112) ? (112 - index) : (240 - index);
	sha512_update(ctx, padding, pad_len);
	sha512_update(ctx, bits_amount, 16);
}
