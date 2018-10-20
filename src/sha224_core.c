/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:20:43 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:20:45 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_256.h"
#include "utils.h"

void		sha224_init
(
	t_sha224_ctx *ctx
)
{
	static t_word	start_value[8] = { 0xC1059ED8, 0x367CD507, 0x3070DD17,
		0xF70E5939, 0xFFC00B31, 0x68581511, 0x64F98FA7, 0xBEFA4FA4};

	sha224_256_init(ctx, start_value);
}

void		sha224_update
(
	t_sha224_ctx *ctx,
	t_byte *input,
	uint32_t input_len
)
{
	sha256_update(ctx, input, input_len);
}

void		sha224_final
(
	t_sha224_ctx *ctx,
	t_byte digest[28]
)
{
	sha224_256_final(ctx);
	big_endian_words_to_bytes(ctx->state, digest, 28);
}
