#ifndef DES_OPTIONS_H
# define DES_OPTIONS_H

# include "des.h"

typedef	int			(*t_des_optparser)(int pos, int argc, char **argv,
						t_des_options *options);

typedef struct		s_des_option_handler
{
	char			*option;
	t_des_optparser	handler;
}					t_des_option_handler;

int					des_decode_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_encode_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_base64_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_input_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_output_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_key_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_salt_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_iv_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_password_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_pbkdf2_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_print_ksi_option_handler(int pos, int argc, char **argv,
						t_des_options *options);
int					des_help_option_handler(int pos, int argc, char **argv,
						t_des_options *options);

void				des_set_default_options(t_des_options *options);
void				des_parse_options(t_des_options *options, int argc,
						char **argv);

#endif
