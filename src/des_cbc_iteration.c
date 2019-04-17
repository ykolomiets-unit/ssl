#include "des_cbc_iteration.h"
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

void				des_cbc_encryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	xor_blocks(block, vector, block);
	des_core(keys, block, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
}

void				des_cbc_decryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	t_byte	temp_vector[DES_BLOCK_SIZE];

	ft_memcpy(temp_vector, block, DES_BLOCK_SIZE);
	des_core(keys, block, block);
	xor_blocks(block, vector, block);
	ft_memcpy(vector, temp_vector, DES_BLOCK_SIZE);
}

