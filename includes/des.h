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
# define DES_KEY_LENGTH 8
# define DES_SALT_LENGTH 8
# define DES_IV_LENGTH 8

# define ENCODE 0
# define DECODE 1

void	des_get_key_and_iv(char *pass, uint64_t salt, uint64_t key, uint64_t iv);
void	des_add_padding(int filled, t_byte block[DES_BLOCK_SIZE]);
 
void	des_key_schedule(uint64_t key, uint64_t subkeys[16], int mode);
void	des_core(uint64_t keys[16], t_byte input[DES_BLOCK_SIZE], t_byte output[DES_BLOCK_SIZE]);

void	des_ecb_encode(t_byte key[DES_KEY_LENGTH], int in, int out);
void	des_ecb_decode(t_byte key[DES_KEY_LENGTH], int in, int out);

#endif
