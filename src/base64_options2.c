/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_options2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:45:33 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:45:34 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_options.h"
#include "libft.h"
#include <fcntl.h>

int	b64_decode_option_handler(int pos, int argc, char **argv,
								t_base64_options *options)
{
	(void)pos;
	(void)argc;
	(void)argv;
	if (options->encode == TRUE)
	{
		ft_dprintf(2, "Select either decode (-d) or encode (-e) option\n");
		return (-1);
	}
	options->decode = TRUE;
	return (1);
}

int	b64_encode_option_handler(int pos, int argc, char **argv,
								t_base64_options *options)
{
	(void)pos;
	(void)argc;
	(void)argv;
	if (options->decode == TRUE)
	{
		ft_dprintf(2, "Select either decode (-d) or encode (-e) option\n");
		return (-1);
	}
	options->encode = TRUE;
	return (1);
}

int	b64_input_option_handler(int pos, int argc, char **argv,
								t_base64_options *options)
{
	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No filename after -i\n");
		return (-1);
	}
	options->input_file = open(argv[pos + 1], O_RDONLY);
	if (options->input_file < 0)
	{
		ft_dprintf(2, "Unable to open '%s': ", argv[pos + 1]);
		return (-1);
	}
	return (2);
}

int	b64_output_option_handler(int pos, int argc, char **argv,
								t_base64_options *options)
{
	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No filename after -o\n");
		return (-1);
	}
	options->output_file = open(argv[pos + 1],
									O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (options->output_file < 0)
	{
		ft_dprintf(2, "Unable to create '%s': ", argv[pos + 1]);
		return (-1);
	}
	return (2);
}

int	b64_break_option_handler(int pos, int argc, char **argv,
								t_base64_options *options)
{
	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No break num after -b\n");
		return (-1);
	}
	options->break_num = ft_atoi(argv[pos + 1]);
	if (options->break_num <= 0 || options->break_num > 1000)
	{
		ft_dprintf(2, "Break num must be in range [1, 1000]\n");
		return (-1);
	}
	return (2);
}
