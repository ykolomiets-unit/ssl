/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:21:51 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:21:52 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_256.h"
#include "utils.h"
#include "libft.h"

void		sha256_init(t_sha256_ctx *ctx)
{
	static t_word	start_value[8] = { 0x6A09E667, 0xBB67AE85, 0x3C6EF372,
		0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19};

	sha224_256_init(ctx, start_value);
}

void		sha256_update
(
	t_sha256_ctx *ctx,
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
		sha256_transform(ctx->state, ctx->buffer);
		i = part_len;
		while (i + 63 < input_len)
		{
			sha256_transform(ctx->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	ft_memcpy(&ctx->buffer[index], &input[i], input_len - i);
}

void		sha256_final
(
	t_sha256_ctx *ctx,
	t_byte digest[SHA256_DIGEST_SIZE]
)
{
	sha224_256_final(ctx);
	big_endian_words_to_bytes(ctx->state, digest, SHA256_DIGEST_SIZE);
}
