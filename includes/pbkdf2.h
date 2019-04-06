#ifndef PBKDF2_H
# define PBKDF2_H

# include "types.h"

typedef struct	s_pbkdf2_params
{
	t_byte		*password;
	uint32_t	password_length;
	t_byte		*salt;
	uint32_t	salt_length;
	uint32_t	iteration_count;
}				t_pbkdf2_params;

void			pbkdf2(t_pbkdf2_params params, t_byte *dk, uint32_t dk_len);

#endif
