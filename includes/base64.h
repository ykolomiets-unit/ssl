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

typedef struct	s_base64_write
{
	int			write;
	int			total;
	int			bnum;
}				t_base64_write;

void	base64_encode_file_to_file(int input, int output, int bnum);
int		base64_decode_file_to_file(int input, int output);

#endif
