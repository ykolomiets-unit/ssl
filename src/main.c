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

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"
#define STANDARD_COMMANDS "Standard commands: "
#define DIGEST_COMMANDS "Message Digest commands: "
#define CIPHER_COMMANDS "Cipher commands: "

#define DIGEST_COMMANDS_AMOUNT 3

static t_handler	get_command_handler
(
	char *command_name,
	t_command_handler digest_commands[]
)
{
	int							i;

	i = -1;
	while (++i < DIGEST_COMMANDS_AMOUNT)
		if (ft_strcmp(command_name, digest_commands[i].command) == 0)
			return (digest_commands[i].handler);
	return (NULL);
}

static void			print_commands
(
	t_command_handler digest_commands[]
)
{
	int	i;

	ft_printf("\n%s\n", STANDARD_COMMANDS);
	ft_printf("\n%s\n", DIGEST_COMMANDS);
	i = -1;
	while (++i < DIGEST_COMMANDS_AMOUNT)
		ft_printf("%s\n", digest_commands[i].command);
	ft_printf("\n%s\n", CIPHER_COMMANDS);
}

int					main(int argc, char **argv)
{
	static t_command_handler	digest_commands[] = {
		{"md5", md5_handler},
		{"sha224", sha224_handler},
		{"sha256", sha256_handler}
	};
	t_handler					handler;
	t_ssl						ssl;

	if (argc < 2)
	{
		ft_printf(USAGE_MSG);
		return (0);
	}
	ssl.command = argv[1];
	ssl.argc = argc - 2;
	ssl.argv = argv + 2;
	handler = get_command_handler(ssl.command, digest_commands);
	if (handler == NULL)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command\n", ssl.command);
		print_commands(digest_commands);
	}
	else
		handler(&ssl);
	return (0);
}
