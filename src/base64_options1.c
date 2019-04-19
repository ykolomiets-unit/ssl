/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_options1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:46:59 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 18:57:57 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_options.h"
#include "libft.h"
#include "ssl_error.h"
#include <stdlib.h>

int							b64_help_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_base64_options *options
)
{
	(void)pos;
	(void)argc;
	(void)argv;
	(void)options;
	ft_printf("-i FILE_NAME : input file\n");
	ft_printf("-o FILE_NAME : output file\n");
	ft_printf("-e : encode\n");
	ft_printf("-d : decode\n");
	ft_printf("-b NUMBER : break at each n-th byte\n");
	ft_printf("--help: this help =)\n");
	exit(0);
	return (0);
}

static t_b64_option_handler	g_option_handlers[] = {
	{ "-d", b64_decode_option_handler	},
	{ "-e", b64_encode_option_handler	},
	{ "-i", b64_input_option_handler	},
	{ "-o", b64_output_option_handler	},
	{ "-b", b64_break_option_handler	},
	{ "--help", b64_help_option_handler	},
	{ NULL, NULL}
};

static t_b64_optparser		select_option(const char *str)
{
	t_b64_option_handler	*opt;

	opt = g_option_handlers;
	while (opt->option != NULL)
	{
		if (ft_strcmp(opt->option, str) == 0)
			return (opt->handler);
		opt++;
	}
	return (NULL);
}

void						base64_parse_options
(
	t_base64_options *options,
	int argc,
	char **argv
)
{
	int						i;
	int						r;
	t_b64_optparser			opt;

	i = 0;
	while (i < argc)
	{
		opt = select_option(argv[i]);
		if (opt != NULL)
		{
			if ((r = opt(i, argc, argv, options)) < 0)
				exit(r);
			i += r;
		}
		else
		{
			if (options->input_file == 0 &&
				(r = b64_input_option_handler(i - 1, argc, argv, options)) < 0)
				exit(r);
			break ;
		}
	}
}
