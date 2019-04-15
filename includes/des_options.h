#ifndef DES_OPTIONS_H
# define DES_OPTIONS_H

# include "types.h"
# include "des.h"

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
int					print_ksi_option_handler(int pos, int argc, char **argv, t_des_options *options);
int					help_option_handler(int pos, int argc, char **argv, t_des_options *options);

void				des_parse_options(t_des_options *options, int argc, char **argv);

#endif
