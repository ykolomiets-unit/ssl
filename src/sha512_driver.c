/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_driver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:21:55 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:21:57 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384_512.h"
#include "libft.h"
#include <unistd.h>

void	sha512_string
(
	char *string,
	t_byte digest[64]
)
{
	t_sha512_ctx	ctx;

	sha512_init(&ctx);
	sha512_update(&ctx, (t_byte *)string, ft_strlen(string));
	sha512_final(&ctx, digest);
}

void	sha512_file
(
	int fd,
	t_byte digest[64]
)
{
	t_sha512_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha512_init(&ctx);
	while ((r = read(fd, buffer, 1024)) > 0)
		sha512_update(&ctx, buffer, r);
	sha512_final(&ctx, digest);
}

void	sha512_filter
(
	t_byte digest[64],
	int echo
)
{
	t_sha512_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha512_init(&ctx);
	while ((r = read(0, buffer, 1024)) > 0)
	{
		if (echo)
			write(1, buffer, r);
		sha512_update(&ctx, buffer, r);
	}
	sha512_final(&ctx, digest);
}
