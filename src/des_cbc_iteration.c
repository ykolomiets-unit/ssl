#include "des.h"
#include "libft.h"

static inline void	xor_blocks(t_byte *a, t_byte *b, t_byte *res)
{
	uint32_t	i;

	i = 0;
	while (i < DES_BLOCK_SIZE)
	{
		res[i] = a[i] ^ b[i];
		i++;
	}
}

void				des_cbc_encryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	xor_blocks(block, vector, block);
	core(keys, block, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
}

void				des_cbc_decryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	t_byte	temp_vector[DES_BLOCK_SIZE];

	ft_memcpy(temp_vector, block, DES_BLOCK_SIZE);
	core(keys, block, block);
	xor_blocks(block, vector, block);
	ft_memcpy(vector, temp_vector, DES_BLOCK_SIZE);
}

