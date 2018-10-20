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

# include "utils.h"

typedef struct	s_md5_context
{
	t_word		state[4];
	t_dword		count;
	t_byte		buffer[64];
}				t_md5_context;

void			md5_init(t_md5_context *context);
void			md5_update(t_md5_context *context, t_byte *input,
							uint32_t input_len);
void			md5_transform(t_word state[4], t_byte buffer[64]);
void			md5_final(t_md5_context *context, t_byte digest[16]);

void			md5_string(char *string, t_byte digest[16]);

#endif
