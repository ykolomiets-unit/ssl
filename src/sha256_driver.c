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

void	sha224_string
(
	char *string,
	t_byte digest[28]
)
{
	t_sha224_ctx	ctx;

	sha224_init(&ctx);
	sha224_update(&ctx, (t_byte *)string, ft_strlen(string));
	sha224_final(&ctx, digest);
}
