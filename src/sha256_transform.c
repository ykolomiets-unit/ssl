/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:22:01 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 22:22:05 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_256.h"
#include "utils.h"

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

static void		initialize
(
	t_word x[64],
	t_byte buffer[64],
	t_word state[8],
	t_word abcdefgh[8]
)
{
	int			i;

	bytes_to_big_endian_words(x, buffer, 64);
	i = 16;
	while (i < 64)
	{
		x[i] = SIG1(x[i - 2]) + x[i - 7] + SIG0(x[i - 15]) + x[i - 16];
		i++;
	}
	i = -1;
	while (++i < 8)
		abcdefgh[i] = state[i];
}

static t_word	*get_k(void)
{
	static t_word	k[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
		0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
		0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
		0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
		0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

	return (k);
}

void			add_new_state(t_word state[8], t_word new_state[8])
{
	int	i;

	i = -1;
	while (++i < 8)
		state[i] += new_state[i];
}

void			sha256_transform
(
	t_word state[8],
	t_byte buffer[64]
)
{
	t_word	x[64];
	t_word	abcdefgh[8];
	t_word	temp[2];
	t_word	*k;
	int		i;

	initialize(x, buffer, state, abcdefgh);
	k = get_k();
	i = -1;
	while (++i < 64)
	{
		temp[0] = abcdefgh[7] + EP1(abcdefgh[4])
			+ CH(abcdefgh[4], abcdefgh[5], abcdefgh[6]) + k[i] + x[i];
		temp[1] = EP0(abcdefgh[0]) + MAJ(abcdefgh[0], abcdefgh[1], abcdefgh[2]);
		abcdefgh[7] = abcdefgh[6];
		abcdefgh[6] = abcdefgh[5];
		abcdefgh[5] = abcdefgh[4];
		abcdefgh[4] = abcdefgh[3] + temp[0];
		abcdefgh[3] = abcdefgh[2];
		abcdefgh[2] = abcdefgh[1];
		abcdefgh[1] = abcdefgh[0];
		abcdefgh[0] = temp[0] + temp[1];
	}
	add_new_state(state, abcdefgh);
}
