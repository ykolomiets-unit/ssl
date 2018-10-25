/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:10:10 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/25 21:10:11 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "ft_ssl.h"
#include "base64.h"
#include <unistd.h>

#define HZ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
#define IS_BASE64(ch, table) ((ch) > 0 && ((table)[ch] >= 0))
#define IS_WHITESPACE(ch) ((ch) == '\n' || (ch) == ' ' || (ch) == '\t')

static const char	g_b64[] = { HZ, HZ, HZ, HZ, -1, -1, -1,
	62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
	-1, -1, -1, -1, -1
};

static int			decode_last_part
(
	t_byte in[ENCODED_SIZE],
	uint32_t in_size,
	uint32_t in_pos,
	t_byte **out
)
{
	if (!IS_BASE64(in[in_pos + 2], g_b64))
		return (-1);
	**out = ((g_b64[in[in_pos + 1]] << 4) & 0xf0)
		| (g_b64[in[in_pos + 2]] >> 2);
	(*out)++;
	if (in_pos + 3 == in_size)
		return (-1);
	if (in[in_pos + 3] == '=')
	{
		if (in_pos + 4 != in_size)
			return (-1);
	}
	else
	{
		if (!IS_BASE64(in[in_pos + 3], g_b64))
			return (-1);
		**out = ((g_b64[in[in_pos + 2]] << 6) & 0xc0)
			| g_b64[in[in_pos + 3]];
		(*out)++;
	}
	return (0);
}

static int			base64_decode
(
	t_byte in[ENCODED_SIZE],
	uint32_t in_size,
	t_byte *out
)
{
	uint32_t	in_pos;
	t_byte		*start;

	start = out;
	in_pos = 0;
	while (in_pos + 2 < in_size)
	{
		if (!IS_BASE64(in[in_pos], g_b64) || !IS_BASE64(in[in_pos + 1], g_b64))
			return (-1);
		*out++ = (g_b64[in[in_pos]] << 2) | (g_b64[in[in_pos + 1]] >> 4); 
		if (in_pos + 2 == in_size)
			return (-1);
		if (in[in_pos + 2] == '=')
		{
			if (in_pos + 4 != in_size || in[in_pos + 3] != '=')
				return (-1);
		}
		else
		{
			if (decode_last_part(in, in_size, in_pos, &out))
				return (-1);
		}
		in_pos += 4;
	}
	return (out - start);
}

static int			filter_buffer(t_byte *buffer, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (!(buffer[i] == ' ' || buffer[i] == '\n'))
		{
			buffer[j] = buffer[i];
			j++;
		}
		i++;
	}
	return (j);
}

int					base64_decode_file_to_file
(
	int input,
	int output
)
{
	int			r;
	uint32_t	in_buf;
	t_byte		input_buffer[ENCODED_SIZE];
	int 		w;
	t_byte		output_buffer[DECODED_SIZE];

	r = 0;
	in_buf = 0;
	while ((r = read(input, input_buffer + in_buf, ENCODED_SIZE - in_buf)) > 0)
	{
		in_buf += filter_buffer(input_buffer + in_buf, r);
		if (in_buf != ENCODED_SIZE)
			continue ;
		if ((w = base64_decode(input_buffer, ENCODED_SIZE, output_buffer)) < 0)
			return (error("Invalid character in input stream"));
		write(output, output_buffer, w);
		in_buf = 0;
	}
	if (in_buf)
	{
		if ((w = base64_decode(input_buffer, in_buf, output_buffer)) < 0)
			return (error("Invalid character in input stream"));
		write(output, output_buffer, w);
	}
	return (0);
}
