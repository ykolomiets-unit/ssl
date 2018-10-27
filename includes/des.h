#ifndef DES_H
# define DES_H

typedef struct	s_pbkdf2_params
{
	char		*pass;
	char		*salt;
	int			c;
	char		*dk;
	int			dk_len;
}				t_pbkdf2_params;

int				pbkdf2_hmac_sha256(t_pbkdf2_params params);

#endif