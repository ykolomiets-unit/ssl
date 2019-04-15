#include "des.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		des_get_salt(t_byte *buf, uint32_t salt_len)
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

void	des_read_salt(t_byte salt[DES_SALT_LENGTH], int fd)
{
	t_byte	buffer[16];
	int		r;
	int		in_buf;

	in_buf = 0;	
	while ((r = read(fd, buffer + in_buf, 16 - in_buf)) > 0)
		in_buf += r;
	if (r < 0 || in_buf < 16)
	{
		ft_dprintf(2, "Error reading input file\n");
		exit(-1);
	}
	if (ft_strncmp((const char *)buffer, "Salted__", 8) != 0)
	{
		ft_dprintf(2, "Bad magic number");
		exit(-1);
	}
	ft_memcpy(salt, buffer + 8, DES_SALT_LENGTH);
}

void	des_write_salt(t_byte *salt, uint32_t len, int fd)
{
	write(fd, "Salted__", ft_strlen("Salted__"));
	write(fd, salt, len);
}
