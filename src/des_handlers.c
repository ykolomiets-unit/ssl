#include "ft_ssl.h"
#include "des.h"

void	des_ecb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_ECB, FALSE);
}

void	des_cbc_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CBC, FALSE);
}

void	des_pcbc_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_PCBC, FALSE);
}

void	des_cfb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CFB, FALSE);
}

void	des_ofb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_OFB, FALSE);
}
