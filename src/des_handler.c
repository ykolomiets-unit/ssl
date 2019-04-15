#include "ft_ssl.h"
#include "des.h"
#include "des_options.h"
#include "base64.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	options->password_present = FALSE;
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
	options->salt_present = TRUE;
}

static void	read_salt_from_file(t_byte salt[DES_SALT_LENGTH], int fd)
{
	t_byte	buffer[16];
	int		r;
	int		in_buf;

	in_buf = 0;	
	while ((r = read(fd, buffer + in_buf, 16 - in_buf)) > 0)
		in_buf += r;
	if (r < 0 || in_buf < 16)
	{
		ft_dprintf(2, "Error reading input file\n");
		exit(-1);
	}
	if (ft_strncmp((const char *)buffer, "Salted__", 8) != 0)
	{
		ft_dprintf(2, "Bad magic number");
		exit(-1);
	}
	ft_memcpy(salt, buffer + 8, DES_SALT_LENGTH);
}

void		initialize_base64_write_pipe(t_des_options *options)
{
	int		fd[2];
	pid_t	p;

	if(pipe(fd) == -1)
	{
		ft_dprintf(2, "Pipe failed\n");
		exit(-1);
	}
	p = fork();
	if (p < 0)
	{
		ft_dprintf(2, "Fork failed\n");
		exit(-1);
	}
	if (p > 0)
	{
		close(fd[0]);
		options->output_file = fd[1];
	}
	else
	{
		close(fd[1]);
		base64_encode_file_to_file(fd[0], options->output_file, 64);
		exit(0);
	}
}

void		initialize_base64_read_pipe(t_des_options *options)
{
	int		fd[2];
	pid_t	p;

	if (pipe(fd) == -1)
	{
		ft_dprintf(2, "Pipe failed\n");
		exit(-1);
	}
	p = fork();
	if (p < 0)
	{
		ft_dprintf(2, "Fork failed\n");
		exit(-1);
	}
	if (p > 0)
	{
		close(fd[1]);
		options->input_file = fd[0];
	}
	else
	{
		close(fd[0]);
		base64_decode_file_to_file(options->input_file, fd[1]);
		return;
	}
}

void		get_password_from_stdin(t_des_options *options)
{
	char	*password;

	password = getpass("Enter encryption password: ");
	if (password == NULL)
	{
		ft_dprintf(2, "Something went wrong!\n");
		exit(-1);
	}
	if (ft_strlen(password) > 1023)
	{
		ft_dprintf(2, "Password is too long\n");
		exit(-1);
	}
	ft_strcpy(options->password, password);
	password = getpass("Repeat encryption password: ");
	if (password == NULL)
	{
		ft_dprintf(2, "Something went wrong!\n");
		exit(-1);
	}
	if (ft_strcmp(options->password, password) != 0)
	{
		ft_dprintf(2, "Password verifing failed\n");
		exit(-1);
	}
	options->password_present = TRUE;
}

void		des_ecb_handler(t_ssl *ssl)
{
	t_des_options		options;

	set_default_options(&options);
	des_parse_options(&options, ssl->argc, ssl->argv);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if (options.password_present == FALSE && options.key_present == FALSE)
		get_password_from_stdin(&options);
	if (options.encode)
	{
		if (options.key_present == FALSE)
			derive_from_password(&options);
		if (options.base64)
			initialize_base64_write_pipe(&options);
		if (options.salt_present)
		{
			write(options.output_file, "Salted__", ft_strlen("Salted__"));
			write(options.output_file, options.salt, DES_SALT_LENGTH);
		}
		des_ecb_encode(options.key, options.input_file, options.output_file);
	}
	else
	{
		if (options.base64)
			initialize_base64_read_pipe(&options);
		if (options.key_present == FALSE)
		{
			read_salt_from_file(options.salt, options.input_file);
			options.salt_present = TRUE;
			derive_from_password(&options);
		}
		des_ecb_decode(options.key, options.input_file, options.output_file);
	}
}

