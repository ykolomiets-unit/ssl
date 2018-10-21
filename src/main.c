#include "libft.h"
#include "md5.h"
#include "sha224_256.h"
#include <stdlib.h>
#include <fcntl.h>

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"

#define COMMANDS_AMOUNT 3
#define FALSE 0
#define TRUE 1

typedef enum	e_source_type
{
	SOURCE_FILE,
	SOURCE_STRING,
	SOURCE_STDIN
}				t_source_type;

typedef struct	s_command_handler
{
	char		*command;
	void		(*handler)(int, char **);
}				t_command_handler;

typedef int		t_bool;

typedef struct	s_digest_flags
{
	t_bool		quite_mode;
	t_bool		reverse_mode;
}				t_digest_flags;

typedef struct	s_digest_help
{
	char		*algorithm_name;
	void		(*digest_of_string)(char *, unsigned char *);
	void		(*digest_of_file)(int, unsigned char *);
	void		(*digest_of_stdin)(unsigned char *, int);
	int			digest_size;
	t_byte		digest[32];
	t_bool		something_processed;
}				t_digest_help;

void	error(char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(1);
}

void	print_digest(t_byte *digest, int digest_size)
{
	int	i;

	i = 0;
	while (i < digest_size)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
}

void	output_result
(
	t_digest_flags *flags,
	t_digest_help *help,
	t_source_type source_type,
	char *source
)
{
	char	*format_string;

	if (source_type == SOURCE_STRING || source_type == SOURCE_FILE)
	{
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
				format_string = source_type == SOURCE_STRING ? "%s (\"%s\") = " : "%s (%s) = ";
				ft_printf(format_string, help->algorithm_name, source);
				print_digest(help->digest, help->digest_size);
			}
		}
	}
	ft_printf("\n");
}

void	handle_p
(
	t_digest_help *help
)
{
	help->digest_of_stdin(help->digest, TRUE);
	print_digest(help->digest, help->digest_size);
	ft_printf("\n");
	help->something_processed = TRUE;
}

int		process_options
(
	int argc,
	char **argv,
	t_digest_help *help,
	t_digest_flags *flags
)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-s") == 0)
		{
			if (++i >= argc)
				error("No string after -s");
			help->digest_of_string(argv[i], help->digest);
			output_result(flags, help, SOURCE_STRING, argv[i]);
			help->something_processed = TRUE;
		}
		else if (ft_strcmp(argv[i], "-q") == 0)
			flags->quite_mode = TRUE;
		else if (ft_strcmp(argv[i], "-r") == 0)
			flags->reverse_mode = TRUE;
		else if (ft_strcmp(argv[i], "-p") == 0)
			handle_p(help);
		else
			break ;
	}
	return (i);
}

void	process_files
(
	int argc,
	char **argv,
	t_digest_help *help,
	t_digest_flags *flags
)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			ft_printf("Can't open file %s\n", argv[i]);
		else
		{
			help->digest_of_file(fd, help->digest);
			output_result(flags, help, SOURCE_FILE, argv[i]);
		}
	}
}

void	process_digest(int argc, char **argv, t_digest_help help)
{
	t_digest_flags	flags;
	int				i;

	flags.quite_mode = FALSE;
	flags.reverse_mode = FALSE;
	i = process_options(argc, argv, &help, &flags);
	process_files(argc - i, argv + i, &help, &flags);
	if (help.something_processed == FALSE)
	{
		help.digest_of_stdin(help.digest, FALSE);
		print_digest(help.digest, help.digest_size);
		ft_printf("\n");
	}
}

void	md5_handler(int argc, char **argv)
{
	static t_digest_help	help = {
		.algorithm_name = "MD5",
		.digest_size = 16,
		.digest_of_string = md5_string,
		.digest_of_file = md5_file,
		.digest_of_stdin = md5_filter,
		.something_processed = FALSE
	};

	process_digest(argc, argv, help);
}

void	sha224_handler(int argc, char **argv)
{
	static t_digest_help	help = {
		.algorithm_name = "SHA224",
		.digest_size = 28,
		.digest_of_string = sha224_string,
		.digest_of_file = sha224_file,
		.digest_of_stdin = sha224_filter,
		.something_processed = FALSE
	};

	process_digest(argc, argv, help);
}

void	sha256_handler(int argc, char **argv)
{
	static t_digest_help	help = {
		.algorithm_name = "SHA256",
		.digest_size = 32,
		.digest_of_string = sha256_string,
		.digest_of_file = sha256_file,
		.digest_of_stdin = sha256_filter,
		.something_processed = FALSE
	};

	process_digest(argc, argv, help);
}

int		main(int argc, char **argv)
{
	t_command_handler	handlers[COMMANDS_AMOUNT] = {
		{"md5", md5_handler},
		{"sha224", sha224_handler},
		{"sha256", sha256_handler}
	};
	int					i;

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
