/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:37:31 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/20 15:37:32 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <inttypes.h>

typedef unsigned char	t_byte;
typedef uint32_t		t_word;
typedef uint64_t		t_dword;

void	bytes_to_little_endian_words(t_word *words, t_byte *bytes,
									uint32_t bytes_len);
void	bytes_to_big_endian_words(t_word *words, t_byte *bytes,
								uint32_t bytes_len);
void	little_endian_words_to_bytes(t_word *words, t_byte *bytes,
								uint32_t bytes_len);
void	big_endian_words_to_bytes(t_word *words, t_byte *bytes,
								uint32_t bytes_len);
void	little_endian_dword_to_bytes(t_dword value, t_byte bytes[8]);

void	big_endian_dword_to_bytes(t_dword value, t_byte bytes[8]);
void	big_endian_dwords_to_bytes(t_dword *words, t_byte *bytes,
								uint32_t bytes_len);

void	bytes_to_big_endian_dwords(t_dword *words, t_byte *bytes,
								uint32_t bytes_len);

void	filter_str(char *buffer);


#endif
