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
#include "ft_ssl.h"

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"

#define COMMANDS_AMOUNT 3

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

int			main(int argc, char **argv)
{
	static t_command_handler	handlers[COMMANDS_AMOUNT] = {
		{"md5", md5_handler},
		{"sha224", sha224_handler},
		{"sha256", sha256_handler}
	};
	int							i;

	if (argc < 2)
	{
		ft_printf(USAGE_MSG);
		return (0);
	}
	i = 0;
	while (i < COMMANDS_AMOUNT)
	{
		if (ft_strcmp(argv[1], handlers[i].command) == 0)
		{
			handlers[i].handler(argc - 2, argv + 2);
			return (0);
		}
		i++;
	}
	ft_printf(USAGE_MSG);
	return (0);
}
