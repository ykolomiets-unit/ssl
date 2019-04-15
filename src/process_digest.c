/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 20:52:35 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/21 20:52:36 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_error.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

static void	output_result
(
	t_digest_flags *flags,
	t_digest_help *help,
	t_source_type source_type,
	char *source
)
{
	char	*format_string;

	if (flags->quite_mode)
		print_digest(help->digest, help->digest_size);
	else
	{
		if (flags->reverse_mode)
		{
			print_digest(help->digest, help->digest_size);
			format_string = source_type == SOURCE_STRING ? " \"%s\"" : " %s";
			ft_printf(format_string, source);
		}
		else
		{
			format_string = source_type == SOURCE_STRING
							? "%s (\"%s\") = "
							: "%s (%s) = ";
			ft_printf(format_string, help->algorithm_name, source);
			print_digest(help->digest, help->digest_size);
		}
	}
	ft_printf("\n");
}

static void	handle_p
(
	t_digest_help *help
)
{
	help->digest_of_stdin(help->digest, TRUE);
	print_digest(help->digest, help->digest_size);
	ft_printf("\n");
	help->something_processed = TRUE;
}

static int	process_options
(
	t_ssl *ssl,
	t_digest_help *help,
	t_digest_flags *flags
)
{
	int	i;

	i = -1;
	while (++i < ssl->argc)
	{
		if (ft_strcmp(ssl->argv[i], "-s") == 0)
		{
			if (++i >= ssl->argc)
				ssl_error("No string after -s");
			help->digest_of_string(ssl->argv[i], help->digest);
			output_result(flags, help, SOURCE_STRING, ssl->argv[i]);
			help->something_processed = TRUE;
		}
		else if (ft_strcmp(ssl->argv[i], "-q") == 0)
			flags->quite_mode = TRUE;
		else if (ft_strcmp(ssl->argv[i], "-r") == 0)
			flags->reverse_mode = TRUE;
		else if (ft_strcmp(ssl->argv[i], "-p") == 0)
			handle_p(help);
		else if (ft_strcmp(ssl->argv[i], "--") == 0)
			return (i + 1);
		else
			return (i);
	}
	return (i);
}

static void	process_files
(
	t_ssl *ssl,
	t_digest_help *help,
	t_digest_flags *flags
)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < ssl->argc)
	{
		fd = open(ssl->argv[i], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("ft_ssl: %s: %s: ", ssl->command, ssl->argv[i]);
			perror(NULL);
		}
		else
		{
			help->digest_of_file(fd, help->digest);
			output_result(flags, help, SOURCE_FILE, ssl->argv[i]);
		}
		help->something_processed = TRUE;
	}
}

void		process_digest
(
	t_ssl *ssl,
	t_digest_help help
)
{
	t_digest_flags	flags;
	int				i;

	flags.quite_mode = FALSE;
	flags.reverse_mode = FALSE;
	i = process_options(ssl, &help, &flags);
	ssl->argc -= i;
	ssl->argv += i;
	process_files(ssl, &help, &flags);
	if (help.something_processed == FALSE)
	{
		help.digest_of_stdin(help.digest, FALSE);
		print_digest(help.digest, help.digest_size);
		ft_printf("\n");
	}
}
