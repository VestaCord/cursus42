/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:52:33 by vtian             #+#    #+#             */
/*   Updated: 2025/06/21 00:57:01 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"
#include "fcntl.h"
#include "stdio.h"
#include "unistd.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	int		j = 1;
	char	*line;

	if (argc < 2)
	{
		printf("Usage: test [filename1] [filename2...]\n");
		exit (1);
	}
	while (j < argc)
	{
		fd = open(argv[j], O_RDONLY);
		printf("[DEBUG] ULIMIT_OPEN_FILES (%d) BUFFER_SIZE (%d)\n\tfd (%d)\n\tfilename (%s)\n",
			ULIMIT_OPEN_FILES, BUFFER_SIZE, fd, argv[1]);
		i = 1;
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break;
			printf("%-3d\t%s\n", i, line);
			free (line);
			++i;
		}
		++j;
	}
	return (0);
}