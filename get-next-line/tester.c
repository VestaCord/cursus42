/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:32:38 by vtian             #+#    #+#             */
/*   Updated: 2025/06/21 00:52:50 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"
#include "stdio.h"
#include "unistd.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		i = 1;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: test [filename1] [filename2...]\n");
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	printf("[DEBUG] BUFFER_SIZE (%d)\n\tfd (%d)\n\tfilename (%s)\n",
		BUFFER_SIZE, fd, argv[1]);
	// line = ft_calloc(BUFFER_SIZE, sizeof(char));
	// read(fd, line, BUFFER_SIZE);
	// printf("[DEBUG] Read BUFFER_SIZE bytes:\n===\n\t%s\n===\n", line);
	// free(line);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%-3d\t%s\n", i, line);
		free (line);
		++i;
	}
	return (0);
}