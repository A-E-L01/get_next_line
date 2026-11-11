/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboel-ma <aboel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:03:42 by aboel-ma          #+#    #+#             */
/*   Updated: 2026/11/11 13:50:42 by aboel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *get)
{
	int	index;

	index = 0;
	if (get == NULL)
		return (0);
	while (get[index] && get[index] != '\n')
		index++;
	if (get[index] == '\n')
		return (1);
	return (0);
}

char	*read_and_save(int fd, char *buffer, char *get)
{
	ssize_t		read_len;
	char		*tmp;

	if (get == NULL)
		get = ft_strdup("");
	if (get == NULL)
		return (NULL);
	if (find_newline(get) == 1)
		return (get);
	while (find_newline(get) == 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len > 0)
			buffer[read_len] = '\0';
		if (read_len < 0)
			return (free(get), NULL);
		if (read_len == 0)
			break ;
		tmp = ft_strjoin(get, buffer);
		if (tmp == NULL)
			return (free(get), NULL);
		free(get);
		get = tmp;
	}
	return (get);
}

char	*new_line(char *get)
{
	int		index;
	int		size;
	char	*line;

	index = 0;
	size = 0;
	if (get == NULL)
		return (NULL);
	while (get[size] && get[size] != '\n')
		size++;
	if (get[size] == '\n')
		size = size + 1 + 1;
	else
		size = size + 1;
	line = malloc(sizeof(char) * size);
	if (line == NULL)//wax makhasch fre get
		return (NULL);
	size = size - 1;
	while (index < size)
	{
		line[index] = get[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

char	*update_get(char *get)
{
	int		index;
	char	*tmp;

	index = 0;
	if (get == NULL)
		return (NULL);
	while (get[index] != '\0' && get[index] != '\n')//
		index++;
	if (get[index] == '\0')
	{
		free(get);
		return (NULL);
	}
	tmp = ft_substr(get, index + 1, ft_strlen(get) - (index + 1));
	if (tmp == NULL)
	{
		free(get);
		return (NULL);
	}
	free(get);
	get = tmp;
	return (get);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*get;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		if (get != NULL)
			free(get);
		return (NULL);
	}
	get = read_and_save(fd, buffer, get);
	free(buffer);
	if (get == NULL || get[0] == '\0')
	{
		free(get);
		get = NULL;
		return (NULL);
	}
	line = new_line(get);
	get = update_get(get);
	return (line);
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	printf("fd1: %d\n", fd);

	char *x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);

	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);

	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);
	
	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);
	
	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);
	
	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);

	x = get_next_line(fd);
	printf("[%s].\n", x);
	free(x);
	
	close(fd);
	return (0);
}






// int main(void)
// {
// 	int		fd;
// 	char	*line;
//
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }