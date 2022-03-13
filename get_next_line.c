/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoon <hmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:54:51 by hmoon             #+#    #+#             */
/*   Updated: 2022/03/13 11:47:47 by hmoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_buff(int fd, char **save)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		buff = NULL;
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret < 0 || buff == NULL)
	{
		free(buff);
		buff = NULL;
		return (-1);
	}
	buff[ret] = '\0';
	temp = ft_strjoin(*save, buff);
	free(*save);
	free(buff);
	*save = NULL;
	buff = NULL;
	*save = temp;
	if (ret > 0)
		return (1);
	else
		return (ret);
}

void	division(char **save, char **line, int ret)
{
	char	*output;
	char	*backup;
	int		i;

	i = 0;
	if (ret == 0)
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	else if (ret > 0)
	{
		while ((*save)[i] != '\n')
			i++;
		output = ft_substr(*save, 0, i);
		*line = output;
		backup = ft_strdup(*save + i + 1);
		free(*save);
		*save = NULL;
		*save = backup;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (save == NULL)
		save = ft_strdup("");
	ret = 1;
	while (ret > 0 && (ft_strchr(save, '\n') == 0))
		ret = read_buff(fd, &save);
	division(&save, line, ret);
	return (line);
}
