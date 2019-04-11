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
#include "ft_ssl.h"
#include "utils.h"
#include <unistd.h>

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"
#define STANDARD_COMMANDS "Standard commands: "
#define DIGEST_COMMANDS "Message Digest commands: "
#define CIPHER_COMMANDS "Cipher commands: "

#define DIGEST_COMMANDS_AMOUNT 5
#define CIPHER_COMMANDS_AMOUNT 3

static const t_command_handler	g_digest_commands[] = {
	{"md5", md5_handler},
	{"sha224", sha224_handler},
	{"sha256", sha256_handler},
	{"sha384", sha384_handler},
	{"sha512", sha512_handler}
};

static const t_command_handler	g_cipher_commands[] = {
	{"base64", base64_handler},
	{"des", des_ecb_handler},
	{"des-ecb", des_ecb_handler}
};

static void						print_commands(void)
{
	int	i;

	ft_printf("\n%s\n", STANDARD_COMMANDS);
	ft_printf("\n%s\n", DIGEST_COMMANDS);
	i = -1;
	while (++i < DIGEST_COMMANDS_AMOUNT)
		ft_printf("%s\n", g_digest_commands[i].command);
	ft_printf("\n%s\n", CIPHER_COMMANDS);
	i = -1;
	while (++i < CIPHER_COMMANDS_AMOUNT)
		ft_printf("%s\n", g_cipher_commands[i].command);
}

static t_handler				get_command_handler
(
	char *command_name
)
{
	int	i;

	i = -1;
	while (++i < DIGEST_COMMANDS_AMOUNT)
		if (ft_strcmp(command_name, g_digest_commands[i].command) == 0)
			return (g_digest_commands[i].handler);
	i = -1;
	while (++i < CIPHER_COMMANDS_AMOUNT)
		if (ft_strcmp(command_name, g_cipher_commands[i].command) == 0)
			return (g_cipher_commands[i].handler);
	return (NULL);
}

static int						process_params
(
	int argc,
	char **argv
)
{
	t_handler	handler;
	t_ssl		ssl;

	ssl.command = argv[0];
	ssl.argc = argc - 1;
	ssl.argv = argv + 1;
	handler = get_command_handler(ssl.command);
	if (handler == NULL)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command\n", ssl.command);
		print_commands();
	}
	else
		handler(&ssl);
	return (0);
}

static int						listen_commands_from_stdin(void)
{
	char	buffer[1025];
	char	**table;
	int		argc;
	int		r;

	while (1)
	{
		ft_printf("ft_ssl> ");
		if ((r = read(0, buffer, 1024)) > 0)
		{
			buffer[r] = '\0';
			filter_str(buffer);
			table = ft_strsplit(buffer, ' ');
			argc = ft_get_table_size(table);
			if (argc > 0)
				process_params(argc, table);
			ft_free_table(&table, argc);
		}
		else
			return (0);
	}
}

int								main
(
	int argc,
	char **argv
)
{
	if (argc < 2)
		listen_commands_from_stdin();
	else
		process_params(argc - 1, argv + 1);
	return (0);
}
