/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:18:56 by alcacere          #+#    #+#             */
/*   Updated: 2025/05/20 16:30:52 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	ft_free(char **stc);
char	*to_read(int fd, char *stc);
char	*new_stc(char *stc);
char	*set_line(char **stc);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stc;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (ft_free(&stc), NULL);
	if (stc == NULL || nl_check(stc, '\n') < 0)
	{
		if (stc == NULL)
			stc = ft_strdup("");
		stc = to_read(fd, stc);
		if (stc == NULL || stc[0] == '\0')
			return (ft_free(&stc), NULL);
	}
	line = set_line(&stc);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*to_read(int fd, char *stc)
{
	char	*buffer;
	char	*tmp;
	int		rb;

	if (stc == NULL)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (ft_free(&stc), NULL);
	rb = 1;
	while (rb > 0)
	{
		rb = read(fd, buffer, BUFFER_SIZE);
		if (rb < 0)
			return (ft_free(&stc), ft_free(&buffer), NULL);
		buffer[rb] = '\0';
		tmp = stc;
		stc = ft_strjoin(tmp, buffer);
		if (stc == NULL)
			return (ft_free(&tmp), ft_free(&buffer), NULL);
		ft_free(&tmp);
		if (nl_check(stc, '\n') >= 0 || rb < BUFFER_SIZE)
			break ;
	}
	return (ft_free(&buffer), stc);
}

char	*set_line(char **stc)
{
	char	*line;
	ssize_t	index;
	char	*tmp;

	tmp = *stc;
	index = nl_check(*stc, '\n');
	if (index >= 0)
		line = ft_substr(*stc, 0, index + 1);
	else
		line = ft_substr(*stc, 0, ft_strlen(*stc));
	if (line == NULL)
		return (ft_free(&(*stc)), NULL);
	if (index < 0)
		return (ft_free(&(*stc)), line);
	*stc = ft_substr(*stc, index + 1, ft_strlen(*stc) - (index + 1));
	if (*stc == NULL)
		return (ft_free(&tmp), ft_free(&line), NULL);
	ft_free(&tmp);
	return (line);
}

void	ft_free(char **stc)
{
	if (*stc == NULL)
		return ;
	free(*stc);
	*stc = NULL;
}

//#include <stdio.h>
//#include <fcntl.h>
//int main()
//{
//	int fd = open("test_len.txt", O_RDONLY);
//	char *line = NULL;
//
//	while (1)
//	{
//		line = get_next_line(fd);
//		printf("line: %s\n", line);
//		free(line);
//		if (line == NULL)
//			break ;
//	}
//	close(fd);
//}
