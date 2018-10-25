/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:37:14 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:37:16 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "utils.h"

# define FALSE 0
# define TRUE 1

typedef enum	e_source_type
{
	SOURCE_FILE,
	SOURCE_STRING,
	SOURCE_STDIN
}				t_source_type;

typedef struct	s_ssl
{
	char		*command;
	int			argc;
	char		**argv;
}				t_ssl;

typedef void	(*t_handler)(t_ssl *);

typedef struct	s_command_handler
{
	char		*command;
	t_handler	handler;
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

typedef struct	s_base64_options
{
	t_bool		encode;
	t_bool		decode;
	char		*input_file;
	char		*output_file;
}				t_base64_options;

int				error(char *err_msg);
void			print_digest(unsigned char *digest, int size);
void			md5_handler(t_ssl *ssl);
void			sha224_handler(t_ssl *ssl);
void			sha256_handler(t_ssl *ssl);
void			sha384_handler(t_ssl *ssl);
void			sha512_handler(t_ssl *ssl);
void			base64_handler(t_ssl *ssl);
void			process_digest(t_ssl *ssl, t_digest_help help);

#endif
