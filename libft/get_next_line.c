/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:04:31 by ulee              #+#    #+#             */
/*   Updated: 2021/01/20 21:22:08 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isnewline(char **backup, char **line)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*backup, '\n');
	if (newline == NULL)
		return (0);
	*newline = '\0';
	*line = ft_strdup(*backup);
	if (*line == NULL)
		return (-1);
	temp = ft_strdup(++newline);
	if (temp == NULL)
		return (-1);
	free(*backup);
	*backup = temp;
	return (1);
}

int	backup_clean(char **backup, char **line, int read_size)
{
	if (read_size < 0)
		return (-1);
	if (*backup != NULL && (isnewline(backup, line)))
		return (1);
	else if (*backup != NULL)
	{
		*line = ft_strdup(*backup);
		if (*line == NULL)
			return (-1);
		free(*backup);
		*backup = NULL;
		return (0);
	}
	*line = ft_strdup("");
	if (*line == NULL)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	char			*temp;
	int				error;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE < 1))
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		temp = backup[fd];
		backup[fd] = ft_strjoin(backup[fd], buf);
		if (backup[fd] == NULL)
			return (-1);
		free(temp);
		error = isnewline(&backup[fd], line);
		if (error != 0)
			return (error);
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	return (backup_clean(&backup[fd], line, read_size));
}
