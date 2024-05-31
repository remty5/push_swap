/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:18:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 17:58:56 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const t_op_f			g_ops[MAXOP] = {\
	[SA] = sa, \
	[SB] = sb, \
	[SS] = ss, \
	[PA] = pa, \
	[PB] = pb, \
	[RA] = ra, \
	[RB] = rb, \
	[RR] = rr, \
	[RRA] = rra, \
	[RRB] = rrb, \
	[RRR] = rrr, \
};

bool	apply_ops(t_ctx *c, int ops[MAXOP])
{
	t_op_f		op_f;
	t_op		op;

	op = MAXOP;
	while (--op)
	{
		if (ops[op])
			op_f = g_ops[op];
		while (ops[op])
		{
			if (!op_f(c))
				return (false);
			ops[op]--;
		}
	}
	return (true);
}

static const char *const	g_ops_str[MAXOP] = {\
	[SA] = "sa", \
	[SB] = "sb", \
	[SS] = "ss", \
	[PA] = "pa", \
	[PB] = "pb", \
	[RA] = "ra", \
	[RB] = "rb", \
	[RR] = "rr", \
	[RRA] = "rra", \
	[RRB] = "rrb", \
	[RRR] = "rrr", \
};

void	print_oplist(t_oplist *l)
{
	while (l)
	{
		ft_printf("%s\n", g_ops_str[l->op]);
		l = l->next;
	}
}
