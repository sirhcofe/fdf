/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:29:24 by chenlee           #+#    #+#             */
/*   Updated: 2023/01/06 17:49:48 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// line 22-23: counts until either end of buffer or occurance of \n
// line 26-30: if buffer is at end of file, no need reset and end program
// line 33:	   allocate memory based on size of buffer after \n
//			   example: buffer = "12345\n6789"
//						we neeed to reset buffer after \n such that
//						buffer starts at 6
// line 38-40: fill in values for reset
char	*reset_buffer(char *buffer)
{
	char	*reset;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (0);
	}
	reset = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		reset[j++] = buffer[i++];
	free(buffer);
	buffer = 0;
	return (reset);
}

// line 53-55: Error handling
// line 56-58: Allocate memory for output string
//			   59: (i + 2) in calloc is to consider '\n' and '\0'
// line 62-69: Copy string and append '\n' at 2nd last string
char	*print_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

// line 73-81: As function suggests, join string and free
char	*join_and_free(char *buffer, char *temp)
{
	char	*pepega;

	pepega = ft_strjoin(buffer, temp);
	free(buffer);
	buffer = 0;
	return (pepega);
}

// line 93:		Allocate memory based on specified BUFFER_SIZE
// line 94:		Initialize byte_read
// line 95-105: While function checks if the string of BUFFER_SIZE contains '\n'
//				True = strjoin buffer w temp, then end while loop
//				False = strjoin buffer w temp, continues loop until '\n' is found
char	*read_file(char *buffer, int fd)
{
	char	*temp;
	int		byte_read;

	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	byte_read = 1;
	while (!ft_strchr(temp, '\n') && byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp);
			return (0);
		}
		temp[byte_read] = 0;
		buffer = join_and_free(buffer, temp);
	}
	free(temp);
	temp = 0;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	if (buffer == NULL)
		buffer = ft_calloc(1, sizeof(char));
	buffer = read_file(buffer, fd);
	if (!buffer)
		return (0);
	line = print_line(buffer);
	buffer = reset_buffer(buffer);
	return (line);
}
