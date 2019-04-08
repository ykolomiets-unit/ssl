/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:19:21 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/27 18:19:22 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "types.h"

# define MOVE_BIT(n, s, e) ((((n) & (0x1L << (64 - s))) >> (64 - s)) << (64 - e))
# define ROL28(a, n) ((((a) << (n)) | ((a) >> (28 - (n)))) & 0x0FFFFFFF)

# define DES_BLOCK_SIZE 8
 
void		des_get_key_and_iv(char *pass, uint64_t salt,
				uint64_t key, uint64_t iv);

void		generate_subkeys(uint64_t key, uint64_t subkeys[16]);
void		des_core(uint64_t keys[16], t_byte input[DES_BLOCK_SIZE], t_byte output[DES_BLOCK_SIZE]);
uint64_t	apply_ip(uint64_t m);
uint64_t	expand(uint64_t m);
uint64_t	substitude(uint64_t m);
uint64_t	permute(uint64_t m);
uint64_t	apply_fp(uint64_t m);

#endif
