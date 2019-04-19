/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:54:20 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:54:21 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PBKDF2_H
# define PBKDF2_H

# include "types.h"

typedef struct	s_pbkdf2_params
{
	t_byte		*password;
	uint32_t	password_length;
	t_byte		*salt;
	uint32_t	salt_length;
	uint32_t	iteration_count;
}				t_pbkdf2_params;

void			pbkdf2(t_pbkdf2_params params, t_byte *dk, uint32_t dk_len);

#endif
