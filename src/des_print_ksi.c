#include "des.h"
#include "libft.h"

static void	print_hex(t_byte *bytes, uint32_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%2.2x", bytes[i]);
		i++;
	}
}

void	des_print_ksi(t_des_options *options)
{
	ft_printf("salt = ");
	print_hex(options->salt, DES_SALT_LENGTH);
	ft_printf("\nkey = ");
	if (options->des3)
		print_hex(options->key, 3 * DES_KEY_LENGTH);
	else
		print_hex(options->key, DES_KEY_LENGTH);
	ft_printf("\niv = ");
	print_hex(options->initial_vector, DES_IV_LENGTH);
	ft_printf("\n");
}
