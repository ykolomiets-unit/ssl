#include "des.h"
#include "md5.h"
#include "pbkdf2.h"
#include "libft.h"

static void		primitive_kdf(t_pbkdf_params *options)
{
	t_md5_ctx	ctx;
	t_byte		digest[DES_KEY_LENGTH + DES_IV_LENGTH];

	md5_init(&ctx);
	md5_update(&ctx, (t_byte *)options->password, ft_strlen(options->password));
	md5_update(&ctx, options->salt, DES_SALT_LENGTH);
	md5_final(&ctx, digest);
	ft_memcpy(options->key, digest, DES_KEY_LENGTH);
	ft_memcpy(options->iv, digest + DES_KEY_LENGTH, DES_IV_LENGTH);
}

static void		apply_pbkdf2(t_pbkdf_params *options)
{
	t_pbkdf2_params	params;
	t_byte					result[3 * DES_KEY_LENGTH + DES_IV_LENGTH];

	params.password = (t_byte *)options->password;
	params.password_length = ft_strlen(options->password);
	params.salt = options->salt;
	params.salt_length = DES_SALT_LENGTH;
	params.iteration_count = 4096;
	pbkdf2(params, result, options->key_length + DES_IV_LENGTH);
	ft_memcpy(options->key, result, options->key_length);
	ft_memcpy(options->iv, result + options->key_length, DES_IV_LENGTH);
}

int				des_derive_key_from_password(t_pbkdf_params *options)
{
	if (options->generate_salt == TRUE)
		if (des_get_salt(options->salt, DES_SALT_LENGTH))
			return (-1);
	if (options->use_pbkdf2 == FALSE && options->key_length == 8)
		primitive_kdf(options);
	else
		apply_pbkdf2(options);
	return (0);
}
