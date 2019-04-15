/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:39:42 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/26 16:40:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "utils.h"
#include "libft.h"
#include <unistd.h>

#define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

uint32_t	base64_encode
(
	t_byte in[DECODED_SIZE],
	uint32_t in_size,
	t_byte out[ENCODED_SIZE]
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

static void			base64_write(int fd, t_byte *buffer, t_base64_write *help)
{
	int			last_line_length;
	int			pos;

	if (help->bnum == 0)
		write(fd, buffer, help->write);
	else
	{
		last_line_length = help->total % help->bnum;
		pos = help->bnum - last_line_length;
		if (pos > help->write)
			write(fd, buffer, help->write);
		else
			write(fd, buffer, pos);
		write(fd, "\n", 1);
		while (pos + help->bnum <= help->write)
		{
			write(fd, buffer + pos, help->bnum);
			write(fd, "\n", 1);
			pos += help->bnum;
		}
		if (pos < help->write)
			write(fd, buffer + pos, help->write - pos);
	}
	help->total += help->write;
}


void		base64_encode_file_to_file
(
	int input,
	int output,
	int	bnum
)
{
	int				r;
	uint32_t		in_buf;
	t_base64_write	help;
	t_byte			input_buffer[DECODED_SIZE];
	t_byte			output_buffer[ENCODED_SIZE];

	r = 0;
	in_buf = 0;
	help.bnum = bnum;
	help.total = 0;
	while ((r = read(input, input_buffer + in_buf, DECODED_SIZE - in_buf)) > 0)
	{
		in_buf += r;
		if (in_buf == DECODED_SIZE)
		{
			help.write = base64_encode(input_buffer, DECODED_SIZE, output_buffer);
			base64_write(output, output_buffer, &help);
			in_buf = 0;
		}
	}
	if (in_buf)
	{
		help.write = base64_encode(input_buffer, in_buf, output_buffer);
		base64_write(output, output_buffer, &help);
	}
	write(output, "\x0a", 1);
}
