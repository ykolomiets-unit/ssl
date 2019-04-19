/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_options3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:39:07 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 17:58:07 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_options.h"
#include "libft.h"

static t_byte	get_4bits_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0xff);
}

static int		parse_hex(char *str, t_byte *res, uint32_t res_size)
{
	uint32_t	i;
	t_byte		temp;

	i = 0;
	ft_bzero(res, res_size);
	while (*str && i < res_size * 2)
	{
		temp = get_4bits_value(*str);
		if (temp == 0xff)
			return (-1);
		res[i / 2] |= temp << ((i + 1) % 2) * 4;
		i++;
		str++;
	}
	if (*str)
		return (2);
	if (i < res_size * 2)
		return (1);
	return (0);
}

int				des_key_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No key after -k\n");
		return (-1);
	}
	if (options->password_present)
	{
		ft_dprintf(2, "Use either password or key/iv\n");
		return (-1);
	}
	options->key_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->key, 3 * DES_KEY_LENGTH);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse key\n");
	else if (parse_res == 2)
		ft_dprintf(2, "Key is too long, remainder truncated\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Key was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}

int				des_salt_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No salt after -s\n");
		return (-1);
	}
	options->salt_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->salt, DES_SALT_LENGTH);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse salt\n");
	else if (parse_res == 2)
		ft_dprintf(2, "Salt is too long, remainder truncated\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Salt was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}

int				des_iv_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No initial vector after -v\n");
		return (-1);
	}
	if (options->password_present)
	{
		ft_dprintf(2, "Use either password or key/iv\n");
		return (-1);
	}
	options->initial_vector_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->initial_vector,
							DES_IV_LENGTH);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse initial vector\n");
	else if (parse_res == -2)
		ft_dprintf(2, "Initial vector is too long, remainder truncated\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Initial vector was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}
