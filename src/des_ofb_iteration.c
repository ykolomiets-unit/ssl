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

void				des_ofb_encryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	des_core(keys, vector, vector);
	xor_blocks(vector, block, block);
}

void				des_ofb_decryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	des_core(keys, vector, vector);
	xor_blocks(block, vector, block);
}

