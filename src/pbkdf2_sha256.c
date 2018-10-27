/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2_sha256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 19:40:09 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/27 19:40:30 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pbkdf2.h"
#include "hmac.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>

static void	f
(
	t_pbkdf2_params params,
	int32_t block_index,
	t_byte buffer[SHA256_DIGEST_SIZE]
)
{
	int				i;
	t_hmac_params	hmac_params;
	t_byte			*salt_plus_iteration;

	salt_plus_iteration = (t_byte *)malloc(4 + params.salt_len);
	ft_memcpy(salt_plus_iteration, params.salt, params.salt_len);
	big_endian_words_to_bytes((uint32_t *)&block_index,
		salt_plus_iteration + params.salt_len, 4);
	ft_memcpy(salt_plus_iteration + params.salt_len, &block_index, 4);
	hmac_params.key = params.pass;
	hmac_params.key_len = params.pass_len;
	hmac_params.text = salt_plus_iteration;
	hmac_params.text_len = params.salt_len + 4;
	hmac_sha256(hmac_params, buffer);
	free(salt_plus_iteration);
	i = 0;
	hmac_params.text = buffer;
	hmac_params.text_len = SHA256_DIGEST_SIZE;
	while (++i < block_index)
		hmac_sha256(hmac_params, buffer);
}

int			pbkfd2_hmac_sha256(t_pbkdf2_params params)
{
	int		l;
	int		r;
	int		i;
	t_byte	temp[SHA256_DIGEST_SIZE];

	l = params.dk_len / SHA256_DIGEST_SIZE;
	r = params.dk_len % SHA256_DIGEST_SIZE;
	l = r ? l + 1 : l;
	i = 0;
	while (i < l - 1)
	{
		f(params, i, temp);
		ft_memcpy(params.dk + i * SHA256_DIGEST_SIZE, temp, SHA256_DIGEST_SIZE);
		i++;
	}
	f(params, i, temp);
	ft_memcpy(params.dk + i * SHA256_DIGEST_SIZE, temp, r);
	return (0);
}
