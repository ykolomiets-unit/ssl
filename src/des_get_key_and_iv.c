#include "des.h"
#include "md5.h"
#include "pbkdf2.h"
#include "libft.h"

static void		primitive_kdf
(
	char *password,
	t_byte salt[DES_SALT_LENGTH],
	t_byte key[DES_KEY_LENGTH],
	t_byte iv[DES_IV_LENGTH]
)
{
	t_md5_ctx	ctx;
	t_byte		digest[DES_KEY_LENGTH + DES_IV_LENGTH];

	md5_init(&ctx);
	md5_update(&ctx, (t_byte *)password, ft_strlen(password));
	md5_update(&ctx, salt, DES_SALT_LENGTH);
	md5_final(&ctx, digest);
	ft_memcpy(key, digest, DES_KEY_LENGTH);
	ft_memcpy(iv, digest + DES_KEY_LENGTH, DES_IV_LENGTH);
}

static void		apply_pbkdf2
(
	char *password,
	t_byte salt[DES_SALT_LENGTH],
	t_byte key[DES_KEY_LENGTH],
	t_byte iv[DES_IV_LENGTH]
)
{
	t_pbkdf2_params	params;
	t_byte			result[DES_KEY_LENGTH + DES_IV_LENGTH];

	params.password = (t_byte *)password;
	params.password_length = ft_strlen(password);
	params.salt = salt;
	params.salt_length = DES_SALT_LENGTH;
	params.iteration_count = 4096;
	pbkdf2(params, result, DES_KEY_LENGTH + DES_IV_LENGTH);
	ft_memcpy(key, result, DES_KEY_LENGTH);
	ft_memcpy(iv, result + DES_KEY_LENGTH, DES_IV_LENGTH);
}

int				des_derive_key_from_password(t_pbkdf_params *options)
{
	if (options->generate_salt == TRUE)
		if (des_get_salt(options->salt, DES_SALT_LENGTH))
			return (-1);
	if (options->use_pbkdf2 == FALSE)
		primitive_kdf(options->password, options->salt, options->key, options->iv);
	else
		apply_pbkdf2(options->password, options->salt, options->key, options->iv);
	return (0);
}
