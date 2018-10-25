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

void	sha384_string
(
	char *string,
	t_byte digest[48]
)
{
	t_sha384_ctx	ctx;

	sha384_init(&ctx);
	sha384_update(&ctx, (t_byte *)string, ft_strlen(string));
	sha384_final(&ctx, digest);
}

void	sha384_file
(
	int fd,
	t_byte digest[48]
)
{
	t_sha384_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha384_init(&ctx);
	while ((r = read(fd, buffer, 1024)) > 0)
		sha384_update(&ctx, buffer, r);
	sha384_final(&ctx, digest);
}

void	sha384_filter
(
	t_byte digest[48],
	int echo
)
{
	t_sha384_ctx	ctx;
	t_byte			buffer[1024];
	int				r;

	sha384_init(&ctx);
	while ((r = read(0, buffer, 1024)) > 0)
	{
		if (echo)
			write(1, buffer, r);
		sha384_update(&ctx, buffer, r);
	}
	sha384_final(&ctx, digest);
}
