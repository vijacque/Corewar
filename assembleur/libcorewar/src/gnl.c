/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:35:49 by vijacque          #+#    #+#             */
/*   Updated: 2016/10/12 13:42:01 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libcorewar.h>

static void		ft_write(char **tab, char **s, int count)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (count > 1)
		free(*s);
	*s = (char*)malloc(sizeof(char) * ft_linelen(tab[0]) + 1);
	while (tab[0][i] != '\n' && tab[0][i] != 0)
	{
		(*s)[i] = tab[0][i];
		i++;
	}
	(*s)[i] = '\0';
	i++;
	while (tab[0][i] != 0)
	{
		tab[0][j] = tab[0][i];
		i++;
		j++;
	}
	tab[0][j] = 0;
}

static int		ft_read(char **tab, int bytes, int const fd)
{
	char	*s;

	s = tab[0];
	tab[1] = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);
	bytes = read(fd, tab[1], BUFF_SIZE);
	if (bytes == 0 || bytes == -1)
	{
		free(tab[1]);
		return (bytes);
	}
	tab[1][bytes] = 0;
	tab[0] = ft_strjoin(tab[0], tab[1]);
	if (s)
	{
		free(s);
		s = NULL;
	}
	ft_bzero(tab[1], BUFF_SIZE + 1);
	return (bytes);
}

int				get_next_line(int const fd, char **line)
{
	static char	**tmp;
	static int	count;
	static int	bytes;

	if (BUFF_SIZE < 1 || count == -1 || fd < 0)
		return (-1);
	count++;
	if (count == 1)
	{
		tmp = (char**)malloc(sizeof(char*) * 3);
		tmp[0] = (char*)malloc(sizeof(char) * 1);
		bytes = 1;
	}
	if (bytes == 0)
	{
		free(tmp[0]);
		free(tmp);
		count = -1;
		return (0);
	}
	while (ft_strchr(tmp[0], '\n') == NULL && bytes != 0)
		if ((bytes = ft_read(tmp, bytes, fd)) == -1)
			return (-1);
	ft_write(tmp, line, count);
	return (1);
}
