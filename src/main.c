#include "libft.h"
#include "md5.h"
#include "sha224_256.h"

#define USAGE_MSG "usage: ft_ssl command [command opts] [command args]\n"

int		main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	unsigned char	sha256_digest[32];
	unsigned char	sha224_digest[32];
	unsigned char	md5_digest[16];

	sha256_string("abc", sha256_digest);
	sha224_string("abc", sha224_digest);
	md5_string("abc", md5_digest);
	for (int i = 0; i < 32; i++)
		ft_printf("%.2x", sha256_digest[i]);
	ft_printf("\n");
	for (int i = 0; i < 28; i++)
		ft_printf("%.2x", sha224_digest[i]);
	ft_printf("\n");
	for (int i = 0; i < 16; i++)
		ft_printf("%.2x", md5_digest[i]);
	ft_printf("\n");

//	if (argc == 1)
//		ft_printf(USAGE_MSG);
	return (0);
}
