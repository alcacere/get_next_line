#include "get_next_line.h"

char	*to_read(int fd, char *stc);
char	*new_stc(char *stc);
char	*set_line(char **stc);

void	ft_free(char **stc)
{
	if (*stc == NULL)
		return ;
	free(*stc);
	*stc = NULL;
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*stc;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (ft_free(&stc), NULL);
	if (stc == NULL || nl_check(stc, '\n') < 0)
	{
		stc = to_read(fd, stc);
		if (stc == NULL)
			return (NULL);
		if (stc[0] == '\0')
			return (ft_free(&stc), NULL);
	}
	line = set_line(&stc);
	if (line == NULL)
		return (NULL);
	return (line);
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

char	*to_read(int fd, char *stc)
{
	char	*buffer;
	int	rb;
	char	*tmp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (ft_free(&stc), NULL);
	rb = 1;
	while (rb > 0)
	{
		rb = read(fd, buffer, BUFFER_SIZE);
		if (rb < 0)
			return (ft_free(&buffer), NULL);
		buffer[rb] = '\0';
		if (!stc)
		{
			stc = ft_strdup("");
			if (!stc)
				return (ft_free(&buffer) ,NULL);
		}
		tmp = stc;
		stc = ft_strjoin(tmp, buffer);
		if (stc == NULL)
			return (ft_free(&tmp), ft_free(&buffer), NULL);
		ft_free(&tmp);
		if (nl_check(stc,'\n') >= 0 || rb < BUFFER_SIZE)
			break ;
	}
	return (ft_free(&buffer), stc);
}

//char	*new_stc(char *stc)
//{
//	ssize_t	index;
//
//	index = nl_check(stc, '\n');
//	if (index < 0)
//		return (stc = ft_strdup(""), stc);
//	stc = ft_substr(stc, index + 1, ft_strlen(stc) - (index + 1));
//	if (stc == NULL)
//		return (NULL);
//	return (stc);
//}

int main ()
{
	int fd = open("giant_line.txt", O_RDONLY);
	char *line = NULL;
	int i = 0;

	while (1)
	{
		line = get_next_line(fd);
	if (!line)
		return (printf("\n"), close(fd), 1);
	printf("line aft gnl: %s", line);
	//	if (i == 11)
	//		break ;
		free(line);
		i++;
		if (i == 10)
			close(fd);
		//usleep(60000);
	}
	free(line);
	close(fd);
	return (0);
}
