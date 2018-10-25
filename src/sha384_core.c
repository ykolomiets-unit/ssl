/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 22:58:33 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/25 18:18:48 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384_512.h"
#include "libft.h"

void		sha384_init(t_sha384_ctx *ctx)
{
	static t_dword	start_value[8] = { 0xCBBB9D5DC1059ED8ULL,
		0x629A292A367CD507ULL, 0x9159015A3070DD17ULL,
		0x152FECD8F70E5939ULL, 0x67332667FFC00B31ULL,
		0x8EB44A8768581511ULL, 0xDB0C2E0D64F98FA7ULL,
		0x47B5481DBEFA4FA4ULL };

	sha384_512_init(ctx, start_value);
}

void		sha384_update
(
	t_sha384_ctx *ctx,
	t_byte *input,
	uint32_t input_len
)
{
	sha512_update(ctx, input, input_len);
}

void		sha384_final
(
	t_sha384_ctx *ctx,
	t_byte digest[48]
)
{
	sha384_512_final(ctx);
	big_endian_dwords_to_bytes(ctx->state, digest, 48);
}
