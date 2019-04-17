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

static void	encode(t_des_options *options)
{
	if (options->base64)
		initialize_base64_write_pipe(options);
	if (options->password_present == TRUE)
	{
		derive_from_password(options);
		if (options->print_ksi == TRUE)
			des_print_ksi(options);
		des_write_salt(options->salt, DES_SALT_LENGTH, options->output_file);
	}
	else if (options->print_ksi == TRUE)
		des_print_ksi(options);
	des_cbc_encode(options->key, options->initial_vector, options->input_file, options->output_file);
}

static void	decode(t_des_options *options)
{
	if (options->base64)
		initialize_base64_read_pipe(options);
	if (options->password_present == TRUE)
	{
		des_read_salt(options->salt, options->input_file);
		options->salt_present = TRUE;
		derive_from_password(options);
	}
	if (options->print_ksi == TRUE)
		des_print_ksi(options);
	des_cbc_decode(options->key, options->initial_vector, options->input_file, options->output_file);
}

void		des_cbc_handler(t_ssl *ssl)
{
	t_des_options		options;

	des_set_default_options(&options);
	des_parse_options(&options, ssl->argc, ssl->argv);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if ((options.key_present == TRUE && options.initial_vector_present == FALSE) ||
		(options.key_present == FALSE && options.initial_vector_present == TRUE))
		ssl_error("In CBC-mode key and iv must be presented\n");
	if (options.password_present == FALSE && options.key_present == FALSE)
		des_get_password_from_stdin(&options);
	if (options.encode)
		encode(&options);
	else
		decode(&options);
}

