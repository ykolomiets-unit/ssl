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

# define MOVE_BIT(n, start_pos, end_pos) ((((n) & (0x1L << (start_pos))) >> (start_pos)) << (end_pos))

void		des_get_key_and_iv(char *pass, uint64_t salt,
				uint64_t key, uint64_t iv);

uint64_t	apply_pc1(uint64_t key);

#endif
