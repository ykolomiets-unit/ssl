#include "des.h"
#include "libft.h"

void				des_ecb_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
)
{
	(void)vector;
	des_core(keys, block, block);
}
