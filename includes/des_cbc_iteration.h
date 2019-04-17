#ifndef DES_CBC_ITERATION_H
# define DES_CBC_ITERATION_H

# include "des.h"

typedef void	(*t_des_cbc_iteration)
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
);

void			des_cbc_encryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
);

void			des_cbc_decryption_iteration
(
	uint64_t keys[16],
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE]
);

#endif
