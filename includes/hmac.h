/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:19:39 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/27 18:20:41 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_H
# define HMAC_H

# include "types.h"
# include "md5.h"
# include "sha224_256.h"

typedef void		(*t_hash_init)(void *ctx);
typedef void		(*t_hash_update)(void *ctx,
						t_byte *input, uint32_t input_len);
typedef void		(*t_hash_final)(void *ctx, t_byte *digest);

typedef struct		s_hmac_help
{
	void			*ctx;
	t_byte			*ipad;
	t_byte			*opad;
	uint32_t		block_size;
	uint32_t		digest_size;
	t_hash_init		init;
	t_hash_update	update;
	t_hash_final	final;
	t_byte			*newkey;
}					t_hmac_help;

typedef struct		s_hmac_params
{
	t_byte			*text;
	uint32_t		text_len;
	t_byte			*key;
	uint32_t		key_len;
}					t_hmac_params;

void				hmac_md5(t_hmac_params params,
						t_byte digest[MD5_DIGEST_SIZE]);

void				hmac_sha256(t_hmac_params params,
						t_byte digest[SHA256_DIGEST_SIZE]);

#endif
