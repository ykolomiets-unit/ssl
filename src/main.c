/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:52:43 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/21 20:52:44 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "md5.h"
#include "sha224_256.h"
#include "base64.h"
#include "ft_ssl.h"
#include <fcntl.h>

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"
#define STANDARD_COMMANDS "Standard commands: "
#define DIGEST_COMMANDS "Message Digest commands: "
#define CIPHER_COMMANDS "Cipher commands: "

#define DIGEST_COMMANDS_AMOUNT 3
#define CIPHER_COMMANDS_AMOUNT 1

static void	md5_handler(int argc, char **argv)
{
	t_digest_help	help;

	help.algorithm_name = "MD5";
	help.digest_size = 16;
	help.digest_of_string = md5_string;
	help.digest_of_file = md5_file;
	help.digest_of_stdin = md5_filter;
	help.something_processed = FALSE;
	process_digest(argc, argv, help);
}

static void	sha224_handler(int argc, char **argv)
{
	t_digest_help	help;

	help.algorithm_name = "SHA224";
	help.digest_size = 28;
	help.digest_of_string = sha224_string;
	help.digest_of_file = sha224_file;
	help.digest_of_stdin = sha224_filter;
	help.something_processed = FALSE;
	process_digest(argc, argv, help);
}

static void	sha256_handler(int argc, char **argv)
{
	t_digest_help	help;

	help.algorithm_name = "SHA256";
	help.digest_size = 32;
	help.digest_of_string = sha256_string;
	help.digest_of_file = sha256_file;
	help.digest_of_stdin = sha256_filter;
	help.something_processed = FALSE;
	process_digest(argc, argv, help);
}

typedef struct	s_base64_options
{
	t_bool		encode;
	t_bool		decode;
	char		*input_file;
	char		*output_file;
}				t_base64_options;

static void	base64_parse_options(t_base64_options *options, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < argc)
		if (ft_strcmp(argv[i], "-d") == 0)
			options->decode = TRUE;
		else if (ft_strcmp(argv[i], "-e") == 0)
			options->encode = TRUE;
		else if (ft_strcmp(argv[i], "-i") == 0)
		{
			if (++i >= argc)
				error("No filename after -i");
			options->input_file = argv[i];
		}
		else if (ft_strcmp(argv[i], "-o") == 0)
		{
			if (++i >= argc)
				error("No filename after -o");
			options->output_file = argv[i];
		}
		else if (ft_strcmp(argv[i], "--") == 0 && i++)
			break ;
		else
			break ;
	if (i < argc)
		options->input_file = argv[i];
}

static void	base64_handler(int argc, char **argv)
{
	t_base64_options	options;
	int					in;
	int					out;

	ft_bzero(&options, sizeof(options));
	base64_parse_options(&options, argc, argv);
	if (options.input_file == NULL)
		in = 0;
	else
		in = open(options.input_file, O_RDONLY);
	if (options.output_file == NULL)
		out = 1;
	else
		out = open(options.output_file, O_WRONLY | O_CREAT, 0644);
	if (!options.decode)
		base64_encode_file_to_file(in, out);
}

static t_handler	get_command_handler
(
	char *command_name,
	t_command_handler digest_commands[],
	t_command_handler cipher_commands[]
)
{
	int							i;

	i = -1;
	while (++i < DIGEST_COMMANDS_AMOUNT)
		if (ft_strcmp(command_name, digest_commands[i].command) == 0)
			return (digest_commands[i].handler);
	i = -1;
	while (++i < CIPHER_COMMANDS_AMOUNT)
		if (ft_strcmp(command_name, cipher_commands[i].command) == 0)
			return (cipher_commands[i].handler);
	return (NULL);
}

static void	print_commands
(
	char *invalid_command,
	t_command_handler digest_commands[],
	t_command_handler cipher_commands[]
)
{
	int	i;

	ft_printf("ft_ssl: Error: '%s' is an invalid command\n\n", invalid_command);
	ft_printf("%s\n", STANDARD_COMMANDS);
	i = -1;
	ft_printf("\n");
	ft_printf("%s\n", DIGEST_COMMANDS);
	while (++i < DIGEST_COMMANDS_AMOUNT)
		ft_printf("%s\n", digest_commands[i].command);
	ft_printf("\n");
	ft_printf("%s\n", CIPHER_COMMANDS);
	i = -1;
	while (++i < CIPHER_COMMANDS_AMOUNT)
		ft_printf("%s\n", cipher_commands[i].command);
}

int			main(int argc, char **argv)
{
	static t_command_handler	digest_commands[] = {
		{"md5", md5_handler},
		{"sha224", sha224_handler},
		{"sha256", sha256_handler}
	};
	static t_command_handler	cipher_commands[] = {
		{"base64", base64_handler}
	};
	t_handler					handler;
	

	if (argc < 2)
	{
		ft_printf(USAGE_MSG);
		return (0);
	}
	handler = get_command_handler(argv[1], digest_commands, cipher_commands);
	if (handler == NULL)
		print_commands(argv[1], digest_commands, cipher_commands);
	else
		handler(argc - 2, argv + 2);
	return (0);
}
