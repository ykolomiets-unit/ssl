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

void	md5_string
(
	char *string,
	unsigned char digest[16]
)
{
	t_md5_context	context;

	md5_init(&context);
	md5_update(&context, string, ft_strlen(string));
	md5_final(&context, digest);
}
