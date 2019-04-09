#include "ft_ssl.h"
#include "des.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_option_value
(
	int *i,
	int argc,
	char **argv,
	char **target
)
{
	if ((*i + 1) >= argc)
	{
		ft_printf("No option value after %s\n", argv[*i]);
		return (-1);
	}
	*i += 1;
	*target = argv[*i];
	return (0);
}

static int	parse
(
	t_des_options *options,
	int *i,
	int argc,
	char **argv
)
{
	static char	*options_with_value = "iokpsv";
	char		*current;
	char		*option_value;

	current = argv[*i];
	if (ft_strcmp(current, "-d") == 0)
		options->decode = TRUE;
	else if (ft_strcmp(current, "-e") == 0)
		options->encode = TRUE;
	else if (ft_strcmp(current, "-a") == 0)
		options->base64 = TRUE;
	else if (ft_strlen(current) == 2 && current[0] == '-' && ft_strchr(options_with_value, current[1]))
	{
		if (get_option_value(i, argc, argv, &option_value))
			return (-1);
		if (ft_strcmp(current, "-i") == 0)
			options->input_file = option_value;
		else if (ft_strcmp(current, "-o") == 0)
			options->output_file = option_value;
		else if (ft_strcmp(current, "-k") == 0)
			options->key = option_value;
		else if (ft_strcmp(current, "-p") == 0)
			options->password = option_value;
		else if (ft_strcmp(current, "-s") == 0)
			options->salt = option_value;
		else if (ft_strcmp(current, "-v") == 0)
			options->initial_vector = option_value;
	}
	else if (ft_strcmp(current, "--") == 0 && *i++)
		return (2);
	else
		return (1);
	return (0);
}


static int	des_parse_options
(
	t_des_options *options,
	int argc,
	char **argv
)
{
	int i;
	int	parse_res;

	i = -1;
	while (++i < argc)
	{
		parse_res = parse(options, &i, argc, argv);
		if (parse_res == -1)
			return (-1);
		if (parse_res == 1)
			break;
		else if (parse_res == 2)
		{
			i++;
			break;
		}
	}
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

void	print_options(t_des_options *options)
{
	ft_printf("Options: \n");
	ft_printf("\tdecrypt = %s\n", options->decode ? "true" : "false");
	ft_printf("\tencrypt = %s\n", options->encode ? "true" : "false");
	ft_printf("\tbase64 = %s\n", options->base64 ? "true" : "false");
	ft_printf("\tinput file = %s\n", options->input_file);
	ft_printf("\toutput file = %s\n", options->output_file);
	ft_printf("\tkey = %s\n", options->key);
	ft_printf("\tpassword = %s\n", options->password);
	ft_printf("\tsalt = %s\n", options->salt);
	ft_printf("\tiv = %s\n", options->initial_vector);
}

static t_byte	get_4bits_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <='f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <='F')
		return (c - 'A' + 10);    
	return (0xff);
}

static int	parse_hex(char *str, uint64_t *res)
{
	uint32_t	i;
	uint64_t	temp;

	i = 0;
	*res = 0;
	while (*str && i < 16)
	{
		temp = get_4bits_value(*str);
		if (temp == 0xff)
			return (-1);
		temp <<= (15 - i) * 4;
		*res |= temp;
		i++;
		str++;
	}
	if (*str)
		return (-2);
	return (0);
}

void		des_handler(t_ssl *ssl)
{
	t_des_options		options;
	int					in;
	int					out;

	ft_bzero(&options, sizeof(options));
	if (des_parse_options(&options, ssl->argc, ssl->argv))
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
	uint64_t	key;
	parse_hex(options.key, &key);
	des_ecb_encode(key, in, out);
}

void		add_padding(int filled, t_byte block[DES_BLOCK_SIZE])
{
	int	value;

	value = DES_BLOCK_SIZE - filled;
	while (filled < DES_BLOCK_SIZE)
	{
		block[filled] = value;
		filled++;
	}
}

void		des_ecb_encode(uint64_t key, int in, int out)
{
	uint64_t	subkeys[16];
	t_byte		block[DES_BLOCK_SIZE];
	int			r;
	uint32_t	in_buf;

	generate_subkeys(key, subkeys);
	r = 0;
	in_buf = 0;
	while ((r = read(in, block + in_buf, DES_BLOCK_SIZE - in_buf)) > 0)
	{
		in_buf += r;
		if (in_buf == DES_BLOCK_SIZE)
		{
			des_core(subkeys, block, block);
			write(out, block, DES_BLOCK_SIZE);
			in_buf = 0;
		}
	}
	add_padding(in_buf, block);
	des_core(subkeys, block, block);
	write(out, block, DES_BLOCK_SIZE);
}
