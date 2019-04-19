/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:22:17 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 16:22:18 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"

void	des3_core(uint64_t *keys, t_byte *block, t_byte *output)
{
	des_core(keys, block, output);
	des_core(keys + 16, block, output);
	des_core(keys + 32, block, output);
}
