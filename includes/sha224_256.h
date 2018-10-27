/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_256.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:17:03 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:17:04 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_256_H
# define SHA224_256_H

# define SHA224_DIGEST_SIZE 28
# define SHA256_DIGEST_SIZE 32

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
							t_byte digest[SHA256_DIGEST_SIZE]);

void					sha224_init(t_sha224_ctx *ctx);
void					sha224_update(t_sha224_ctx *ctx,
							t_byte *input, uint32_t input_len);
void					sha224_final(t_sha224_ctx *ctx,
							t_byte digest[SHA224_DIGEST_SIZE]);

void					sha256_string(char *string,
							t_byte digest[SHA256_DIGEST_SIZE]);
void					sha224_string(char *string,
							t_byte digest[SHA224_DIGEST_SIZE]);
void					sha256_file(int fd, t_byte digest[SHA256_DIGEST_SIZE]);
void					sha224_file(int fd, t_byte digest[SHA224_DIGEST_SIZE]);
void					sha224_filter(t_byte digest[SHA256_DIGEST_SIZE],
							int echo);
void					sha256_filter(t_byte digest[SHA224_DIGEST_SIZE],
							int echo);

#endif
