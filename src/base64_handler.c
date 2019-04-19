/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:26:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/26 16:41:27 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "base64.h"
#include "base64_options.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	set_default_options(t_base64_options *options)
{
	options->break_num = 0;
	options->decode = FALSE;
	options->encode = FALSE;
	options->input_file = 0;
	options->output_file = 1;
}

void		base64_handler(t_ssl *ssl)
{
	t_base64_options	options;

	set_default_options(&options);
	base64_parse_options(&options, ssl->argc, ssl->argv);
	if (options.encode == FALSE && options.decode == FALSE)
		options.encode = TRUE;
	if (options.encode == TRUE)
		base64_encode_file_to_file(options.input_file,
			options.output_file, options.break_num);
	else
		base64_decode_file_to_file(options.input_file, options.output_file);
}
