/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:26:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/25 21:26:22 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static int	get_file_name
(
	int *i,
	int argc,
	char **argv,
	char **target
)
{
	if ((*i + 1) >= argc)
	{
		ft_printf("No file name after %s\n", argv[*i]);
		return (-1);
	}
	*i += 1;
	*target = argv[*i];
	return (0);
}

static int	base64_parse_options
(
	t_base64_options *options,
	int argc,
	char **argv
)
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
			if (get_file_name(&i, argc, argv, &options->input_file))
				return (-1);
		}
		else if (ft_strcmp(argv[i], "-o") == 0)
		{
			if (get_file_name(&i, argc, argv, &options->output_file))
				return (-1);
		}
		else if (ft_strcmp(argv[i], "--") == 0 && i++)
			break ;
		else
			break ;
	if (i < argc)
		options->input_file = argv[i];
	return (0);
}

static int	open_input_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Unable to open '%s': ", file_name);
		perror(NULL);
		exit(1);
	}
	return (fd);
}

static int	open_output_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("Unable to create '%s': ", file_name);
		perror(NULL);
		exit(1);
	}
	return (fd);
}

void		base64_handler(t_ssl *ssl)
{
	t_base64_options	options;
	int					in;
	int					out;

	ft_bzero(&options, sizeof(options));
	if (base64_parse_options(&options, ssl->argc, ssl->argv))
		return ;
	if (options.input_file == NULL)
		in = 0;
	else
		in = open_input_file(options.input_file);
	if (options.output_file == NULL)
		out = 1;
	else
		out = open_output_file(options.output_file);
	if (options.encode == TRUE && options.decode == TRUE)
	{
		ft_printf("Choose one option: encode (default) or decode\n");
		exit(1);
	}
	if (!options.decode)
		base64_encode_file_to_file(in, out);
	else
		base64_decode_file_to_file(in, out);
}

