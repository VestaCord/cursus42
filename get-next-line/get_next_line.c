/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:17:51 by vtian             #+#    #+#             */
/*   Updated: 2025/06/21 00:39:39 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*read_file(int fd, char *line_buffer)
// arbitrary bytes_read intial value
// read_buffer must bzero in case bytes_r < bufsize
{
	char	*read_buffer;
	char	*tmp;
	int		bytes_read;

	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read && !ft_strchr(read_buffer, '\n'))
	{
		ft_bzero(read_buffer, BUFFER_SIZE);
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = 0;
		tmp = ft_strjoin(line_buffer, read_buffer);
		free(line_buffer);
		line_buffer = tmp;
	}
	free(read_buffer);
	return (line_buffer);
}

char	*read_line(char *line_buffer)
// don't need to set last char of line bc calloc
{
	char	*line;
	int		i;

	if (!*line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	line = calloc(i + 1, sizeof(char));
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
	{
		line[i] = line_buffer[i];
		++i;
	}
	return (line);
}

char	*prune_buffer(char *line_buffer)
// don't need to set last char of new_buf bc calloc
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
	{
		free(line_buffer);
		return (NULL);
	}
	new_buffer = ft_calloc((ft_strlen(line_buffer) - i + 1), sizeof(char));
	++i;
	j = 0;
	while (line_buffer[i])
		new_buffer[j++] = line_buffer[i++];
	free(line_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
// BUFFER_SIZE is determined at compilation time
//	it controls how much is read into buffer at once,
//	not the total size of the buffer
// read_file reads into the buffer
// get_line extracts the line from buffer
// prune_buffer removes the extracted line
{
	static char	*line_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line_buffer)
		line_buffer = ft_calloc(1, 1);
	line_buffer = read_file(fd, line_buffer);
	if (!line_buffer)
		return (NULL);
	line = read_line(line_buffer);
	line_buffer = prune_buffer(line_buffer);
	return (line);
}
