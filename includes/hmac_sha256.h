/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:19:39 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:53:16 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_SHA256_H
# define HMAC_SHA256_H

# include "types.h"
# include "sha224_256.h"

# define HMAC_SHA256_OUTPUT_LEN SHA256_DIGEST_SIZE

typedef struct	s_hmac_params
{
	t_byte		*key;
	uint32_t	key_length;
	t_byte		*message;
	uint32_t	message_length;
}				t_hmac_params;

void			hmac_sha256(t_hmac_params *params,
					t_byte result[HMAC_SHA256_OUTPUT_LEN]);

#endif
