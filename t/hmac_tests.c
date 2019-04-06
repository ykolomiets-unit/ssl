#include "t.h"
#include "test_groups.h"
#include "hmac_sha256.h"
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

static int	test1()
{
	t_hmac_params	params;
	t_byte 			result[SHA256_DIGEST_SIZE];

	params.key = (t_byte *)"";
	params.key_length = 0;
	params.message = (t_byte*)"";
	params.message_length = 0;
	hmac_sha256(params, result);
	char *converted = convert_digest_to_string(result, SHA256_DIGEST_SIZE);
	if (ft_strcmp(converted, "b613679a0814d9ec772f95d778c35fc5ff1697c493715653c6c712144292c5ad"))
		return 1;
	return 0;
}

static int	test2()
{
	t_hmac_params	params;
	t_byte 			result[SHA256_DIGEST_SIZE];

	params.key = (t_byte *)"key";
	params.key_length = ft_strlen((char *)params.key);
	params.message = (t_byte*)"The quick brown fox jumps over the lazy dog";
	params.message_length = ft_strlen((char *)params.message);
	hmac_sha256(params, result);
	char *converted = convert_digest_to_string(result, SHA256_DIGEST_SIZE);
	if (ft_strcmp(converted, "f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8"))
		return 1;
	return 0;
}

static int	test3()
{
	t_hmac_params	params;
	t_byte 			result[SHA256_DIGEST_SIZE];

	params.key = (t_byte *)"password";
	params.key_length = ft_strlen((char *)params.key);
	t_byte message[] = {'s', 'a', 'l', 't', 0, 0, 0, 1};
	params.message = message;
	params.message_length = sizeof(message);
	hmac_sha256(params, result);
	char *converted = convert_digest_to_string(result, SHA256_DIGEST_SIZE);
	if (ft_strcmp(converted, "120fb6cffcf8b32c43e7225256c4f837a86548c92ccc35480805987cb70be17b"))
		return 1;
	return 0;
}

int hmac_tests()
{
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	return 0;
}
