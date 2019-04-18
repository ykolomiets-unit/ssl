#include "des.h"
#include "libft.h"

static inline void	xor_blocks(t_byte a[DES_BLOCK_SIZE], t_byte b[DES_BLOCK_SIZE], t_byte res[DES_BLOCK_SIZE])
{
	uint32_t	i;

	i = 0;
	while (i < DES_BLOCK_SIZE)
	{
		res[i] = a[i] ^ b[i];
		i++;
	}
}

void				des_cfb_encryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	core(keys, vector, vector);
	xor_blocks(vector, block, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
}

void				des_cfb_decryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	t_byte	temp[DES_BLOCK_SIZE];

	core(keys, vector, temp);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
	xor_blocks(block, temp, block);
}

