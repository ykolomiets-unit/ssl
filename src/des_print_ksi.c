/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_print_ksi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:11 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:41:13 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"

static void	print_hex(t_byte *bytes, uint32_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%2.2x", bytes[i]);
		i++;
	}
}

void		des_print_ksi(t_des_options *options)
{
	if (options->password_present)
	{
		ft_printf("salt =\t");
		print_hex(options->salt, DES_SALT_LENGTH);
	}
	ft_printf("\nkey =\t");
	if (options->des3)
		print_hex(options->key, 3 * DES_KEY_LENGTH);
	else
		print_hex(options->key, DES_KEY_LENGTH);
	if (options->mode != DES_MODE_ECB)
	{
		ft_printf("\niv =\t");
		print_hex(options->initial_vector, DES_IV_LENGTH);
	}
	ft_printf("\n");
}
