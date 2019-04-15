#include "des_options.h"
#include "libft.h"
#include <stdlib.h>

int	des_password_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
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
	if (ft_strlen(argv[pos + 1]) > 1023)
	{
		ft_dprintf(2, "Password is too long\n");
		return (-1);
	}
	ft_strcpy(options->password, argv[pos + 1]);
	options->password_present = TRUE;
	return (2);
}

int	des_pbkdf2_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
{
	(void)pos;
	(void)argc;
	(void)argv;
	options->use_pbkdf2 = TRUE;
	return (1);
}

int des_print_ksi_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
)
{
	(void)pos;
	(void)argc;
	(void)argv;
	options->print_ksi = TRUE;
	return (1);
}

int	des_help_option_handler
(
	int pos,
	int argc,
	char **argv,
	t_des_options *options
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
	ft_printf("-p STRING : password\n");
	ft_printf("-a : perform base64 encoding/decoding\n");
	ft_printf("-k HEX_STRING : key in hex (ex. 0123abcd)\n");
	ft_printf("-s HEX_STRING : salt in hex (ex. 0123abcd)\n");
	ft_printf("-i HEX_STRING : initial_vector in hex (ex. 0123abcd)\n");
	ft_printf("--pbkdf2 : use pbkdf2 (HMAC-SHA256 with 4096 iterations)\n");
	ft_printf("--print: print used key, salt and iv\n");
	ft_printf("--help: this help =)\n");
	exit(0);
	return (0);
}
