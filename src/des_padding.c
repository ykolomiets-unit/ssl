#include "des.h"

void		des_add_padding(int filled, t_byte block[DES_BLOCK_SIZE])
{
	int	value;

	value = DES_BLOCK_SIZE - filled;
	while (filled < DES_BLOCK_SIZE)
	{
		block[filled] = value;
		filled++;
	}
}
