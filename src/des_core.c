#include "des.h"
#include "utils.h"

static const int	g_ip[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

static const int	g_fp[64] = {
	40,  8, 48, 16, 56, 24, 64, 32,
	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,
	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,
	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,
	33,  1, 41,  9, 49, 17, 57, 25
};

static const int	g_expansion[48] = {
	32,	 1,  2,  3,  4,  5,  4,  5,
	 6,  7,  8,  9,  8,  9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32,  1
};

static const int	g_sboxes[8][64] = {
	{
		0xe0000000, 0x00000000, 0x40000000, 0xf0000000, 
		0xd0000000, 0x70000000, 0x10000000, 0x40000000, 
		0x20000000, 0xe0000000, 0xf0000000, 0x20000000, 
		0xb0000000, 0xd0000000, 0x80000000, 0x10000000, 
		0x30000000, 0xa0000000, 0xa0000000, 0x60000000, 
		0x60000000, 0xc0000000, 0xc0000000, 0xb0000000, 
		0x50000000, 0x90000000, 0x90000000, 0x50000000, 
		0x00000000, 0x30000000, 0x70000000, 0x80000000, 
		0x40000000, 0xf0000000, 0x10000000, 0xc0000000, 
		0xe0000000, 0x80000000, 0x80000000, 0x20000000, 
		0xd0000000, 0x40000000, 0x60000000, 0x90000000, 
		0x20000000, 0x10000000, 0xb0000000, 0x70000000, 
		0xf0000000, 0x50000000, 0xc0000000, 0xb0000000, 
		0x90000000, 0x30000000, 0x70000000, 0xe0000000, 
		0x30000000, 0xa0000000, 0xa0000000, 0x00000000, 
		0x50000000, 0x60000000, 0x00000000, 0xd0000000
	},
	{
		0x0f000000, 0x03000000, 0x01000000, 0x0d000000, 
		0x08000000, 0x04000000, 0x0e000000, 0x07000000, 
		0x06000000, 0x0f000000, 0x0b000000, 0x02000000, 
		0x03000000, 0x08000000, 0x04000000, 0x0e000000, 
		0x09000000, 0x0c000000, 0x07000000, 0x00000000, 
		0x02000000, 0x01000000, 0x0d000000, 0x0a000000, 
		0x0c000000, 0x06000000, 0x00000000, 0x09000000, 
		0x05000000, 0x0b000000, 0x0a000000, 0x05000000, 
		0x00000000, 0x0d000000, 0x0e000000, 0x08000000, 
		0x07000000, 0x0a000000, 0x0b000000, 0x01000000, 
		0x0a000000, 0x03000000, 0x04000000, 0x0f000000, 
		0x0d000000, 0x04000000, 0x01000000, 0x02000000, 
		0x05000000, 0x0b000000, 0x08000000, 0x06000000, 
		0x0c000000, 0x07000000, 0x06000000, 0x0c000000, 
		0x09000000, 0x00000000, 0x03000000, 0x05000000, 
		0x02000000, 0x0e000000, 0x0f000000, 0x09000000 
	},
	{
		0x00a00000, 0x00d00000, 0x00000000, 0x00700000, 
		0x00900000, 0x00000000, 0x00e00000, 0x00900000, 
		0x00600000, 0x00300000, 0x00300000, 0x00400000, 
		0x00f00000, 0x00600000, 0x00500000, 0x00a00000, 
		0x00100000, 0x00200000, 0x00d00000, 0x00800000, 
		0x00c00000, 0x00500000, 0x00700000, 0x00e00000, 
		0x00b00000, 0x00c00000, 0x00400000, 0x00b00000, 
		0x00200000, 0x00f00000, 0x00800000, 0x00100000, 
		0x00d00000, 0x00100000, 0x00600000, 0x00a00000, 
		0x00400000, 0x00d00000, 0x00900000, 0x00000000, 
		0x00800000, 0x00600000, 0x00f00000, 0x00900000, 
		0x00300000, 0x00800000, 0x00000000, 0x00700000, 
		0x00b00000, 0x00400000, 0x00100000, 0x00f00000, 
		0x00200000, 0x00e00000, 0x00c00000, 0x00300000, 
		0x00500000, 0x00b00000, 0x00a00000, 0x00500000, 
		0x00e00000, 0x00200000, 0x00700000, 0x00c00000 
	},
	{
		0x00070000, 0x000d0000, 0x000d0000, 0x00080000, 
		0x000e0000, 0x000b0000, 0x00030000, 0x00050000, 
		0x00000000, 0x00060000, 0x00060000, 0x000f0000, 
		0x00090000, 0x00000000, 0x000a0000, 0x00030000, 
		0x00010000, 0x00040000, 0x00020000, 0x00070000, 
		0x00080000, 0x00020000, 0x00050000, 0x000c0000, 
		0x000b0000, 0x00010000, 0x000c0000, 0x000a0000, 
		0x00040000, 0x000e0000, 0x000f0000, 0x00090000, 
		0x000a0000, 0x00030000, 0x00060000, 0x000f0000, 
		0x00090000, 0x00000000, 0x00000000, 0x00060000, 
		0x000c0000, 0x000a0000, 0x000b0000, 0x00010000, 
		0x00070000, 0x000d0000, 0x000d0000, 0x00080000, 
		0x000f0000, 0x00090000, 0x00010000, 0x00040000, 
		0x00030000, 0x00050000, 0x000e0000, 0x000b0000, 
		0x00050000, 0x000c0000, 0x00020000, 0x00070000, 
		0x00080000, 0x00020000, 0x00040000, 0x000e0000 
	},
	{
		0x00002000, 0x0000e000, 0x0000c000, 0x0000b000, 
		0x00004000, 0x00002000, 0x00001000, 0x0000c000, 
		0x00007000, 0x00004000, 0x0000a000, 0x00007000, 
		0x0000b000, 0x0000d000, 0x00006000, 0x00001000, 
		0x00008000, 0x00005000, 0x00005000, 0x00000000, 
		0x00003000, 0x0000f000, 0x0000f000, 0x0000a000, 
		0x0000d000, 0x00003000, 0x00000000, 0x00009000, 
		0x0000e000, 0x00008000, 0x00009000, 0x00006000, 
		0x00004000, 0x0000b000, 0x00002000, 0x00008000, 
		0x00001000, 0x0000c000, 0x0000b000, 0x00007000, 
		0x0000a000, 0x00001000, 0x0000d000, 0x0000e000, 
		0x00007000, 0x00002000, 0x00008000, 0x0000d000, 
		0x0000f000, 0x00006000, 0x00009000, 0x0000f000, 
		0x0000c000, 0x00000000, 0x00005000, 0x00009000, 
		0x00006000, 0x0000a000, 0x00003000, 0x00004000, 
		0x00000000, 0x00005000, 0x0000e000, 0x00003000 
	},
	{
		0x00000c00, 0x00000a00, 0x00000100, 0x00000f00, 
		0x00000a00, 0x00000400, 0x00000f00, 0x00000200, 
		0x00000900, 0x00000700, 0x00000200, 0x00000c00, 
		0x00000600, 0x00000900, 0x00000800, 0x00000500, 
		0x00000000, 0x00000600, 0x00000d00, 0x00000100, 
		0x00000300, 0x00000d00, 0x00000400, 0x00000e00, 
		0x00000e00, 0x00000000, 0x00000700, 0x00000b00, 
		0x00000500, 0x00000300, 0x00000b00, 0x00000800, 
		0x00000900, 0x00000400, 0x00000e00, 0x00000300, 
		0x00000f00, 0x00000200, 0x00000500, 0x00000c00, 
		0x00000200, 0x00000900, 0x00000800, 0x00000500, 
		0x00000c00, 0x00000f00, 0x00000300, 0x00000a00, 
		0x00000700, 0x00000b00, 0x00000000, 0x00000e00, 
		0x00000400, 0x00000100, 0x00000a00, 0x00000700, 
		0x00000100, 0x00000600, 0x00000d00, 0x00000000, 
		0x00000b00, 0x00000800, 0x00000600, 0x00000d00
	},
	{
		0x00000040, 0x000000d0, 0x000000b0, 0x00000000, 
		0x00000020, 0x000000b0, 0x000000e0, 0x00000070, 
		0x000000f0, 0x00000040, 0x00000000, 0x00000090, 
		0x00000080, 0x00000010, 0x000000d0, 0x000000a0, 
		0x00000030, 0x000000e0, 0x000000c0, 0x00000030, 
		0x00000090, 0x00000050, 0x00000070, 0x000000c0, 
		0x00000050, 0x00000020, 0x000000a0, 0x000000f0, 
		0x00000060, 0x00000080, 0x00000010, 0x00000060, 
		0x00000010, 0x00000060, 0x00000040, 0x000000b0, 
		0x000000b0, 0x000000d0, 0x000000d0, 0x00000080, 
		0x000000c0, 0x00000010, 0x00000030, 0x00000040, 
		0x00000070, 0x000000a0, 0x000000e0, 0x00000070, 
		0x000000a0, 0x00000090, 0x000000f0, 0x00000050, 
		0x00000060, 0x00000000, 0x00000080, 0x000000f0, 
		0x00000000, 0x000000e0, 0x00000050, 0x00000020, 
		0x00000090, 0x00000030, 0x00000020, 0x000000c0 
	},
	{
		0x0000000d, 0x00000001, 0x00000002, 0x0000000f, 
		0x00000008, 0x0000000d, 0x00000004, 0x00000008, 
		0x00000006, 0x0000000a, 0x0000000f, 0x00000003, 
		0x0000000b, 0x00000007, 0x00000001, 0x00000004, 
		0x0000000a, 0x0000000c, 0x00000009, 0x00000005, 
		0x00000003, 0x00000006, 0x0000000e, 0x0000000b, 
		0x00000005, 0x00000000, 0x00000000, 0x0000000e, 
		0x0000000c, 0x00000009, 0x00000007, 0x00000002, 
		0x00000007, 0x00000002, 0x0000000b, 0x00000001, 
		0x00000004, 0x0000000e, 0x00000001, 0x00000007, 
		0x00000009, 0x00000004, 0x0000000c, 0x0000000a, 
		0x0000000e, 0x00000008, 0x00000002, 0x0000000d, 
		0x00000000, 0x0000000f, 0x00000006, 0x0000000c, 
		0x0000000a, 0x00000009, 0x0000000d, 0x00000000, 
		0x0000000f, 0x00000003, 0x00000003, 0x00000005, 
		0x00000005, 0x00000006, 0x00000008, 0x0000000b
	}
};

static const int	g_pbox[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};

uint64_t	apply_ip(uint64_t m)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = 1;
	while (i <= 64)
	{
		res |= MOVE_BIT(m, g_ip[i - 1], i);
		i++;
	}
	return (res);
}

uint64_t	expand(uint64_t m)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = 1;
	while (i <= 48)
	{
		res |= MOVE_BIT(m, g_expansion[i - 1], i);
		i++;
	}
	return (res);
}

uint64_t	substitude(uint64_t m)
{
	uint64_t	res;
	int			i;
	
	res = 0;
	i = 0;
	while (i < 8)
	{
		res |= g_sboxes[i][(m >> 58) & 0x3F];
		m <<= 6;
		i++;
	}
	res <<= 32;
	return (res);
}

uint64_t	permute(uint64_t m)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = 1;
	while (i <= 32)
	{
		res |= MOVE_BIT(m, g_pbox[i - 1], i);
		i++;
	}
	return (res);
}

uint64_t	apply_fp(uint64_t m)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = 1;
	while (i <= 64)
	{
		res |= MOVE_BIT(m, g_fp[i - 1], i);
		i++;
	}
	return (res);
}

void	des_core(uint64_t keys[16], t_byte input[DES_BLOCK_SIZE], t_byte output[DES_BLOCK_SIZE])
{
	uint64_t	m;
	uint64_t	left;
	uint64_t	right;
	uint64_t	temp;
	int			i;

	bytes_to_big_endian_dwords(&m, input, DES_BLOCK_SIZE);
	m = apply_ip(m);
	left = m & 0xFFFFFFFF00000000;
	right = m << 32;
	i = 0;
	while (i < 16)
	{
		temp = permute(substitude(expand(right) ^ keys[i])) ^ left;
		left = right;
		right = temp;
		i++;
	}
	m = right | (left >> 32);
	m = apply_fp(m);
	big_endian_dword_to_bytes(m, output);
}
