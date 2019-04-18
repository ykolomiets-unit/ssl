#include "des.h"
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

static void	des_init
(
	t_des_ctx *ctx,
	t_des_chain_params *params
)
{
	ft_bzero(ctx, sizeof(t_des_ctx));
	ctx->out = params->out;
	ctx->encode = params->encode;
	bytes_to_big_endian_dwords(&ctx->key, params->key, DES_KEY_LENGTH);
	if (params->mode == DES_MODE_CFB || params->mode == DES_MODE_OFB)
		des_key_schedule(ctx->key, ctx->subkeys, TRUE);
	else
		des_key_schedule(ctx->key, ctx->subkeys, ctx->encode);
	ft_memcpy(ctx->vector, params->iv, DES_IV_LENGTH);
	ctx->iter = g_modes_iter[params->mode][ctx->encode ? 0 : 1];
}

static void	des_update(t_des_ctx *ctx, t_byte *input, uint32_t input_len)
{
	uint32_t	current_pos;
	uint32_t	start_pos;

	current_pos = 0;
	if (ctx->last_block_size > 0 && (input_len > DES_BLOCK_SIZE - ctx->last_block_size))
	{
		ft_memcpy(ctx->block, input, DES_BLOCK_SIZE - ctx->last_block_size);
		current_pos = DES_BLOCK_SIZE - ctx->last_block_size;
		ctx->iter(ctx->subkeys, ctx->block, ctx->vector);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	start_pos = current_pos;
	while (current_pos + DES_BLOCK_SIZE < input_len)
	{
		ctx->iter(ctx->subkeys, input + current_pos, ctx->vector);
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
			ctx->iter(ctx->subkeys, ctx->block, ctx->vector);
			write(ctx->out, ctx->block, DES_BLOCK_SIZE);
			ctx->last_block_size = 0;
		}
		des_add_padding(ctx->last_block_size, ctx->block);
		ctx->iter(ctx->subkeys, ctx->block, ctx->vector);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	else
	{
		ctx->iter(ctx->subkeys, ctx->block, ctx->vector);
		if (ctx->block[DES_BLOCK_SIZE - 1] < 1 || ctx->block[DES_BLOCK_SIZE - 1] > 8)
			ft_printf("Wrong padding\n");
		write(ctx->out, ctx->block, DES_BLOCK_SIZE - ctx->block[DES_BLOCK_SIZE - 1]);
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
