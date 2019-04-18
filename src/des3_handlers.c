#include "ft_ssl.h"
#include "des.h"

void	des_ede3_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_ECB, TRUE);
}

void	des_ede3_cbc_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CBC, TRUE);
}
