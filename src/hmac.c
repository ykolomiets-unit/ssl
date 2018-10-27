/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:21:26 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/27 18:22:13 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmac.h"
#include "libft.h"

static void	hmac_init
(
	t_hmac_help help,
	t_hmac_params *params
)
{
	uint32_t	i;

	if (params->key_len > help.block_size)
	{
		help.init(help.ctx);
		help.update(help.ctx, params->key, params->key_len);
		help.final(help.ctx, help.newkey);
		params->key = help.newkey;
		params->key_len = help.digest_size;
	}
	ft_bzero(help.ipad, help.block_size);
	ft_bzero(help.opad, help.block_size);
	ft_memcpy(help.ipad, params->key, params->key_len);
	ft_memcpy(help.opad, params->key, params->key_len);
	i = 0;
	while (i < help.block_size)
	{
		help.ipad[i] ^= 0x36;
		help.opad[i] ^= 0x5c;
		i++;
	}
}

static void	hmac_core
(
	t_hmac_help help,
	t_hmac_params params,
	t_byte *digest
)
{
	hmac_init(help, &params);
	help.init(help.ctx);
	help.update(help.ctx, help.ipad, help.block_size);
	help.update(help.ctx, params.text, params.text_len);
	help.final(help.ctx, digest);
	help.init(help.ctx);
	help.update(help.ctx, help.opad, help.block_size);
	help.update(help.ctx, digest, help.digest_size);
	help.final(help.ctx, digest);
}

void		hmac_md5(t_hmac_params params, t_byte digest[MD5_DIGEST_SIZE])
{
	t_hmac_help		help;
	t_md5_ctx		ctx;
	t_byte			ipad[MD5_BLOCK_SIZE];
	t_byte			opad[MD5_BLOCK_SIZE];
	t_byte			newkey[MD5_DIGEST_SIZE];

	help.ctx = &ctx;
	help.block_size = MD5_BLOCK_SIZE;
	help.digest_size = MD5_DIGEST_SIZE;
	help.init = (t_hash_init)md5_init;
	help.update = (t_hash_update)md5_update;
	help.final = (t_hash_final)md5_final;
	help.ipad = ipad;
	help.opad = opad;
	help.newkey = newkey;
	hmac_core(help, params, digest);
}

void		hmac_sha256(t_hmac_params params, t_byte digest[SHA256_DIGEST_SIZE])
{
	t_hmac_help		help;
	t_sha256_ctx	ctx;
	t_byte			ipad[SHA256_BLOCK_SIZE];
	t_byte			opad[SHA256_BLOCK_SIZE];
	t_byte			newkey[SHA256_DIGEST_SIZE];

	help.ctx = &ctx;
	help.block_size = SHA256_BLOCK_SIZE;
	help.digest_size = SHA224_DIGEST_SIZE;
	help.init = (t_hash_init)sha256_init;
	help.update = (t_hash_update)sha256_update;
	help.final = (t_hash_final)sha256_final;
	help.ipad = ipad;
	help.opad = opad;
	help.newkey = newkey;
	hmac_core(help, params, digest);
}
