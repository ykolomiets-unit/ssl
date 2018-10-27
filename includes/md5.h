/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:37:24 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:37:52 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "types.h"

# define MD5_BLOCK_SIZE 64
# define MD5_DIGEST_SIZE 16

typedef struct	s_md5_ctx
{
	t_word		state[4];
	t_dword		count;
	t_byte		buffer[MD5_BLOCK_SIZE];
}				t_md5_ctx;

void			md5_init(t_md5_ctx *ctx);
void			md5_update(t_md5_ctx *ctx, t_byte *input,
							uint32_t input_len);
void			md5_transform(t_word state[4], t_byte buffer[MD5_BLOCK_SIZE]);
void			md5_final(t_md5_ctx *ctx, t_byte digest[MD5_DIGEST_SIZE]);

void			md5_string(char *string, t_byte digest[MD5_DIGEST_SIZE]);
void			md5_file(int fd, t_byte digest[MD5_DIGEST_SIZE]);
void			md5_filter(t_byte digest[MD5_DIGEST_SIZE], int echo);

#endif
