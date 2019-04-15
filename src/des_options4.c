#include "des_options.h"
#include "libft.h"
#include <stdlib.h>

int	password_option_handler
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

int	pbkdf2_option_handler
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

int	help_option_handler
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
	ft_printf("Help!!!!!!!!!\n");
	exit(0);
	return (0);
}
