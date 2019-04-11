#include "des.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

typedef struct	s_des_ctx
{
	int			mode;
	uint64_t	key;
	uint64_t	subkeys[16];
	t_byte		block[DES_BLOCK_SIZE];
	uint32_t	last_block_size;
	int			out;
}				t_des_ctx;

static void		des_ecb_init(t_des_ctx *ctx)
{
	des_key_schedule(ctx->key, ctx->subkeys, ctx->mode);
}

static void		des_ecb_update(t_des_ctx *ctx, t_byte *input, uint32_t input_len)
{
	uint32_t	current_pos;
	uint32_t	start_pos;

	current_pos = 0;
	if (ctx->last_block_size > 0 && (input_len > DES_BLOCK_SIZE - ctx->last_block_size))
	{
		ft_memcpy(ctx->block, input, DES_BLOCK_SIZE - ctx->last_block_size);
		current_pos = DES_BLOCK_SIZE - ctx->last_block_size;
		des_core(ctx->subkeys, ctx->block, ctx->block);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	start_pos = current_pos;
	while (current_pos + DES_BLOCK_SIZE < input_len)
	{
		des_core(ctx->subkeys, input + current_pos, input + current_pos);
		current_pos += DES_BLOCK_SIZE;
	}
	write(ctx->out, input + start_pos, current_pos - start_pos);
	ctx->last_block_size = input_len - current_pos;
	ft_memcpy(ctx->block, input + current_pos, ctx->last_block_size);
}

static void		des_ecb_final(t_des_ctx *ctx)
{
	if (ctx->mode == ENCODE)
	{
		if (ctx->last_block_size == 8)
		{
			des_core(ctx->subkeys, ctx->block, ctx->block);
			write(ctx->out, ctx->block, DES_BLOCK_SIZE);
			ctx->last_block_size = 0;
		}
		des_add_padding(ctx->last_block_size, ctx->block);
		des_core(ctx->subkeys, ctx->block, ctx->block);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	else
	{
		des_core(ctx->subkeys, ctx->block, ctx->block);
		if (ctx->block[DES_BLOCK_SIZE - 1] < 1 || ctx->block[DES_BLOCK_SIZE - 1] > 8)
			ft_printf("Wrong padding\n");
		write(ctx->out, ctx->block, DES_BLOCK_SIZE - ctx->block[DES_BLOCK_SIZE - 1]);
	}
}

void		des_ecb_encode(t_byte key[DES_KEY_LENGTH], int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = ENCODE;
	bytes_to_big_endian_dwords(&ctx.key, key, DES_KEY_LENGTH);
	ctx.out = out;
	des_ecb_init(&ctx);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_ecb_update(&ctx, buffer, r);
	des_ecb_final(&ctx);
}

void		des_ecb_decode(t_byte key[DES_KEY_LENGTH], int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = DECODE;
	bytes_to_big_endian_dwords(&ctx.key, key, DES_KEY_LENGTH);
	ctx.out = out;
	des_ecb_init(&ctx);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_ecb_update(&ctx, buffer, r);
	des_ecb_final(&ctx);
}
