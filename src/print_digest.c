/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:52:27 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/21 20:52:29 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	print_digest(t_byte *digest, int digest_size)
{
	int	i;

	i = 0;
	while (i < digest_size)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}
