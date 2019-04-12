#include "ft_ssl.h"
#include "des.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef	int	(*t_option_parser)(int pos, int argc, char **argv, t_des_options *options);

typedef struct		s_option_handler
{
	char			*option;
	t_option_parser	handler;
}					t_option_handler;

static int	decode_option_handler(int pos, int argc, char **argv, t_des_options *options)
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

static int	encode_option_handler(int pos, int argc, char **argv, t_des_options *options)
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

static int	base64_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	(void)pos;
	(void)argc;
	(void)argv;
	options->base64 = TRUE;
	return (1);
}

static int	input_option_handler(int pos, int argc, char **argv, t_des_options *options)
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

static int	output_option_handler(int pos, int argc, char **argv, t_des_options *options)
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

static t_byte	get_4bits_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <='f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <='F')
		return (c - 'A' + 10);    
	return (0xff);
}

static int	parse_hex(char *str, t_byte res[8])
{
	uint32_t	i;
	t_byte		temp;

	i = 0;
	ft_bzero(res, 8);
	while (*str && i < 16)
	{
		temp = get_4bits_value(*str);
		if (temp == 0xff)
			return (-1);
		res[i / 2] |= temp << ((i + 1) % 2) * 4;
		i++;
		str++;
	}
	if (*str)
		return (-2);
	if (i < 16)
		return (1);
	return (0);
}

static int	key_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No key after -k\n");
		return (-1);
	}
	if (options->password)
	{
		ft_dprintf(2, "Use either password or key/iv\n");
		return (-1);
	}
	options->key_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->key);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse key\n");
	else if (parse_res == -2)
		ft_dprintf(2, "Key is too long\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Key was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}

static int	salt_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No salt after -s\n");
		return (-1);
	}
	options->salt_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->salt);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse salt\n");
	else if (parse_res == -2)
		ft_dprintf(2, "Salt is too long\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Salt was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}

static int	iv_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	int	parse_res;

	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No initial vector after -v\n");
		return (-1);
	}
	if (options->password)
	{
		ft_dprintf(2, "Use either password or key/iv\n");
		return (-1);
	}
	options->initial_vector_present = TRUE;
	parse_res = parse_hex(argv[pos + 1], options->initial_vector);
	if (parse_res == -1)
		ft_dprintf(2, "Cannot parse initial vector\n");
	else if (parse_res == -2)
		ft_dprintf(2, "Initial vector is too long\n");
	else if (parse_res == 1)
		ft_dprintf(2, "Initial vector was filled with 0 in the end\n");
	if (parse_res < 0)
		return (-1);
	return (2);
}

static int	password_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	if (pos + 1 >= argc)
	{
		ft_dprintf(2, "No password after -p\n");
		return (-1);
	}

	if (options->key_present || options->initial_vector_present)
	{
		ft_dprintf(2, "Use either key/iv or password\n");
		return (-1);
	}
	options->password = argv[pos + 1];
	return (2);
}

static int	pbkdf2_option_handler(int pos, int argc, char **argv, t_des_options *options)
{
	(void)pos;
	(void)argc;
	(void)argv;
	options->use_pbkdf2 = TRUE;
	return (1);
}


static t_option_handler	g_option_handlers[] = {
	{ "-d", decode_option_handler	},
	{ "-e", encode_option_handler	},
	{ "-a", base64_option_handler	},
	{ "-i", input_option_handler	},
	{ "-o", output_option_handler	},
	{ "-k", key_option_handler		},
	{ "-s", salt_option_handler		},
	{ "-v", iv_option_handler		},
	{ "-p", password_option_handler	},
	{ "--pbkdf2", pbkdf2_option_handler	},
	{ NULL, NULL}
};

static void	des_parse_options(t_des_options *options, int argc, char **argv)
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
		if (option_handler->option == NULL)
		{
			ft_dprintf(2, "Unknown option\n");
			exit(-1);
		}
	}
}

static void	set_default_options(t_des_options *options)
{
	options->base64 = FALSE;
	options->decode = FALSE;
	options->encode = FALSE;
	options->initial_vector_present = FALSE;
	options->key_present = FALSE;
	options->salt_present = FALSE;
	options->input_file = 0;
	options->output_file = 1;
	options->password = NULL;
	options->use_pbkdf2 = FALSE;
}

static void	derive_from_password(t_des_options *options)
{
	t_pbkdf_params	params;

	params.use_pbkdf2 = options->use_pbkdf2;
	params.salt = options->salt;
	params.key = options->key;
	params.iv = options->initial_vector;
	params.generate_salt = !options->salt_present;
	params.password = options->password;
	if (des_derive_key_from_password(&params))
	{
		ft_dprintf(2, "Error while generating salt, key and iv from password\n");
		exit(-1);
	}
}

void		des_ecb_handler(t_ssl *ssl)
{
	t_des_options		options;

	set_default_options(&options);
	des_parse_options(&options, ssl->argc, ssl->argv);
	if (options.key_present == FALSE)
		derive_from_password(&options);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if (options.encode)
		des_ecb_encode(options.key, options.input_file, options.output_file);
	else
		des_ecb_decode(options.key, options.input_file, options.output_file);
}

