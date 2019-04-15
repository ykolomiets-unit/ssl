#include "ssl_error.h"
#include "libft.h"
#include <stdlib.h>

void	ssl_error(const char *error_msg)
{
	ft_dprintf(2, "%s\n", error_msg);
	exit(-1);
}
