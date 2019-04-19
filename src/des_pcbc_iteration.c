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

void				des_pcbc_encryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	t_byte	temp[DES_BLOCK_SIZE];

	ft_memcpy(temp, block, DES_BLOCK_SIZE);
	xor_blocks(block, vector, block);
	core(keys, block, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
	xor_blocks(vector, temp, vector);
}

void				des_pcbc_decryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	t_byte	temp[DES_BLOCK_SIZE];

	ft_memcpy(temp, block, DES_BLOCK_SIZE);
	core(keys, block, block);
	xor_blocks(block, vector, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
	xor_blocks(vector, temp, vector);
}

