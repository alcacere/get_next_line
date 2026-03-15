/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:34:23 by alcacere          #+#    #+#             */
/*   Updated: 2026/03/15 22:36:22 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include "libft.h"

typedef struct s_gnl_state
{
	char	*buffer;
	size_t	capacity;
	size_t	len;
}	t_gnl_state;

char	*get_next_line(int fd);

#endif
