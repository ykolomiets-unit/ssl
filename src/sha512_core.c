/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 22:58:33 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/24 22:59:53 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384_512.h"
#include "libft.h"

void		sha512_init(t_sha512_ctx *ctx)
{
	static t_dword	start_value[8] = { 0x6A09E667F3BCC908ll,
		0xBB67AE8584CAA73Bll, 0x3C6EF372FE94F82Bll, 0xA54FF53A5F1D36F1ll,
		0x510E527FADE682D1ll, 0x9B05688C2B3E6C1Fll, 0x1F83D9ABFB41BD6Bll,
		0x5BE0CD19137E2179ll};

	sha384_512_init(ctx, start_value);
}

static void	add_len(t_sha512_ctx *ctx, uint32_t input_len)
{
	t_dword temp;

	temp = ctx->count[0];
	if ((ctx->count[0] += input_len) < temp)
		ctx->count[1]++;
}

void		sha512_update
(
	t_sha512_ctx *ctx,
	t_byte *input,
	uint32_t input_len
)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	part_len;

	i = 0;
	index = (ctx->count[0] / 8) % 128;
	add_len(ctx, input_len * 8);
	part_len = 128 - index;
	if (input_len >= part_len)
	{
		ft_memcpy(&ctx->buffer[index], input, part_len);
		sha512_transform(ctx->state, ctx->buffer);
		i = part_len;
		while (i + 127 < input_len)
		{
			sha512_transform(ctx->state, &input[i]);
			i += 128;
		}
		index = 0;
	}
	ft_memcpy(&ctx->buffer[index], &input[i], input_len - i);
}

void		sha512_final
(
	t_sha512_ctx *ctx,
	t_byte digest[64]
)
{
	sha384_512_final(ctx);
	big_endian_dwords_to_bytes(ctx->state, digest, 64);
}
