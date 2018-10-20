/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:34:07 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:35:14 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"
#include "utils.h"

void		md5_init
(
	t_md5_context *context
)
{
	context->count = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
	ft_bzero(context->buffer, 64);
}

void		md5_update
(
	t_md5_context *context,
	char *input,
	uint32_t input_len
)
{
	uint32_t	i;
	uint32_t	index;
	uint32_t	part_len;

	i = 0;
	index = (context->count / 8) % 64;
	context->count += input_len * 8;
	part_len = 64 - index;
	if (input_len >= part_len)
	{
		ft_memcpy(&context->buffer[index], input, part_len);
		md5_transform(context->state, context->buffer);
		i = part_len;
		while (i + 63 < input_len)
		{
			md5_transform(context->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	ft_memcpy(&context->buffer[index], &input[i], input_len - i);
}

static void	length_to_bytes
(
	uint64_t length,
	char bytes[8]
)
{
	bytes[0] = length & 0xff;
	bytes[1] = (length >> 8) & 0xff;
	bytes[2] = (length >> 16) & 0xff;
	bytes[3] = (length >> 24) & 0xff;
	bytes[4] = (length >> 32) & 0xff;
	bytes[5] = (length >> 40) & 0xff;
	bytes[6] = (length >> 48) & 0xff;
	bytes[7] = (length >> 56) & 0xff;
}

void		md5_final
(
	t_md5_context *context,
	unsigned char digest[16]
)
{
	static char padding[64] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0 };
	char		bits_amount[8];
	uint32_t	index;
	uint32_t	pad_len;

	length_to_bytes(context->count, bits_amount);
	index = (context->count / 8) % 64;
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, padding, pad_len);
	md5_update(context, bits_amount, 8);
	low_order_words_to_bytes(context->state, (char *)digest, 16);
}
