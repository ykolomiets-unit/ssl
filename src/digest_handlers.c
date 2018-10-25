/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:05:23 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/23 19:05:33 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include "sha224_256.h"
#include "sha384_512.h"

void	md5_handler(t_ssl *ssl)
{
	t_digest_help	help;

	help.algorithm_name = "MD5";
	help.digest_size = 16;
	help.digest_of_string = md5_string;
	help.digest_of_file = md5_file;
	help.digest_of_stdin = md5_filter;
	help.something_processed = FALSE;
	process_digest(ssl, help);
}

void	sha224_handler(t_ssl *ssl)
{
	t_digest_help	help;

	help.algorithm_name = "SHA224";
	help.digest_size = 28;
	help.digest_of_string = sha224_string;
	help.digest_of_file = sha224_file;
	help.digest_of_stdin = sha224_filter;
	help.something_processed = FALSE;
	process_digest(ssl, help);
}

void	sha256_handler(t_ssl *ssl)
{
	t_digest_help	help;

	help.algorithm_name = "SHA256";
	help.digest_size = 32;
	help.digest_of_string = sha256_string;
	help.digest_of_file = sha256_file;
	help.digest_of_stdin = sha256_filter;
	help.something_processed = FALSE;
	process_digest(ssl, help);
}

void	sha384_handler(t_ssl *ssl)
{
	t_digest_help	help;

	help.algorithm_name = "SHA384";
	help.digest_size = 48;
	help.digest_of_string = sha384_string;
	help.digest_of_file = sha384_file;
	help.digest_of_stdin = sha384_filter;
	help.something_processed = FALSE;
	process_digest(ssl, help);
}

void	sha512_handler(t_ssl *ssl)
{
	t_digest_help	help;

	help.algorithm_name = "SHA512";
	help.digest_size = 64;
	help.digest_of_string = sha512_string;
	help.digest_of_file = sha512_file;
	help.digest_of_stdin = sha512_filter;
	help.something_processed = FALSE;
	process_digest(ssl, help);
}
