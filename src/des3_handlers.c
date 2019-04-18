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

void	des_ede3_cfb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CFB, TRUE);
}
void	des_ede3_ofb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_OFB, TRUE);
}
