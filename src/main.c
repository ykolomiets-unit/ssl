#include "libft.h"
#include "md5.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	unsigned char digest[16];

	md5_string("huy", digest);
	for (int i = 0; i < 16; i++)
		ft_printf("%.2x", digest[i]);
	ft_printf("\n");
	return (0);
}
