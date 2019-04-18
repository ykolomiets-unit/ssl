#include "des_options.h"
#include "libft.h"
#include <stdlib.h>

static t_des_option_handler	g_option_handlers[] = {
	{ "-d", des_decode_option_handler },
	{ "-e", des_encode_option_handler },
	{ "-a", des_base64_option_handler },
	{ "-i", des_input_option_handler },
	{ "-o", des_output_option_handler },
	{ "-k", des_key_option_handler },
	{ "-s", des_salt_option_handler },
	{ "-v", des_iv_option_handler },
	{ "-p", des_password_option_handler },
	{ "--pbkdf2", des_pbkdf2_option_handler },
	{ "--help", des_help_option_handler },
	{ "--print", des_print_ksi_option_handler },
	{ NULL, NULL}
};

void						des_set_default_options(t_des_options *options)
{
	ft_bzero(options, sizeof(t_des_options));
	options->output_file = 1;
}

void						des_parse_options
(
	t_des_options *options,
	int argc,
	char **argv
)
{
	int						i;
	t_des_option_handler	*option_handler;
	int						parse_res;
	
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
		if (option_handler->option == NULL)
		{
			ft_dprintf(2, "Unknown option\n");
			exit(-1);
		}
	}
}
