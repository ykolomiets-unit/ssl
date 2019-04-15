/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:26:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/26 16:41:27 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

typedef	int	(*t_option_parser)(int pos, int argc, char **argv, t_base64_options *options);

typedef struct		s_option_handler
{
	char			*option;
	t_option_parser	handler;
}					t_option_handler;

static int	decode_option_handler(int pos, int argc, char **argv, t_base64_options *options)
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

static int	encode_option_handler(int pos, int argc, char **argv, t_base64_options *options)
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

static int	input_option_handler(int pos, int argc, char **argv, t_base64_options *options)
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

static int	output_option_handler(int pos, int argc, char **argv, t_base64_options *options)
{
	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No filename after -o\n");
		return (-1);
	}
	options->output_file = open(argv[pos + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (options->output_file < 0)
	{
		ft_dprintf(2, "Unable to create '%s': ", argv[pos + 1]);
		return (-1);
	}
	return (2);
}

static int	break_option_handler(int pos, int argc, char **argv, t_base64_options *options)
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

static t_option_handler	g_option_handlers[] = {
	{ "-d", decode_option_handler	},
	{ "-e", encode_option_handler	},
	{ "-i", input_option_handler	},
	{ "-o", output_option_handler	},
	{ "-b", break_option_handler	},
	//TODO help
	{ NULL, NULL}
};

static void	base64_parse_options(t_base64_options *options, int argc, char **argv)
{
	int					i;
	t_option_handler	*option_handler;
	int					parse_res;
	
	i = 0;
	while (i < argc)
	{
		option_handler = g_option_handlers;
		while (option_handler->option != NULL)
			if (ft_strcmp(option_handler->option, argv[i]) == 0)
			{
				parse_res = option_handler->handler(i, argc, argv, options);
				if (parse_res < 0)
					exit(parse_res);
				i += parse_res;
				break;
			}
			else
				option_handler++;
		//TODO: check if this is input file (./ft_ssl base64 Makefile)
		if (option_handler->option == NULL)
		{
			ft_dprintf(2, "Unknown option\n");
			exit(-1);
		}
	}
}

static void	set_default_options(t_base64_options *options)
{
	options->break_num = 0;
	options->decode = FALSE;
	options->encode = FALSE;
	options->input_file = 0;
	options->output_file = 1;
}

void		base64_handler(t_ssl *ssl)
{
	t_base64_options	options;

	set_default_options(&options);
	base64_parse_options(&options, ssl->argc, ssl->argv);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if (options.encode == TRUE)
		base64_encode_file_to_file(options.input_file, options.output_file, options.break_num);
	else
		base64_decode_file_to_file(options.input_file, options.output_file);
}
