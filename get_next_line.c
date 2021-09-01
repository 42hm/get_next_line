/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:54:51 by hmoon             #+#    #+#             */
/*   Updated: 2021/06/10 14:43:24 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		buff = NULL;
	if ((ret= read(fd, buff, BUFFER_SIZE)) < 0 || buff == NULL)
	{
		free(buff);
		buff = NULL;
		return (-1);
	}
	buff[ret] = '\0';
	if (!(temp = ft_strjoin(*save, buff)))
		return (-1);
	free(*save);
	free(buff);
	*save = NULL;
	buff = NULL;
	*save = temp;
	return (ret = (ret > 0) ? 1 : ret);
}

int		division(char **save, char **line, int ret)
{
	char	*output;
	char	*backup;
	int		i;

	i = 0;
	if (ret == 0)
	{
		if (!(*line = ft_strdup(*save)))
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
	else if (ret > 0)
	{
		while ((*save)[i] != '\n')
			i++;
		if (!(output = ft_substr(*save, 0, i)))
			return (-1);
		*line = output;
		if (!(backup = ft_strdup(*save + i + 1)))
			return (-1);
		free(*save);
		*save = NULL;
		*save = backup;
	}
	return (ret = (ret > 0) ? 1 : ret);
}

int		get_next_line(int fd, char **line)
{
	static char *save[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!save[fd])
	{
		save[fd] = ft_strdup("");
		if (!save[fd])
			return (-1);
	}
	ret = 1;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == 0))
		ret = read_buff(fd, &save[fd]);
	return (division(&save[fd], line, ret));
}
