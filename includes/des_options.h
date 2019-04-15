#ifndef DES_OPTIONS_H
# define DES_OPTIONS_H

# include "types.h"
# include "des.h"

typedef struct		s_des_options
{
	t_bool			encode;
	t_bool			decode;
	t_bool			base64;
	int				input_file;
	int				output_file;
	t_byte			key[DES_KEY_LENGTH];
	t_bool			key_present;
	t_byte			salt[DES_SALT_LENGTH];
	t_bool			salt_present;
	t_byte			initial_vector[DES_IV_LENGTH];
	t_bool			initial_vector_present;
	t_bool			use_pbkdf2;
	char			password[1024];
	t_bool			password_present;
}					t_des_options;

typedef	int			(*t_des_optparser)(int pos, int argc, char **argv, t_des_options *options);

typedef struct		s_des_option_handler
{
	char			*option;
	t_des_optparser	handler;
}					t_des_option_handler;

int					decode_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					encode_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					base64_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					input_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					output_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					key_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					salt_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					iv_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					password_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					pbkdf2_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					help_option_handler(int pos, int argc, char **argv, t_des_options *options);

void				des_parse_options(t_des_options *options, int argc, char **argv);

#endif
