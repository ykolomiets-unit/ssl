#include "des_options.h"
#include "libft.h"
#include <stdlib.h>

static t_des_option_handler	g_option_handlers[] = {
	{ "-d", decode_option_handler },
	{ "-e", encode_option_handler },
	{ "-a", base64_option_handler },
	{ "-i", input_option_handler },
	{ "-o", output_option_handler },
	{ "-k", key_option_handler },
	{ "-s", salt_option_handler },
	{ "-v", iv_option_handler },
	{ "-p", password_option_handler },
	{ "--pbkdf2", pbkdf2_option_handler },
	{ "--help", help_option_handler },
	{ NULL, NULL}
};

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
