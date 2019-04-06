#include "t.h"
#include "test_groups.h"

int main()
{
	RUN_GROUP(hmac_tests);
	RUN_GROUP(pbkdf2_tests);
}
