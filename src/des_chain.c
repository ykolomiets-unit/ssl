/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_chain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:25:33 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:25:34 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "ssl_error.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

static t_des_iter	g_modes_iter[DES_MODES_COUNT][2] = {
	{
		des_ecb_iteration,
		des_ecb_iteration,
	},
	{
		des_cbc_encryption_iteration,
		des_cbc_decryption_iteration
	},
	{
		des_pcbc_encryption_iteration,
		des_pcbc_decryption_iteration
	},
	{
		des_cfb_encryption_iteration,
		des_cfb_decryption_iteration
	},
	{
		des_ofb_encryption_iteration,
		des_ofb_decryption_iteration
	}
};

static void	set_subkeys(t_des_ctx *ctx, t_des_chain_params *p)
{
	uint64_t	key1;
	uint64_t	key2;
	uint64_t	key3;

	bytes_to_big_endian_dwords(&key1, p->key, DES_KEY_LENGTH);
	if (p->des3 == FALSE)
	{
		if (ctx->encode || p->mode == DES_MODE_CFB || p->mode == DES_MODE_OFB)
			des_key_schedule(key1, ctx->subkeys, TRUE);
		else
			des_key_schedule(key1, ctx->subkeys, FALSE);
		return ;
	}
	bytes_to_big_endian_dwords(&key2, p->key + 8, DES_KEY_LENGTH);
	bytes_to_big_endian_dwords(&key3, p->key + 16, DES_KEY_LENGTH);
	if (ctx->encode || p->mode == DES_MODE_CFB || p->mode == DES_MODE_OFB)
	{
		des_key_schedule(key1, ctx->subkeys, TRUE);
		des_key_schedule(key2, ctx->subkeys + 16, FALSE);
		des_key_schedule(key3, ctx->subkeys + 32, TRUE);
		return ;
	}
	des_key_schedule(key1, ctx->subkeys + 32, FALSE);
	des_key_schedule(key2, ctx->subkeys + 16, TRUE);
	des_key_schedule(key3, ctx->subkeys, FALSE);
}

static void	des_init
(
	t_des_ctx *ctx,
	t_des_chain_params *params
)
{
	ft_bzero(ctx, sizeof(t_des_ctx));
	ctx->out = params->out;
	ctx->encode = params->encode;
	set_subkeys(ctx, params);
	ft_memcpy(ctx->vector, params->iv, DES_IV_LENGTH);
	ctx->iter = g_modes_iter[params->mode][ctx->encode ? 0 : 1];
	ctx->core = params->des3 ? des3_core : des_core;
	if (params->mode == DES_MODE_CFB || params->mode == DES_MODE_OFB)
		ctx->require_padding = FALSE;
	else
		ctx->require_padding = TRUE;
}

static void	des_update(t_des_ctx *ctx, t_byte *input, uint32_t input_len)
{
	uint32_t	current_pos;
	uint32_t	start_pos;

	current_pos = 0;
	if (ctx->last_block_size > 0 &&
		(input_len > DES_BLOCK_SIZE - ctx->last_block_size))
	{
		ft_memcpy(ctx->block, input, DES_BLOCK_SIZE - ctx->last_block_size);
		current_pos = DES_BLOCK_SIZE - ctx->last_block_size;
		ctx->iter(ctx->subkeys, ctx->block, ctx->vector, ctx->core);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	start_pos = current_pos;
	while (current_pos + DES_BLOCK_SIZE < input_len)
	{
		ctx->iter(ctx->subkeys, input + current_pos, ctx->vector, ctx->core);
		current_pos += DES_BLOCK_SIZE;
	}
	write(ctx->out, input + start_pos, current_pos - start_pos);
	ctx->last_block_size = input_len - current_pos;
	ft_memcpy(ctx->block, input + current_pos, ctx->last_block_size);
}

static void	des_final(t_des_ctx *ctx)
{
	if (ctx->encode == TRUE)
	{
		if (ctx->last_block_size == 8)
		{
			ctx->iter(ctx->subkeys, ctx->block, ctx->vector, ctx->core);
			write(ctx->out, ctx->block, DES_BLOCK_SIZE);
			ctx->last_block_size = 0;
		}
		if (!ctx->require_padding)
			return ;
		des_add_padding(ctx->last_block_size, ctx->block);
		ctx->iter(ctx->subkeys, ctx->block, ctx->vector, ctx->core);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
		return ;
	}
	ctx->iter(ctx->subkeys, ctx->block, ctx->vector, ctx->core);
	if (!ctx->require_padding)
		write(ctx->out, ctx->block, ctx->last_block_size);
	else
	{
		if (ctx->block[7] < 1 || ctx->block[7] > 8)
			ssl_error("Wrong padding\n");
		write(ctx->out, ctx->block, DES_BLOCK_SIZE - ctx->block[7]);
	}
}

void		des_chain(t_des_chain_params *params)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	des_init(&ctx, params);
	r = 0;
	while ((r = read(params->in, buffer, 4096)) > 0)
		des_update(&ctx, buffer, r);
	des_final(&ctx);
}
