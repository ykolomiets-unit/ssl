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

# define DES_SALT_LEN 8
# define DES_KEY_LEN 8
# define DES_IV_LEN 8	

void	des_get_key_and_iv(char *pass, t_byte salt[DES_SALT_LEN],
			t_byte key[DES_KEY_LEN], t_byte iv[DES_IV_LEN]);

#endif
