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

void						base64_parse_options
(
	t_base64_options *options,
	int argc,
	char **argv
)
{
	int						i;
	t_b64_option_handler	*option_handler;
	int						parse_res;
	
	i = 0;
	while (i < argc)
	{
		option_handler = g_option_handlers;
		while (option_handler->option != NULL)
			if (ft_strcmp(option_handler->option, argv[i]) == 0)
			{
				if ((parse_res = option_handler->handler(i, argc, argv, options)) < 0)
					exit(parse_res);
				i += parse_res;
				break;
			}
			else
				option_handler++;
		if (option_handler->option == NULL)
		{
			if ((parse_res = b64_input_option_handler(i - 1, argc, argv, options)) < 0)
				exit(parse_res);
			break;
		}
	}
}
