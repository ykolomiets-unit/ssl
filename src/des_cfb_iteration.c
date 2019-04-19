/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cfb_iteration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:24:15 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:28:14 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void				des_cfb_encryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	core(keys, vector, vector);
	xor_blocks(vector, block, block);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
}

void				des_cfb_decryption_iteration
(
	uint64_t *keys,
	t_byte block[DES_BLOCK_SIZE],
	t_byte vector[DES_BLOCK_SIZE],
	t_des_core core
)
{
	t_byte	temp[DES_BLOCK_SIZE];

	core(keys, vector, temp);
	ft_memcpy(vector, block, DES_BLOCK_SIZE);
	xor_blocks(block, temp, block);
}
