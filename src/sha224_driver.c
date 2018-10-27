/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_driver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:20:27 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/21 20:20:29 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_256.h"
#include "libft.h"
#include <unistd.h>

void	sha224_string
(
	char *string,
	t_byte digest[SHA224_DIGEST_SIZE]
)
{
	t_sha224_ctx	ctx;

	sha224_init(&ctx);
	sha224_update(&ctx, (t_byte *)string, ft_strlen(string));
	sha224_final(&ctx, digest);
}

void	sha224_file
(
	int fd,
	t_byte digest[SHA224_DIGEST_SIZE]
)
{
	t_sha224_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha224_init(&ctx);
	while ((r = read(fd, buffer, 1024)) > 0)
		sha224_update(&ctx, buffer, r);
	sha224_final(&ctx, digest);
}

void	sha224_filter
(
	t_byte digest[SHA224_DIGEST_SIZE],
	int echo
)
{
	t_sha224_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha224_init(&ctx);
	while ((r = read(0, buffer, 1024)) > 0)
	{
		if (echo)
			write(1, buffer, r);
		sha224_update(&ctx, buffer, r);
	}
	sha224_final(&ctx, digest);
}
