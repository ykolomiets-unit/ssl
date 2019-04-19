/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:55:46 by ykolomie          #+#    #+#             */
/*   Updated: 2019/04/19 15:55:48 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_error.h"
#include "libft.h"
#include <stdlib.h>

void	ssl_error(const char *error_msg)
{
	ft_dprintf(2, "%s\n", error_msg);
	exit(-1);
}
