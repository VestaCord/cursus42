/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:33:03 by vtian             #+#    #+#             */
/*   Updated: 2025/07/07 21:39:00 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*prune_buffer(char *buffer)
// don't need to set last char of new_buf bc calloc
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*read_line(char *line_buffer)
// don't need to set last char of line bc calloc
{
	char	*line;
	int		i;

	i = 0;
	if (!line_buffer[i])
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
	{
		line[i] = line_buffer[i];
		i++;
	}
	if (line_buffer[i] && line_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *line_buffer)
// arbitrary bytes_read intial value
// read_buffer must bzero in case bytes_r < bufsize
// 	alternative is read_buffer[byte_read] = 0;
{
	char	*read_buffer;
	char	*tmp;
	int		byte_read;

	if (!line_buffer)
		line_buffer = ft_calloc(1, 1);
	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		ft_bzero(read_buffer, BUFFER_SIZE);
		byte_read = read(fd, read_buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		tmp = line_buffer;
		line_buffer = ft_strjoin(tmp, read_buffer);
		free(tmp);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (line_buffer);
}

char	*get_next_line(int fd)
// BUFFER_SIZE is determined at compilation time
//	it controls how much is read into buffer at once,
//	not the total size of the buffer
// read_file reads into the buffer
// get_line extracts the line from buffer
// prune_buffer removes the extracted line
{
	static char	*line_buffer[ULIMIT_OPEN_FILES];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line_buffer[fd] = read_file(fd, line_buffer[fd]);
	if (!line_buffer[fd])
		return (NULL);
	line = read_line(line_buffer[fd]);
	line_buffer[fd] = prune_buffer(line_buffer[fd]);
	return (line);
}
