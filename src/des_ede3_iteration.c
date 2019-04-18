#include "des.h"
#include "libft.h"

void				des_ede3_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	(void)vector;
	des_core(keys, block, block);
	des_core(keys + 16, block, block);
	des_core(keys + 32, block, block);
}
