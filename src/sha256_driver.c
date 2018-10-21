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

#include "sha224_256.h"
#include "libft.h"
#include <unistd.h>

void	sha256_string
(
	char *string,
	t_byte digest[32]
)
{
	t_sha256_ctx	ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, (t_byte *)string, ft_strlen(string));
	sha256_final(&ctx, digest);
}

void	sha256_file
(
	int fd,
	t_byte digest[32]
)
{
	t_sha256_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha256_init(&ctx);
	while ((r = read(fd, buffer, 1024)) > 0)
		sha256_update(&ctx, buffer, r);
	sha256_final(&ctx, digest);
}

void	sha256_filter
(
	t_byte digest[32],
	int echo
)
{
	t_sha256_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha256_init(&ctx);
	while ((r = read(0, buffer, 1024)) > 0)
	{
		if (echo)
			write(1, buffer, r);
		sha256_update(&ctx, buffer, r);
	}
	if (echo)
		write(1, "\n", 1);
	sha256_final(&ctx, digest);
}