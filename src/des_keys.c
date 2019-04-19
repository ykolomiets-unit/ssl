#include "des.h"
#include "libft.h"

static const int g_pc1[56] = {
	57, 49, 41, 33, 25, 17,  9,
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};

static const int g_rotations[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

static const int g_pc2[48] = {
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};


static uint64_t	apply_pc1(uint64_t key)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = 1;
	while (i <= 56)
	{
		res |= MOVEBIT(key, g_pc1[i - 1], i); 
		i++;
	}
	return (res);
}

static uint64_t	apply_pc2(uint64_t c, uint64_t d)
{
	uint64_t	temp;
	uint64_t	res;
	int			i;

	temp = (c << 36) | (d << 8);
	res = 0;
	i = 1;
	while (i <= 48)
	{
		uint64_t t = MOVEBIT(temp, g_pc2[i - 1], i);
		res |= t;
		i++;
	}
	return (res);
}

void	des_key_schedule(uint64_t key, uint64_t subkeys[16], t_bool encode)
{
	uint32_t	c;
	uint32_t	d;
	int			i;
	uint64_t	temp;

	key = apply_pc1(key);
	c = key >> 36;
	d = (key >> 8) & 0xFFFFFFF;
	i = 1;
	while (i <= 16)
	{
		c = ROL28(c, g_rotations[i - 1]);
		d = ROL28(d, g_rotations[i - 1]);
		subkeys[i - 1] = apply_pc2(c, d);
		i++;
	}
	if (!encode) {
		i = -1;
		while (++i < 8) {
			temp = subkeys[i];
			subkeys[i] = subkeys[15 - i];
			subkeys[15 - i] = temp;
		}
	}
}
