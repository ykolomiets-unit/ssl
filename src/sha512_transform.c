/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 23:00:13 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/25 22:39:21 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha384_512.h"
#include "utils.h"

#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (64 - (bits))))

#define EP0(x) (ROTRIGHT(x, 28) ^ ROTRIGHT(x, 34) ^ ROTRIGHT(x, 39))
#define EP1(x) (ROTRIGHT(x, 14) ^ ROTRIGHT(x, 18) ^ ROTRIGHT(x, 41))

#define SIG0(x) (ROTRIGHT(x, 1) ^ ROTRIGHT(x, 8) ^ ((x) >> 7))
#define SIG1(x) (ROTRIGHT(x, 19) ^ ROTRIGHT(x, 61) ^ ((x) >> 6))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

static t_dword	g_k[] = {
	0x428A2F98D728AE22ULL, 0x7137449123EF65CDULL,
	0xB5C0FBCFEC4D3B2FULL, 0xE9B5DBA58189DBBCULL, 0x3956C25BF348B538ULL,
	0x59F111F1B605D019ULL, 0x923F82A4AF194F9BULL, 0xAB1C5ED5DA6D8118ULL,
	0xD807AA98A3030242ULL, 0x12835B0145706FBEULL, 0x243185BE4EE4B28CULL,
	0x550C7DC3D5FFB4E2ULL, 0x72BE5D74F27B896FULL, 0x80DEB1FE3B1696B1ULL,
	0x9BDC06A725C71235ULL, 0xC19BF174CF692694ULL, 0xE49B69C19EF14AD2ULL,
	0xEFBE4786384F25E3ULL, 0x0FC19DC68B8CD5B5ULL, 0x240CA1CC77AC9C65ULL,
	0x2DE92C6F592B0275ULL, 0x4A7484AA6EA6E483ULL, 0x5CB0A9DCBD41FBD4ULL,
	0x76F988DA831153B5ULL, 0x983E5152EE66DFABULL, 0xA831C66D2DB43210ULL,
	0xB00327C898FB213FULL, 0xBF597FC7BEEF0EE4ULL, 0xC6E00BF33DA88FC2ULL,
	0xD5A79147930AA725ULL, 0x06CA6351E003826FULL, 0x142929670A0E6E70ULL,
	0x27B70A8546D22FFCULL, 0x2E1B21385C26C926ULL, 0x4D2C6DFC5AC42AEDULL,
	0x53380D139D95B3DFULL, 0x650A73548BAF63DEULL, 0x766A0ABB3C77B2A8ULL,
	0x81C2C92E47EDAEE6ULL, 0x92722C851482353BULL, 0xA2BFE8A14CF10364ULL,
	0xA81A664BBC423001ULL, 0xC24B8B70D0F89791ULL, 0xC76C51A30654BE30ULL,
	0xD192E819D6EF5218ULL, 0xD69906245565A910ULL, 0xF40E35855771202AULL,
	0x106AA07032BBD1B8ULL, 0x19A4C116B8D2D0C8ULL, 0x1E376C085141AB53ULL,
	0x2748774CDF8EEB99ULL, 0x34B0BCB5E19B48A8ULL, 0x391C0CB3C5C95A63ULL,
	0x4ED8AA4AE3418ACBULL, 0x5B9CCA4F7763E373ULL, 0x682E6FF3D6B2B8A3ULL,
	0x748F82EE5DEFB2FCULL, 0x78A5636F43172F60ULL, 0x84C87814A1F0AB72ULL,
	0x8CC702081A6439ECULL, 0x90BEFFFA23631E28ULL, 0xA4506CEBDE82BDE9ULL,
	0xBEF9A3F7B2C67915ULL, 0xC67178F2E372532BULL, 0xCA273ECEEA26619CULL,
	0xD186B8C721C0C207ULL, 0xEADA7DD6CDE0EB1EULL, 0xF57D4F7FEE6ED178ULL,
	0x06F067AA72176FBAULL, 0x0A637DC5A2C898A6ULL, 0x113F9804BEF90DAEULL,
	0x1B710B35131C471BULL, 0x28DB77F523047D84ULL, 0x32CAAB7B40C72493ULL,
	0x3C9EBE0A15C9BEBCULL, 0x431D67C49C100D4CULL, 0x4CC5D4BECB3E42B6ULL,
	0x597F299CFC657E2AULL, 0x5FCB6FAB3AD6FAECULL, 0x6C44198C4A475817ULL
};

static void		initialize
(
	t_dword x[80],
	t_byte buffer[128],
	t_dword state[8],
	t_dword abcdefgh[8]
)
{
	int			i;

	bytes_to_big_endian_dwords(x, buffer, 128);
	i = 16;
	while (i < 80)
	{
		x[i] = SIG1(x[i - 2]) + x[i - 7] + SIG0(x[i - 15]) + x[i - 16];
		i++;
	}
	i = -1;
	while (++i < 8)
		abcdefgh[i] = state[i];
}

static void		add_new_state(t_dword state[8], t_dword new_state[8])
{
	int	i;

	i = -1;
	while (++i < 8)
		state[i] += new_state[i];
}

void			sha512_transform
(
	t_dword state[8],
	t_byte buffer[128]
)
{
	t_dword	x[80];
	t_dword	abcdefgh[8];
	t_dword	temp[2];
	int		i;

	initialize(x, buffer, state, abcdefgh);
	i = -1;
	while (++i < 80)
	{
		temp[0] = abcdefgh[7] + EP1(abcdefgh[4]) +
			CH(abcdefgh[4], abcdefgh[5], abcdefgh[6]) + g_k[i] + x[i];
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
