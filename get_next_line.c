/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuhuss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 21:00:54 by yabuhuss          #+#    #+#             */
/*   Updated: 2026/11/05 22:14:27 by yabuhuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	size_t	i;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	return (str_sub(stash, 0, i + 1));
}

static char	*update_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = str_sub(stash, i + 1, str_len(stash));
	free(stash);
	return (new_stash);
}

static char	*free_fun(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_fun(stash, NULL));
	bytes_read = 1;
	while (!search_n(stash) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_fun(stash, buffer));
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			tmp = str_join(stash, buffer);
			free(stash);
			stash = tmp;
			if (!stash)
				break ;
		}
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
