#include "des.h"
#include "des_cbc_iteration.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

static void	des_cbc_init
(
	t_des_ctx *ctx,
	t_byte key[DES_KEY_LENGTH],
	t_byte iv[DES_IV_LENGTH],
	int	out_fd
)
{
	ctx->out = out_fd;
	bytes_to_big_endian_dwords(&ctx->key, key, DES_KEY_LENGTH);
	des_key_schedule(ctx->key, ctx->subkeys, ctx->mode);
	ft_memcpy(ctx->vector, iv, DES_IV_LENGTH);
}

static void	des_cbc_update(t_des_ctx *ctx, t_byte *input, uint32_t input_len, t_des_cbc_iteration iter)
{
	uint32_t	current_pos;
	uint32_t	start_pos;

	current_pos = 0;
	if (ctx->last_block_size > 0 && (input_len > DES_BLOCK_SIZE - ctx->last_block_size))
	{
		ft_memcpy(ctx->block, input, DES_BLOCK_SIZE - ctx->last_block_size);
		current_pos = DES_BLOCK_SIZE - ctx->last_block_size;
		iter(ctx->subkeys, ctx->block, ctx->vector);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	start_pos = current_pos;
	while (current_pos + DES_BLOCK_SIZE < input_len)
	{
		iter(ctx->subkeys, input + current_pos, ctx->vector);
		current_pos += DES_BLOCK_SIZE;
	}
	write(ctx->out, input + start_pos, current_pos - start_pos);
	ctx->last_block_size = input_len - current_pos;
	ft_memcpy(ctx->block, input + current_pos, ctx->last_block_size);
}

static void	des_cbc_final(t_des_ctx *ctx, t_des_cbc_iteration iter)
{
	if (ctx->mode == ENCODE)
	{
		if (ctx->last_block_size == 8)
		{
			iter(ctx->subkeys, ctx->block, ctx->vector);
			write(ctx->out, ctx->block, DES_BLOCK_SIZE);
			ctx->last_block_size = 0;
		}
		des_add_padding(ctx->last_block_size, ctx->block);
		iter(ctx->subkeys, ctx->block, ctx->vector);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	else
	{
		iter(ctx->subkeys, ctx->block, ctx->vector);
		if (ctx->block[DES_BLOCK_SIZE - 1] < 1 || ctx->block[DES_BLOCK_SIZE - 1] > 8)
			ft_printf("Wrong padding\n");
		write(ctx->out, ctx->block, DES_BLOCK_SIZE - ctx->block[DES_BLOCK_SIZE - 1]);
	}
}

void		des_cbc_encode(t_byte key[DES_KEY_LENGTH], t_byte iv[DES_IV_LENGTH], int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = ENCODE;
	des_cbc_init(&ctx, key, iv, out);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_cbc_update(&ctx, buffer, r, des_cbc_encryption_iteration);
	des_cbc_final(&ctx, des_cbc_encryption_iteration);
}

void		des_cbc_decode(t_byte key[DES_KEY_LENGTH], t_byte iv[DES_IV_LENGTH], int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = DECODE;
	des_cbc_init(&ctx, key, iv, out);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_cbc_update(&ctx, buffer, r, des_cbc_decryption_iteration);
	des_cbc_final(&ctx, des_cbc_decryption_iteration);
}
