/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:56:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/28 12:39:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_parsing_exit(int fd, char *msg, t_data *data)
{
	if (fd > -1)
		close(fd);
	ft_err_exit(msg, data);
}

static void		ft_get_mapsize(int fd, char *line, t_data *data)
{
	if (!(*line))
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	else if (ft_nbwords(line) != 2)
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	else if (!(data->map_sz.w = ft_atoi(line)))
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	else if (!(data->map_sz.h = ft_atoi(line + ft_nbrlen(data->map_sz.w, 10))))
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
}

static void		ft_parse_line(int fd, int index, char *line, t_data *data)
{
	int		val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '2')
		{
			if (data->player.position.x != -1)
				ft_parsing_exit(fd, "wolf3d: parsing error: bad spawn", data);
			data->player.position.x = j + 0.5;
			data->player.position.y = index + 0.5;
		}
		if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3')
		{
			if ((val = ft_atoi(line + i)) > 9)
				ft_parsing_exit(fd, "wolf3d: parsing error: bad bloc index", data);
			data->map[index][j++] = ft_atoi(line + i);
		}
		else if (line[i] != ' ')
			ft_parsing_exit(fd, "wolf3d: parsing error: bad bloc index1", data);
		i++;
	}
}

void			ft_get_map(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(map, O_RDONLY)) == -1)
		ft_parsing_exit(-1, "wolf3d: parsing error: can't open the map", data);
	if ((get_next_line(fd, &line)) < 1)
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	ft_get_mapsize(fd, line, data);
	lt_release((void *)line);
	if (!(data->map =
	(int **)(ft_memalloc_lt(sizeof(int *) * (data->map_sz.h)))))
		ft_parsing_exit(fd, "wolf3d: parsing error: out of memory", data);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (i > data->map_sz.h || ft_nbwords(line) != data->map_sz.w)
			ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
		if (!(data->map[i] =
		(int *)(ft_memalloc_lt(sizeof(int) * (data->map_sz.w)))))
			ft_parsing_exit(fd, "wolf3d: parsing error: out of memory", data);
		ft_parse_line(fd, i, line, data);
		lt_release((void *)line);
		i++;
	}
	if (i != data->map_sz.h || data->player.position.x == -1)
		ft_parsing_exit(fd, "wolf3d: parsing error: bad map format", data);
	close(fd);
}
