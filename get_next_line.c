/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:26:42 by alcacere          #+#    #+#             */
/*   Updated: 2026/03/15 22:36:08 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static ssize_t	ft_strchr_gnl(const char *s, int c, size_t len)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

static void	*free_state(t_gnl_state *state)
{
	free(state->buffer);
	state->buffer = NULL;
	state->capacity = 0;
	state->len = 0;
	return (NULL);
}

static int	append_buffer(t_gnl_state *state, char *chunk, size_t size)
{
	char	*new_buffer;
	size_t	new_capacity;

	if (state->len + size + 1 > state-> capacity)
	{
		new_capacity = state->capacity * 2;
		if (new_capacity == 0)
			new_capacity = BUFFER_SIZE + 1;
		if (new_capacity < state->len + size + 1)
			new_capacity = state->len + size + 1;
		new_buffer = malloc(new_capacity);
		if (!new_buffer)
			return (0);
		if (state->buffer)
		{
			ft_memcpy(new_buffer, state->buffer, state->len);
			free(state->buffer);
		}
		state->buffer = new_buffer;
		state->capacity = new_capacity;
	}
	ft_memcpy(state->buffer + state->len, chunk, size);
	state->len += size;
	state->buffer[state->len] = '\0';
	return (1);
}

static char	*get_line(t_gnl_state *state, ssize_t nl_index)
{
	char	*line;
	size_t	len;

	len = state->len;
	if (nl_index >= 0)
		len = (size_t)nl_index + 1;
	if (len == 0)
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, state->buffer, len);
	line[len] = '\0';
	state->len -= len;
	if (state->len > 0)
	{
		ft_memcpy(state->buffer, state->buffer + len, state->len);
		state->buffer[state->len] = '\0';
	}
	else
		free_state(state);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl_state	stc[1024];
	char				buffer[BUFFER_SIZE];
	ssize_t				b_read;
	ssize_t				nl_index;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		nl_index = ft_strchr_gnl(stc[fd].buffer, '\n', stc[fd].len);
		if (nl_index >= 0)
			return (get_line(&stc[fd], nl_index));
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0 || (b_read == 0 && stc[fd].len == 0))
			return (free_state(&stc[fd]));
		if (b_read == 0)
			return (get_line(&stc[fd], -1));
		if (!append_buffer(&stc[fd], buffer, b_read))
			return (free_state(&stc[fd]));
	}
}
