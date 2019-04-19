#include "des.h"
#include "libft.h"

void	des3_core(uint64_t *keys, t_byte *block, t_byte *output)
{
	des_core(keys, block, output);
	des_core(keys + 16, block, output);
	des_core(keys + 32, block, output);
}
