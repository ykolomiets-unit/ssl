#include "des.h"
#include "des_options.h"
#include "libft.h"
#include "ft_ssl.h"
#include "ssl_error.h"
#include <stdlib.h>
#include <unistd.h>

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
		ft_dprintf(2, "Error while generating salt, key or iv from password\n");
		exit(-1);
	}
	options->salt_present = TRUE;
}

static void	encode(t_des_options *options, t_des_chainmode mode)
{
	t_des_chain_params	params;

	if (options->base64)
		initialize_base64_write_pipe(options);
	if (options->key_present == FALSE)
	{
		derive_from_password(options);
		if (options->print_ksi == TRUE)
			des_print_ksi(options);
		des_write_salt(options->salt, DES_SALT_LENGTH, options->output_file);
	}
	else if (options->print_ksi == TRUE)
		des_print_ksi(options);
	params.key = options->key;
	params.iv = options->initial_vector;
	params.in = options->input_file;
	params.out = options->output_file;
	params.encode = TRUE;
	params.mode = mode;
	des_chain(&params);
}

static void	decode(t_des_options *options, t_des_chainmode mode)
{
	t_des_chain_params	params;

	if (options->base64)
		initialize_base64_read_pipe(options);
	if (options->key_present == FALSE)
	{
		des_read_salt(options->salt, options->input_file);
		options->salt_present = TRUE;
		derive_from_password(options);
	}
	if (options->print_ksi == TRUE)
		des_print_ksi(options);
	params.key = options->key;
	params.iv = options->initial_vector;
	params.in = options->input_file;
	params.out = options->output_file;
	params.encode = FALSE;
	params.mode = mode;
	des_chain(&params);
}

void		des_handler(int argc, char **argv, t_des_chainmode mode)
{
	t_des_options	options;

	des_set_default_options(&options);
	des_parse_options(&options, argc, argv);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if (mode != DES_MODE_ECB &&
		(
			(options.key_present && !options.initial_vector_present) ||
			(!options.key_present && options.initial_vector_present)
		))
	{
		ft_dprintf(2, "In %s-mode key and iv must be presented\n", g_mode_name[mode]);
		exit(-1);
	}
	if (options.password_present == FALSE && options.key_present == FALSE)
		des_get_password_from_stdin(&options);
	if (options.encode)
		encode(&options, mode);
	else
		decode(&options, mode);
}
