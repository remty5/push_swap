/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:18:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/23 05:55:45 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	err(t_ctx *c)
{
	(void) c;
	ft_printf("[DEBUG] NOP called!\n");
	return (false);
}

static const t_op_f			g_ops[MAXOP] = {\
	[NOP] = err, \
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

static const t_op_f			g_rev_ops[MAXOP] = {\
	[PA] = pb, \
	[PB] = pa, \
	[RA] = rra, \
	[RB] = rrb, \
	[RR] = rrr, \
	[RRA] = ra, \
	[RRB] = rb, \
	[RRR] = rr, \
};

t_op_f	get_op(t_op op, bool rev)
{
	t_op_f	ret;

	ret = NULL;
	if (rev)
		ret = g_rev_ops[op];
	if (ret == NULL)
		ret = g_ops[op];
	return (ret);
}

bool	apply_ops(t_ctx *c, t_oplist **l, int ops[MAXOP])
{
	t_oplist	**o_l;
	t_op_f		op_f;
	t_op		op;

	o_l = c->l;
	c->l = l;
	op = MAXOP;
	while (--op)
	{
		if (ops[op])
			op_f = get_op(op, false);
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

static const char *const	g_ops_str[MAXOP] = {\
	[NOP] = "NOP", \
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

void	undo_oplist(t_ctx *c, t_oplist **l)
{
	static t_op_f	rev_op;

	if (*l)
	{
		undo_oplist(c, &(*l)->next);
		rev_op = get_op((*l)->op, true);
		c->undo = true;
		rev_op(c);
		c->undo = false;
		free_lst(l);
	}
}
