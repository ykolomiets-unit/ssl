/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:34:07 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:35:14 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"

void		md5_init
(
	t_md5_ctx *ctx
)
{
	ctx->count = 0;
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ft_bzero(ctx->buffer, 64);
}

void		md5_update
(
	t_md5_ctx *ctx,
	t_byte *input,
	uint32_t input_len
)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	part_len;

	i = 0;
	index = (ctx->count / 8) % 64;
	ctx->count += input_len * 8;
	part_len = 64 - index;
	if (input_len >= part_len)
	{
		ft_memcpy(&ctx->buffer[index], input, part_len);
		md5_transform(ctx->state, ctx->buffer);
		i = part_len;
		while (i + 63 < input_len)
		{
			md5_transform(ctx->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	ft_memcpy(&ctx->buffer[index], &input[i], input_len - i);
}

void		md5_final
(
	t_md5_ctx *ctx,
	t_byte digest[MD5_DIGEST_SIZE]
)
{
	static t_byte	padding[64] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0 };
	t_byte			bits_amount[8];
	uint32_t		index;
	uint32_t		pad_len;

	little_endian_dword_to_bytes(ctx->count, bits_amount);
	index = (ctx->count / 8) % 64;
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(ctx, padding, pad_len);
	md5_update(ctx, bits_amount, 8);
	little_endian_words_to_bytes(ctx->state, digest, 16);
}
