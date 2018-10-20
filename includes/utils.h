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

void	bytes_to_low_order_words(uint32_t *words, char *bytes,
								uint32_t bytes_len);
void	low_order_words_to_bytes(uint32_t *words, char *bytes,
								uint32_t bytes_len);

#endif
