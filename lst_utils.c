/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 03:11:05 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 19:26:46 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_lst	*lst_create(enum e_type type, ...)
{
	t_lst	*new;
	va_list	args;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		return (NULL);
	va_start(args, type);
	if (type == STACK)
		*new = (t_lst){.value = va_arg(args, t_val)};
	else if (type == OPLIST)
		*new = (t_lst){.op = va_arg(args, t_op)};
	va_end(args);
	return (new);
}

bool	lst_add(t_lst **start, t_lst *new, int *len, bool check_dupes)
{
	t_lst	**s;

	if (new == NULL)
		return (false);
	s = start;
	while (*s)
	{
		if (check_dupes && (*s)->value == new->value)
			return (free(new), false);
		s = &(*s)->next;
	}
	*s = new;
	if (len)
		++*len;
	return (true);
}

int	lst_size(t_lst *l)
{
	int	i;

	i = 0;
	while (l)
	{
		i++;
		l = l->next;
	}
	return (i);
}

int	lst_indexof(t_lst *l, t_lst *q)
{
	int	i;

	i = 0;
	while (l && q != l)
	{
		l = l->next;
		i++;
	}
	if (q != l)
		return (-1);
	return (i);
}

void	free_lst(t_lst **l)
{
	t_lst	*to_free;

	while (*l)
	{
		to_free = *l;
		*l = (*l)->next;
		free(to_free);
	}
}
