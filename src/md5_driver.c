/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:33:33 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:35:00 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"
#include <unistd.h>

void	md5_string
(
	char *string,
	t_byte digest[MD5_DIGEST_SIZE]
)
{
	t_md5_ctx	ctx;

	md5_init(&ctx);
	md5_update(&ctx, (t_byte *)string, ft_strlen(string));
	md5_final(&ctx, digest);
}

void	md5_file
(
	int fd,
	t_byte digest[MD5_DIGEST_SIZE]
)
{
	t_md5_ctx	ctx;
	t_byte		buffer[1024];
	int			r;

	md5_init(&ctx);
	while ((r = read(fd, buffer, 1024)) > 0)
		md5_update(&ctx, buffer, r);
	md5_final(&ctx, digest);
}

void	md5_filter
(
	t_byte digest[MD5_DIGEST_SIZE],
	int echo
)
{
	t_md5_ctx	ctx;
	t_byte		buffer[1024];
	int			r;

	md5_init(&ctx);
	while ((r = read(0, buffer, 1024)) > 0)
	{
		if (echo)
			write(1, buffer, r);
		md5_update(&ctx, buffer, r);
	}
	md5_final(&ctx, digest);
}
