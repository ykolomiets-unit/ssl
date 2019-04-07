#include "t.h"
#include "test_groups.h"
#include  "des.h"

int main()
{
	int a;

	a = 9;

	RUN_GROUP(hmac_tests);
	RUN_GROUP(pbkdf2_tests);
	RUN_GROUP(des_tests);
}
