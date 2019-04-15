#ifndef BASE64_OPTIONS_H
# define BASE64_OPTIONS_H

# include "base64.h"

typedef	int			(*t_b64_optparser)(int pos, int argc, char **argv, t_base64_options *options);

typedef struct		s_b64_option_handler
{
	char			*option;
	t_b64_optparser	handler;
}					t_b64_option_handler;

int					b64_decode_option_handler(int pos, int argc, char **argv, t_base64_options *options);
int					b64_encode_option_handler(int pos, int argc, char **argv, t_base64_options *options);
int					b64_input_option_handler(int pos, int argc, char **argv, t_base64_options *options);
int					b64_output_option_handler(int pos, int argc, char **argv, t_base64_options *options);
int					b64_break_option_handler(int pos, int argc, char **argv, t_base64_options *options);
int					b64_help_option_handler(int pos, int argc, char **argv, t_base64_options *options);

void				base64_parse_options(t_base64_options *options, int argc, char **argv);

#endif
