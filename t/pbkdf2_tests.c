#include "t.h"
#include "test_groups.h"
#include "pbkdf2.h"
#include <stdlib.h>

static char*	convert_digest_to_string(t_byte *digest, int digest_size)
{
	static	char hex[] = "0123456789abcdef";
	char	*res;
	
	res = (char *)malloc(digest_size * 2 + 1);
	for (int i = 0; i < digest_size; i++)
	{
		res[i * 2] = hex[digest[i] / 16];
		res[i * 2 + 1] = hex[digest[i] % 16];
	}
	res[digest_size * 2] = '\0';
	return res;
}

static int test1()
{
	t_pbkdf2_params params;
	t_byte			result[32];

	params.password = (t_byte *)"password";
	params.password_length = ft_strlen((char *)params.password);
	params.salt = (t_byte *)"salt";
	params.salt_length = ft_strlen((char *)params.salt);
	params.iteration_count = 1;
	pbkdf2(params, result, 32);
	char *converted = convert_digest_to_string(result, 32);
	if (ft_strcmp(converted, "120fb6cffcf8b32c43e7225256c4f837a86548c92ccc35480805987cb70be17b"))
		return 1;
	return 0;
}

static int test2()
{
	t_pbkdf2_params params;
	t_byte			result[32];

	params.password = (t_byte *)"password";
	params.password_length = ft_strlen((char *)params.password);
	params.salt = (t_byte *)"salt";
	params.salt_length = ft_strlen((char *)params.salt);
	params.iteration_count = 2;
	pbkdf2(params, result, 32);
	char *converted = convert_digest_to_string(result, 32);
	if (ft_strcmp(converted, "ae4d0c95af6b46d32d0adff928f06dd02a303f8ef3c251dfd6e2d85a95474c43"))
		return 1;
	return 0;
}

static int test3()
{
	t_pbkdf2_params params;
	t_byte			result[32];

	params.password = (t_byte *)"password";
	params.password_length = ft_strlen((char *)params.password);
	params.salt = (t_byte *)"salt";
	params.salt_length = ft_strlen((char *)params.salt);
	params.iteration_count = 4096;
	pbkdf2(params, result, 32);
	char *converted = convert_digest_to_string(result, 32);
	if (ft_strcmp(converted, "c5e478d59288c841aa530db6845c4c8d962893a001ce4e11a4963873aa98134a"))
		return 1;
	return 0;
}

static int test4()
{
	t_pbkdf2_params params;
	t_byte			result[40];

	params.password = (t_byte *)"passwordPASSWORDpassword";
	params.password_length = ft_strlen((char *)params.password);
	params.salt = (t_byte *)"saltSALTsaltSALTsaltSALTsaltSALTsalt";
	params.salt_length = ft_strlen((char *)params.salt);
	params.iteration_count = 4096;
	pbkdf2(params, result, 40);
	char *converted = convert_digest_to_string(result, 40);
	if (ft_strcmp(converted, "348c89dbcbd32b2f32d814b8116e84cf2b17347ebc1800181c4e2a1fb8dd53e1c635518c7dac47e9"))
		return 1;
	return 0;
}

static int test5()
{
	t_pbkdf2_params params;
	t_byte			result[16];

	params.password = (t_byte *)"pass\0word";
	params.password_length = 9;
	params.salt = (t_byte *)"sa\0lt";
	params.salt_length = 5;
	params.iteration_count = 4096;
	pbkdf2(params, result, 16);
	char *converted = convert_digest_to_string(result, 16);
	if (ft_strcmp(converted, "89b69d0516f829893c696226650a8687"))
		return 1;
	return 0;
}

int pbkdf2_tests()
{
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	RUN_TEST(test4);
	RUN_TEST(test5);
	return 0;
}
