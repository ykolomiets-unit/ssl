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

#define BLOCK_SIZE 300
#define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

uint32_t	base64_encode
(
	t_byte in[BLOCK_SIZE],
	uint32_t in_size,
	t_byte *out
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

void		base64_encode_file_to_file
(
	int input,
	int output
)
{
	int			r;
	t_byte		input_buffer[BLOCK_SIZE];
	uint32_t	w;
	t_byte		output_buffer[400];

	r = 0;
	while ((r = read(input, input_buffer, BLOCK_SIZE)))
	{
		ft_printf("Read = %d\n", r);
		w = base64_encode(input_buffer, r, output_buffer);
		write(output, output_buffer, w);
	}
	ft_putchar_fd('\0', output);
}