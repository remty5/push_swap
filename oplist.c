/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:18:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/06/03 19:05:56 by rvandepu         ###   ########.fr       */
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

bool	apply_ops(t_ctx *c, t_oplist **l, int ops[MAXOP])
{
	t_oplist	**o_l;
	t_op_f		op_f;
	t_op		op;

	o_l = c->l;
	if (l)
		c->l = l;
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
	c->l = o_l;
	return (true);
}

const char *const			g_ops_str[MAXOP] = {\
	[SA] = "sa\n", \
	[SB] = "sb\n", \
	[SS] = "ss\n", \
	[PA] = "pa\n", \
	[PB] = "pb\n", \
	[RA] = "ra\n", \
	[RB] = "rb\n", \
	[RR] = "rr\n", \
	[RRA] = "rra\n", \
	[RRB] = "rrb\n", \
	[RRR] = "rrr\n", \
};

void	print_oplist(t_oplist *l)
{
	while (l)
	{
		ft_printf("%s", g_ops_str[l->op]);
		l = l->next;
	}
}
