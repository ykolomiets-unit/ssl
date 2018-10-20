#ifndef SHA224_256_H
# define SHA224_256_H

# include "utils.h"

typedef struct			s_sha256_ctx
{
	t_word				state[8];
	t_dword				count;
	t_byte				buffer[64];
}						t_sha256_ctx;

typedef t_sha256_ctx	t_sha224_ctx;

void					sha224_256_init(t_sha256_ctx *ctx,
							t_word start_value[8]);
void					sha224_256_final(t_sha256_ctx *ctx);

void					sha256_init(t_sha256_ctx *ctx);
void					sha256_update(t_sha256_ctx *ctx,
							t_byte *input, uint32_t input_len);
void					sha256_transform(t_word state[8], t_byte buffer[64]);
void					sha256_final(t_sha256_ctx *ctx,
							t_byte digest[32]);

void					sha224_init(t_sha224_ctx *ctx);
void					sha224_update(t_sha224_ctx *ctx,
							t_byte *input, uint32_t input_len);
void					sha224_final(t_sha224_ctx *ctx,
							t_byte digest[28]);

void					sha256_string(char *string, t_byte digest[32]);
void					sha224_string(char *string, t_byte digest[28]);

#endif
