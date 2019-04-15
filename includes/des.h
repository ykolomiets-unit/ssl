/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:19:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/27 18:19:22 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "types.h"

# define MOVE_BIT(n, s, e) ((((n) & (0x1L << (64 - s))) >> (64 - s)) << (64 - e))
# define ROL28(a, n) ((((a) << (n)) | ((a) >> (28 - (n)))) & 0x0FFFFFFF)

# define DES_BLOCK_SIZE 8
# define DES_KEY_LENGTH 8
# define DES_SALT_LENGTH 8
# define DES_IV_LENGTH 8

# define ENCODE 0
# define DECODE 1

typedef struct	s_pbkdf_params
{
	t_bool		use_pbkdf2;
	t_bool		generate_salt;
	t_byte		*salt;
	t_byte		*key;
	t_byte		*iv;
	char		*password;
}				t_pbkdf_params;

typedef struct	s_des_ctx
{
	int			mode;
	uint64_t	key;
	uint64_t	subkeys[16];
	t_byte		block[DES_BLOCK_SIZE];
	uint32_t	last_block_size;
	int			out;
}				t_des_ctx;

typedef struct	s_des_options
{
	t_bool		encode;
	t_bool		decode;
	t_bool		base64;
	int			input_file;
	int			output_file;
	t_byte		key[DES_KEY_LENGTH];
	t_bool		key_present;
	t_byte		salt[DES_SALT_LENGTH];
	t_bool		salt_present;
	t_byte		initial_vector[DES_IV_LENGTH];
	t_bool		initial_vector_present;
	t_bool		use_pbkdf2;
	char		password[1024];
	t_bool		password_present;
	t_bool		print_ksi;
}				t_des_options;

int				des_derive_key_from_password(t_pbkdf_params *options);
void			des_add_padding(int filled, t_byte block[DES_BLOCK_SIZE]);

void			des_key_schedule(uint64_t key, uint64_t subkeys[16], int mode);
void			des_core(uint64_t keys[16], t_byte input[DES_BLOCK_SIZE], t_byte output[DES_BLOCK_SIZE]);

void			des_ecb_encode(t_byte key[DES_KEY_LENGTH], int in, int out);
void			des_ecb_decode(t_byte key[DES_KEY_LENGTH], int in, int out);

void			initialize_base64_write_pipe(t_des_options *options);
void			initialize_base64_read_pipe(t_des_options *options);
void			des_get_password_from_stdin(t_des_options *options);
int				des_get_salt(t_byte *buf, uint32_t salt_len);
void			des_read_salt(t_byte salt[DES_SALT_LENGTH], int fd);
void			des_write_salt(t_byte *salt, uint32_t len, int fd);
void			des_print_ksi(t_des_options *options);

#endif
