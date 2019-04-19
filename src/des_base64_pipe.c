/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_base64_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:23:43 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:23:45 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"
#include "base64.h"
#include "ssl_error.h"
#include <stdlib.h>
#include <unistd.h>

void		initialize_base64_write_pipe(t_des_options *options)
{
	int		fd[2];
	pid_t	p;

	if (pipe(fd) == -1)
		ssl_error("Pipe failed\n");
	p = fork();
	if (p < 0)
		ssl_error("Fork failed\n");
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
		ssl_error("Pipe failed\n");
	p = fork();
	if (p < 0)
		ssl_error("Fork failed\n");
	if (p > 0)
	{
		close(fd[1]);
		options->input_file = fd[0];
	}
	else
	{
		close(fd[0]);
		base64_decode_file_to_file(options->input_file, fd[1]);
		exit(0);
	}
}
