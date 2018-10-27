#ifndef PBKDF2_H
# define PBKDF2_H

# include "types.h"

typedef struct	s_pbkdf2_params
{
	t_byte		*pass;
	uint32_t	pass_len;
	t_byte		*salt;
	uint32_t	salt_len;
	uint32_t	c;
	t_byte		*dk;
	uint32_t	dk_len;
}				t_pbkdf2_params;

int				pbkdf2_hmac_sha256(t_pbkdf2_params params);

#endif