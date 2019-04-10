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
	//print_options(&options);
	if (options.encode)
		des_ecb_encode(key, in, out);
	else
		des_ecb_decode(key, in, out);
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

typedef struct	s_des_ctx
{
	int			mode;
	uint64_t	key;
	uint64_t	subkeys[16];
	t_byte		block[DES_BLOCK_SIZE];
	uint32_t	last_block_size;
	int			out;
}				t_des_ctx;

void		des_ecb_init(t_des_ctx *ctx)
{
	generate_subkeys(ctx->key, ctx->subkeys, ctx->mode);
}

void		des_ecb_update(t_des_ctx *ctx, t_byte *input, uint32_t input_len)
{
	uint32_t	current_pos;
	uint32_t	start_pos;

	current_pos = 0;
	if (ctx->last_block_size > 0 && (input_len > DES_BLOCK_SIZE - ctx->last_block_size))
	{
		ft_memcpy(ctx->block, input, DES_BLOCK_SIZE - ctx->last_block_size);
		current_pos = DES_BLOCK_SIZE - ctx->last_block_size;
		des_core(ctx->subkeys, ctx->block, ctx->block);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	start_pos = current_pos;
	while (current_pos + DES_BLOCK_SIZE < input_len)
	{
		des_core(ctx->subkeys, input + current_pos, input + current_pos);
		current_pos += DES_BLOCK_SIZE;
	}
	write(ctx->out, input + start_pos, current_pos - start_pos);
	ctx->last_block_size = input_len - current_pos;
	ft_memcpy(ctx->block, input + current_pos, ctx->last_block_size);
}

void		des_ecb_final(t_des_ctx *ctx)
{
	if (ctx->mode == ENCODE)
	{
		if (ctx->last_block_size == 8)
		{
			des_core(ctx->subkeys, ctx->block, ctx->block);
			write(ctx->out, ctx->block, DES_BLOCK_SIZE);
			ctx->last_block_size = 0;
		}
		add_padding(ctx->last_block_size, ctx->block);
		des_core(ctx->subkeys, ctx->block, ctx->block);
		write(ctx->out, ctx->block, DES_BLOCK_SIZE);
	}
	else
	{
		des_core(ctx->subkeys, ctx->block, ctx->block);
		int	padding = ctx->block[7];
		if (padding < 1 || padding > 8)
			ft_printf("Wrong padding\n");
		for (int i = 0; i < padding; i++)
		{
			if (ctx->block[7 - i] != padding)
				ft_printf("Wrong padding\n");
		}
		write(ctx->out, ctx->block, DES_BLOCK_SIZE - padding);
	}
}

void		des_ecb_encode(uint64_t key, int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = ENCODE;
	ctx.key = key;
	ctx.out = out;
	des_ecb_init(&ctx);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_ecb_update(&ctx, buffer, r);
	des_ecb_final(&ctx);
}

void		des_ecb_decode(uint64_t key, int in, int out)
{
	t_des_ctx	ctx;
	t_byte		buffer[4096];
	int			r;

	ctx.mode = DECODE;
	ctx.key = key;
	ctx.out = out;
	des_ecb_init(&ctx);
	r = 0;
	while ((r = read(in, buffer, 4096)) > 0)
		des_ecb_update(&ctx, buffer, r);
	des_ecb_final(&ctx);
}
