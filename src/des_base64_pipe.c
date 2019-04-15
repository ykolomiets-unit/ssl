#include "des.h"
#include "libft.h"
#include "base64.h"
#include <stdlib.h>
#include <unistd.h>

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
