/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:18:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 03:34:09 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	err(t_ctx *c)
{
	(void) c;
	ft_printf("NOP called!\n");
	return (false);
}

static bool (*const	g_ops[MAXOP])(t_ctx *c) = {\
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

static bool (*const	g_rev_ops[MAXOP])(t_ctx *c) = {\
	[PA] = pb, \
	[PB] = pa, \
	[RA] = rra, \
	[RB] = rrb, \
	[RR] = rrr, \
	[RRA] = ra, \
	[RRB] = rb, \
	[RRR] = rr, \
};

void	oplist_undo(t_ctx *c, t_oplist **l)
{
	bool (*rev_op)(t_ctx * c);
	if (*l)
	{
		oplist_undo(c, &(*l)->next);
		rev_op = g_rev_ops[(*l)->op];
		if (rev_op == NULL)
			rev_op = g_ops[(*l)->op];
		rev_op(&(t_ctx){NULL, c->a, c->b, true});
	}
}
