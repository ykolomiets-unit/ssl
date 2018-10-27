#ifndef HMAC_H
# define HMAC_H

# include "utils.h"
# include "md5.h"
# include "sha224_256.h"

typedef void	(*hash_init)(void *ctx);
typedef void	(*hash_update)(void *ctx, t_byte *input, uint32_t input_len);
typedef void	(*hash_final)(void *ctx, t_byte *digest);

typedef struct	s_hmac_help
{
	void		*ctx;
	t_byte		*ipad;
	t_byte		*opad;
	uint32_t	block_size;
	uint32_t	digest_size;
	hash_init	init;
	hash_update	update;
	hash_final	final;
	t_byte		*newkey;
}				t_hmac_help;

typedef struct	s_hmac_params
{
	t_byte		*text;
	uint32_t	text_len;
	t_byte		*key;
	uint32_t	key_len;
}				t_hmac_params;

void			hmac_md5(t_hmac_params params,
					t_byte digest[MD5_DIGEST_SIZE]);

void			hmac_sha256(t_hmac_params params,
					t_byte digest[SHA256_DIGEST_SIZE]);

#endif