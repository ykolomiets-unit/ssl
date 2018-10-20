/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:36:17 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:36:19 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define END(a, s, b) (a) = ROTATE_LEFT ((a), (s)) + (b);
#define FF_C(a, b, c, d, x, ac) (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac);
#define GG_C(a, b, c, d, x, ac) (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac);
#define HH_C(a, b, c, d, x, ac) (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac);
#define II_C(a, b, c, d, x, ac) (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac);

#define FF(a, b, c, d, x, s, ac) FF_C(a, b, c, d, x, ac) END(a, s, b)
#define GG(a, b, c, d, x, s, ac) GG_C(a, b, c, d, x, ac) END(a, s, b)
#define HH(a, b, c, d, x, s, ac) HH_C(a, b, c, d, x, ac) END(a, s, b)
#define II(a, b, c, d, x, s, ac) II_C(a, b, c, d, x, ac) END(a, s, b)

static void	first_round
(
	t_word abcd[4],
	t_word block[16]
)
{
	FF(abcd[0], abcd[1], abcd[2], abcd[3], block[0], S11, 0xd76aa478);
	FF(abcd[3], abcd[0], abcd[1], abcd[2], block[1], S12, 0xe8c7b756);
	FF(abcd[2], abcd[3], abcd[0], abcd[1], block[2], S13, 0x242070db);
	FF(abcd[1], abcd[2], abcd[3], abcd[0], block[3], S14, 0xc1bdceee);
	FF(abcd[0], abcd[1], abcd[2], abcd[3], block[4], S11, 0xf57c0faf);
	FF(abcd[3], abcd[0], abcd[1], abcd[2], block[5], S12, 0x4787c62a);
	FF(abcd[2], abcd[3], abcd[0], abcd[1], block[6], S13, 0xa8304613);
	FF(abcd[1], abcd[2], abcd[3], abcd[0], block[7], S14, 0xfd469501);
	FF(abcd[0], abcd[1], abcd[2], abcd[3], block[8], S11, 0x698098d8);
	FF(abcd[3], abcd[0], abcd[1], abcd[2], block[9], S12, 0x8b44f7af);
	FF(abcd[2], abcd[3], abcd[0], abcd[1], block[10], S13, 0xffff5bb1);
	FF(abcd[1], abcd[2], abcd[3], abcd[0], block[11], S14, 0x895cd7be);
	FF(abcd[0], abcd[1], abcd[2], abcd[3], block[12], S11, 0x6b901122);
	FF(abcd[3], abcd[0], abcd[1], abcd[2], block[13], S12, 0xfd987193);
	FF(abcd[2], abcd[3], abcd[0], abcd[1], block[14], S13, 0xa679438e);
	FF(abcd[1], abcd[2], abcd[3], abcd[0], block[15], S14, 0x49b40821);
}

static void	second_round
(
	t_word abcd[4],
	t_word block[16]
)
{
	GG(abcd[0], abcd[1], abcd[2], abcd[3], block[1], S21, 0xf61e2562);
	GG(abcd[3], abcd[0], abcd[1], abcd[2], block[6], S22, 0xc040b340);
	GG(abcd[2], abcd[3], abcd[0], abcd[1], block[11], S23, 0x265e5a51);
	GG(abcd[1], abcd[2], abcd[3], abcd[0], block[0], S24, 0xe9b6c7aa);
	GG(abcd[0], abcd[1], abcd[2], abcd[3], block[5], S21, 0xd62f105d);
	GG(abcd[3], abcd[0], abcd[1], abcd[2], block[10], S22, 0x2441453);
	GG(abcd[2], abcd[3], abcd[0], abcd[1], block[15], S23, 0xd8a1e681);
	GG(abcd[1], abcd[2], abcd[3], abcd[0], block[4], S24, 0xe7d3fbc8);
	GG(abcd[0], abcd[1], abcd[2], abcd[3], block[9], S21, 0x21e1cde6);
	GG(abcd[3], abcd[0], abcd[1], abcd[2], block[14], S22, 0xc33707d6);
	GG(abcd[2], abcd[3], abcd[0], abcd[1], block[3], S23, 0xf4d50d87);
	GG(abcd[1], abcd[2], abcd[3], abcd[0], block[8], S24, 0x455a14ed);
	GG(abcd[0], abcd[1], abcd[2], abcd[3], block[13], S21, 0xa9e3e905);
	GG(abcd[3], abcd[0], abcd[1], abcd[2], block[2], S22, 0xfcefa3f8);
	GG(abcd[2], abcd[3], abcd[0], abcd[1], block[7], S23, 0x676f02d9);
	GG(abcd[1], abcd[2], abcd[3], abcd[0], block[12], S24, 0x8d2a4c8a);
}

static void	third_round
(
	t_word abcd[4],
	t_word block[16]
)
{
	HH(abcd[0], abcd[1], abcd[2], abcd[3], block[5], S31, 0xfffa3942);
	HH(abcd[3], abcd[0], abcd[1], abcd[2], block[8], S32, 0x8771f681);
	HH(abcd[2], abcd[3], abcd[0], abcd[1], block[11], S33, 0x6d9d6122);
	HH(abcd[1], abcd[2], abcd[3], abcd[0], block[14], S34, 0xfde5380c);
	HH(abcd[0], abcd[1], abcd[2], abcd[3], block[1], S31, 0xa4beea44);
	HH(abcd[3], abcd[0], abcd[1], abcd[2], block[4], S32, 0x4bdecfa9);
	HH(abcd[2], abcd[3], abcd[0], abcd[1], block[7], S33, 0xf6bb4b60);
	HH(abcd[1], abcd[2], abcd[3], abcd[0], block[10], S34, 0xbebfbc70);
	HH(abcd[0], abcd[1], abcd[2], abcd[3], block[13], S31, 0x289b7ec6);
	HH(abcd[3], abcd[0], abcd[1], abcd[2], block[0], S32, 0xeaa127fa);
	HH(abcd[2], abcd[3], abcd[0], abcd[1], block[3], S33, 0xd4ef3085);
	HH(abcd[1], abcd[2], abcd[3], abcd[0], block[6], S34, 0x4881d05);
	HH(abcd[0], abcd[1], abcd[2], abcd[3], block[9], S31, 0xd9d4d039);
	HH(abcd[3], abcd[0], abcd[1], abcd[2], block[12], S32, 0xe6db99e5);
	HH(abcd[2], abcd[3], abcd[0], abcd[1], block[15], S33, 0x1fa27cf8);
	HH(abcd[1], abcd[2], abcd[3], abcd[0], block[2], S34, 0xc4ac5665);
}

static void	fourth_round
(
	t_word abcd[4],
	t_word block[16]
)
{
	II(abcd[0], abcd[1], abcd[2], abcd[3], block[0], S41, 0xf4292244);
	II(abcd[3], abcd[0], abcd[1], abcd[2], block[7], S42, 0x432aff97);
	II(abcd[2], abcd[3], abcd[0], abcd[1], block[14], S43, 0xab9423a7);
	II(abcd[1], abcd[2], abcd[3], abcd[0], block[5], S44, 0xfc93a039);
	II(abcd[0], abcd[1], abcd[2], abcd[3], block[12], S41, 0x655b59c3);
	II(abcd[3], abcd[0], abcd[1], abcd[2], block[3], S42, 0x8f0ccc92);
	II(abcd[2], abcd[3], abcd[0], abcd[1], block[10], S43, 0xffeff47d);
	II(abcd[1], abcd[2], abcd[3], abcd[0], block[1], S44, 0x85845dd1);
	II(abcd[0], abcd[1], abcd[2], abcd[3], block[8], S41, 0x6fa87e4f);
	II(abcd[3], abcd[0], abcd[1], abcd[2], block[15], S42, 0xfe2ce6e0);
	II(abcd[2], abcd[3], abcd[0], abcd[1], block[6], S43, 0xa3014314);
	II(abcd[1], abcd[2], abcd[3], abcd[0], block[13], S44, 0x4e0811a1);
	II(abcd[0], abcd[1], abcd[2], abcd[3], block[4], S41, 0xf7537e82);
	II(abcd[3], abcd[0], abcd[1], abcd[2], block[11], S42, 0xbd3af235);
	II(abcd[2], abcd[3], abcd[0], abcd[1], block[2], S43, 0x2ad7d2bb);
	II(abcd[1], abcd[2], abcd[3], abcd[0], block[9], S44, 0xeb86d391);
}

void		md5_transform
(
	t_word state[4],
	t_byte buffer[64]
)
{
	uint32_t	abcd[4];
	uint32_t	x[16];
	int			i;

	i = -1;
	while (++i < 4)
		abcd[i] = state[i];
	bytes_to_little_endian_words(x, buffer, 64);
	first_round(abcd, x);
	second_round(abcd, x);
	third_round(abcd, x);
	fourth_round(abcd, x);
	i = -1;
	while (++i < 4)
		state[i] += abcd[i];
}
