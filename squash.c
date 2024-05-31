/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:22:00 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 16:55:56 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	squash_ops(int ops[MAXOP])
{
	int	a;
	int	b;
	int	n;

	a = ops[RA] - ops[RRA] + ops[RR] - ops[RRR];
	b = ops[RB] - ops[RRB] + ops[RR] - ops[RRR];
	ft_bzero(ops, sizeof(int [MAXOP]));
	if (a < 0 != b < 0)
	{
		ops[RA + 3 * (a < 0)] = ft_abs(a);
		ops[RB + 3 * (b < 0)] = ft_abs(b);
	}
	else
	{
		n = ft_min(2, ft_abs(a), ft_abs(b));
		ops[RR + 3 * (a < 0)] = n;
		ops[RA + 3 * (a < 0)] = ft_abs(a) - n;
		ops[RB + 3 * (a < 0)] = ft_abs(b) - n;
	}
}

static bool	cut_squash(t_oplist **start, t_oplist ***end, int ops[MAXOP])
{
	t_oplist	*next;
	t_op		op;

	next = **end;
	**end = NULL;
	free_lst(start);
	squash_ops(ops);
	op = RA;
	while (op < MAXOP)
	{
		while (ops[op])
		{
			if (!lst_add(start, lst_create(OPLIST, op), NULL, false))
				return (free_lst(&next), false);
			ops[op]--;
		}
		op++;
	}
	*end = start;
	while (**end)
		*end = &(**end)->next;
	**end = next;
	return (true);
}

bool	squash_oplist(t_oplist **start)
{
	static int	ops[MAXOP] = {0};
	t_oplist	**last_start;
	t_oplist	**curr;

	curr = start;
	while (true)
	{
		while (*curr && (*curr)->op < RA)
			curr = &(*curr)->next;
		if (!*curr)
			break ;
		last_start = curr;
		while (*curr && (*curr)->op >= RA)
		{
			ops[(*curr)->op]++;
			curr = &(*curr)->next;
		}
		if (!cut_squash(last_start, &curr, ops))
			return (false);
	}
	return (true);
}
