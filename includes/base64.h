/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:43:13 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/26 16:43:14 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# define DECODED_SIZE 300
# define ENCODED_SIZE 400

# include "types.h"

typedef struct	s_base64_write
{
	int			write;
	int			total;
	int			bnum;
}				t_base64_write;

typedef struct	s_base64_options
{
	t_bool		encode;
	t_bool		decode;
	int			input_file;
	int			output_file;
	int			break_num;
}				t_base64_options;

void			base64_encode_file_to_file(int input, int output, int bnum);
int				base64_decode_file_to_file(int input, int output);

#endif
