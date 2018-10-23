/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:20:10 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/22 20:20:12 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <unistd.h>

#define HZ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
#define IS_BASE64(ch, table) ((ch) > 0 && ((table)[ch] >= 0))

#define IN_BLOCK_SIZE 300
#define OUT_BLOCK_SIZE 400
#define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

uint32_t	base64_encode
(
	t_byte in[IN_BLOCK_SIZE],
	uint32_t in_size,
	t_byte out[OUT_BLOCK_SIZE]
)
{
	static char	b64[] = B64;
	uint32_t	in_pos;
	uint32_t	out_pos;
	t_byte		temp;

	in_pos = 0;
	out_pos = 0;
	while (in_pos < in_size)
	{
		out[out_pos++] = b64[(in[in_pos] >> 2) & 0x3f];
		temp = ((in[in_pos] << 4) |
			(in_pos + 1 < in_size ? in[in_pos + 1] >> 4 : 0)) & 0x3f;
		out[out_pos++] = b64[temp];
		if (in_pos + 1 < in_size)
			temp = ((in[in_pos + 1] << 2) |
				((in_pos + 2 < in_size) ? in[in_pos + 2] >> 6 : 0)) & 0x3f;
		else
			temp = 64;
		out[out_pos++] = b64[temp];
		out[out_pos++] = b64[in_pos + 2 < in_size ? in[in_pos + 2] & 0x3f : 64];
		in_pos += 3;
	}
	return (out_pos);
}

static char	*get_b64(void)
{
	static char	b64[] = { HZ, HZ, HZ, HZ, -1, -1, -1,
		62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4,
		5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
		-1, -1, -1, -1, -1 };

	return (b64);
}

void		base64_encode_file_to_file
(
	int input,
	int output
)
{
	int			r;
	uint32_t	in_buf;
	t_byte		input_buffer[IN_BLOCK_SIZE];
	uint32_t	w;
	t_byte		output_buffer[OUT_BLOCK_SIZE];

	r = 0;
	in_buf = 0;
	while ((r = read(input, input_buffer + in_buf, IN_BLOCK_SIZE - in_buf)) > 0)
	{
		in_buf += r;
		if (in_buf == IN_BLOCK_SIZE)
		{
			w = base64_encode(input_buffer, IN_BLOCK_SIZE, output_buffer);
			write(output, output_buffer, w);
			in_buf = 0;
		}
	}
	if (in_buf)
	{
		w = base64_encode(input_buffer, in_buf, output_buffer);
		write(output, output_buffer, w);
	}
	ft_putchar_fd('\0', output);
}

uint32_t	base64_decode
(
	t_byte in[OUT_BLOCK_SIZE],
	uint32_t in_size,
	t_byte out[IN_BLOCK_SIZE]
)
{
	char		*b64;
	uint32_t	in_pos;
	uint32_t	out_pos;

	b64 = get_b64();
	in_pos = 0;
	out_pos = 0;
	while (in_pos + 2 < in_size)
	{
		if (!IS_BASE64(in[in_pos], b64) || !IS_BASE64(in[in_pos + 1], b64))
			break ;
		out[out_pos++] = (b64[in[in_pos]] << 2) | (b64[in[in_pos + 1]] >> 4); 
		if (in_pos + 2 == in_size)
			break ;
		if (in[in_pos + 2] == '=')
		{
			if (in_pos + 4 != in_size || in[in_pos + 3] != '=')
				break ;
		}
		else
		{
			if (!IS_BASE64(in[in_pos + 2], b64))
				break ;
			out[out_pos++] = ((b64[in[in_pos + 1]] << 4) & 0xf0)
				| (b64[in[in_pos + 2]] >> 2);
			if (in_pos + 3 == in_size)
				break ;
			if (in[in_pos + 3] == '=')
			{
				if (in_pos + 4 != in_size)
					break ;
			}
			else
			{
				if (!IS_BASE64(in[in_pos + 3], b64))
					break ;
				out[out_pos++] = ((b64[in[in_pos + 2]] << 6) & 0xc0)
					| b64[in[in_pos + 3]];
			}
		}
		in_pos += 4;
	}
	return (0);
}

void		base64_decode_file_to_file
(
	int input,
	int output
)
{
	int			r;
	uint32_t	in_buf;
	t_byte		input_buffer[OUT_BLOCK_SIZE];
	uint32_t	w;
	t_byte		output_buffer[IN_BLOCK_SIZE];

	r = 0;
	in_buf = 0;
	while ((r = read(input, input_buffer + in_buf, IN_BLOCK_SIZE - in_buf)) > 0)
	{
		in_buf += r;
		if (in_buf == OUT_BLOCK_SIZE)
		{
			w = base64_decode(input_buffer, OUT_BLOCK_SIZE, output_buffer);
			write(output, output_buffer, w);
			in_buf = 0;
		}
	}
	if (in_buf)
	{
		w = base64_encode(input_buffer, in_buf, output_buffer);
		write(output, output_buffer, w);
	}
	ft_putchar_fd('\0', output);
}