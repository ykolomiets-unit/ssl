#include "des.h"
#include "pbkdf2.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		get_salt(t_byte *buf, uint32_t salt_len)
{
	uint32_t	pos;
	int			fd;
	int			r;

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

void	des_get_key_and_iv
(
	char *pass,
	t_byte salt[DES_SALT_LEN],
	t_byte key[DES_KEY_LEN],
	t_byte iv[DES_IV_LEN]
)
{
	t_pbkdf2_params	params;
	t_byte			dk[DES_KEY_LEN + DES_IV_LEN];

	params.pass = (t_byte *)pass;
	params.pass_len = ft_strlen(pass);
	get_salt(salt, DES_SALT_LEN);
	params.salt = salt;
	params.salt_len = DES_SALT_LEN;
	params.dk = dk;
	params.dk_len = DES_KEY_LEN + DES_IV_LEN;
	pbkdf2_hmac_sha256(params);
	ft_memcpy(key, dk, DES_KEY_LEN);
	ft_memcpy(iv, dk + DES_KEY_LEN, DES_IV_LEN);
}