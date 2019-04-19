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

void				des_ofb_encryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	core(keys, vector, vector);
	xor_blocks(vector, block, block);
}

void				des_ofb_decryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	core(keys, vector, vector);
	xor_blocks(block, vector, block);
}

