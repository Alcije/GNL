/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpavlov <alpavlov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:57:28 by alpavlov          #+#    #+#             */
/*   Updated: 2026/05/07 13:20:30 by alpavlov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*mtn_line(int fd, char *buff)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(buff, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(buff);
			return (NULL);
		}
		buffer[bytes] = '\0';
		buff = ft_strjoin(buff, buffer);
	}
	free(buffer);
	return (buff);
}

static char	*take_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff || !buff[0])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_buff(char *buff)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	i++;
	new = malloc(ft_strlen(buff + i) + 1);
	if (!new)
	{
		free(buff);
		return (NULL);
	}
	j = 0;
	while (buff[i])
		new[j++] = buff[i++];
	new[j] = '\0';
	free(buff);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = mtn_line(fd, buff);
	if (!buff)
		return (NULL);
	line = take_line(buff);
	buff = update_buff(buff);
	return (line);
}
