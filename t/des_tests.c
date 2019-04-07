#include "t.h"
#include "test_groups.h"
#include "des.h"

int	move_bit()
{
	uint64_t v = 0x10;


	uint64_t res = MOVE_BIT(v, 4, 12);
	uint64_t expected = 0x1 << 12;
	if (res != expected)
		return (1);
	return (0);
}

int  pc1()
{
	uint64_t	key = 0x133457799BBCDFF1;
	uint64_t	expected = 0xF0CCAAF556678F00;

	uint64_t	res = apply_pc1(key);
	ft_printf("\nKEY: %.32b%.32b\n", key >> 32, key);
	ft_printf("\nRES: %.32b%.32b\n", res >> 32, res);
	ft_printf("\nEXP: %.32b%.32b\n", expected >> 32, expected);
	if (res != expected)
		return (1);
	return (0);
}

int	des_tests()
{
	RUN_TEST(move_bit);
	RUN_TEST(pc1);
}
