/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_octets_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vijacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:59:28 by vijacque          #+#    #+#             */
/*   Updated: 2016/10/13 15:04:48 by vijacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_int	*add_octets(t_int *ptr)
{
	unsigned short int	byte2[1];
	unsigned int		byte4[1];
	t_int				*byte;

	byte = NULL;
	if (ptr->valid == 2)
	{
		byte2[0] = ptr->octet[0];
		byte = new_bytecode(((unsigned char*)byte2)[1], 1, NULL, 0);
		byte->next = ptr;
		ptr->octet[0] = ((unsigned char*)byte2)[0];
	}
	else if (ptr->valid == 4)
	{
		byte4[0] = ptr->octet[0];
		byte = new_bytecode(((unsigned char*)byte4)[3], 1, NULL, 0);
		byte->next = new_bytecode(((unsigned char*)byte4)[2], 1, NULL, 0);
		byte->next->next = new_bytecode(((unsigned char*)byte4)[1], 1, NULL, 0);
		byte->next->next->next = ptr;
		ptr->octet[0] = ((unsigned char*)byte4)[0];
	}
	else
		ft_exit("Data corrupt: parameters encoding.", DATA_CORRUPT);
	ptr->valid = 1;
	return (byte);
}

void			complete_octets_list(t_env *e)
{
	t_ins	*ptr;
	t_int	*ptr2;
	t_int	*previous;

	previous = NULL;
	ptr = e->ins;
	while (ptr != NULL)
	{
		ptr2 = ptr->done;
		while (ptr2 != NULL)
		{
			if (ptr2->valid > 1)
			{
				if (previous == NULL)
					ft_exit("Data corrupt: opcode encoding.", DATA_CORRUPT);
				previous->next = add_octets(ptr2);
			}
			previous = ptr2;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

void			ft_usage(void)
{
	ft_putstr("\033[32m");
	ft_putendl("./asm (-n) (/path/) file.s");
	ft_putendl("-n = the path where you want to have the output writed");
	ft_putstr("\033[0m");
}
