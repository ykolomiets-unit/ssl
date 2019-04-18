#include "ft_ssl.h"
#include "des.h"

void	des_ecb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_ECB); 
}

void	des_cbc_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CBC);
}

void	des_pcbc_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_PCBC);
}

void	des_cfb_handler(t_ssl *ssl)
{
	des_handler(ssl->argc, ssl->argv, DES_MODE_CFB);
}

