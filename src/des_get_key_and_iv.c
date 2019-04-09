#include "des.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		get_salt(t_byte *buf, uint32_t salt_len)
{
	uint32_t	pos;
	int       fd;
	int       r;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (-1);
	pos = 0;
	while (pos < salt_len && (r = read(fd, buf + pos, salt_len - pos)) > 0 )
		pos += r;
	if (pos != salt_len)
		return (-1);
	return (0);
}
