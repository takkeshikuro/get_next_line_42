/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:01:30 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/09 23:52:43 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*line_keep(char *str_keep)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str_keep[i] && str_keep[i] != '\n')
		i++;
	if (!str_keep[i])
	{
		free(str_keep);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(str_keep) - i) + 1);
	if (!s)
		return (NULL);
	i++;
	while (str_keep[i])
		s[j++] = str_keep[i++];
	s[j] = '\0';
	free(str_keep);
	return (s);
}

char	*final_line(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = malloc(sizeof(char) * i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*read_line(int fd, char *keep)
{
	char	*buf;
	int		i;

	i = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	while (!ft_strchr(buf, '\n') && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		keep = ft_strjoin(keep, buf);
	}
	free(buf);
	return (keep);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*keep[4096];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	keep[fd] = read_line(fd, keep[fd]);
	if (!keep[fd])
		return (NULL);
	line = final_line(keep[fd]);
	keep[fd] = line_keep(keep[fd]);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*str;

	fd = open("tak.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("%s", str);
		free(str);
	}
	return (0);
} */
