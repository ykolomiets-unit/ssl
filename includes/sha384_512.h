/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 23:06:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/24 23:06:27 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_512_H
# define SHA384_512_H

# include "utils.h"

typedef struct			s_sha512_ctx
{
	t_dword				state[8];
	t_dword				count[2];
	t_byte				buffer[128];
}						t_sha512_ctx;

typedef t_sha512_ctx	t_sha384_ctx;

void					sha384_512_init(t_sha512_ctx *ctx,
							t_dword start_value[8]);
void					sha384_512_final(t_sha512_ctx *ctx);

void					sha512_init(t_sha512_ctx *ctx);
void					sha512_update(t_sha512_ctx *ctx,
							t_byte *input, uint32_t input_len);
void					sha512_transform(t_dword state[8], t_byte buffer[128]);
void					sha512_final(t_sha512_ctx *ctx,
							t_byte digest[64]);

void					sha384_init(t_sha384_ctx *ctx);
void					sha384_update(t_sha384_ctx *ctx,
							t_byte *input, uint32_t input_len);
void					sha384_final(t_sha384_ctx *ctx,
							t_byte digest[48]);

void					sha512_string(char *string, t_byte digest[64]);
void					sha384_string(char *string, t_byte digest[48]);
void					sha512_file(int fd, t_byte digest[64]);
void					sha384_file(int fd, t_byte digest[38]);
void					sha512_filter(t_byte digest[64], int echo);
void					sha384_filter(t_byte digest[48], int echo);

#endif
