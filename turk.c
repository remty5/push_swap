/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:10:14 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/30 20:11:25 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calc_pos(t_stack *elem, t_stack *stack, bool descending);
static int	calc_move(t_ctx *c, int ia, int ib, int ops[MAXOP]);

static void	calc_min(t_ctx *c, t_stack **min)
{
	t_stack		*s;
	int			i;
	int			min_cost;
	int			cost;

	if (!c->turk_rev)
		s = *c->a;
	else
		s = *c->b;
	i = 0;
	*min = NULL;
	while (s)
	{
		if (c->turk_rev)
			cost = calc_move(c, calc_pos(s, *c->a, false), i, NULL);
		else
			cost = calc_move(c, i, calc_pos(s, *c->b, true), NULL);
		if (*min == NULL || cost < min_cost)
		{
			*min = s;
			min_cost = cost;
		}
		s = s->next;
		i++;
	}
}

bool	move_min_cost(t_ctx *c)
{
	static int	ops[MAXOP] = {0};
	t_stack		*min;

	calc_min(c, &min);
	if (!c->turk_rev)
		calc_move(c, lst_indexof(*c->a, min), calc_pos(min, *c->b, true), ops);
	else
		calc_move(c, calc_pos(min, *c->a, false), lst_indexof(*c->b, min), ops);
	if (!apply_ops(c, c->l, ops))
		return (false);
	return (true);
}

static int	calc_pos(t_stack *e, t_stack *stack, bool desc)
{
	t_stack	*limits[2];
	t_stack	*s;

	s = stack;
	limits[0] = s;
	limits[1] = s;
	while (s)
	{
		if (s->value < limits[0]->value)
			limits[0] = s;
		else if (s->value > limits[1]->value)
			limits[1] = s;
		s = s->next;
	}
	if (e->value < limits[0]->value || limits[1]->value < e->value)
		return (lst_indexof(stack, limits[desc]));
	s = limits[desc];
	while ((desc && s->value > e->value) || (!desc && s->value < e->value))
	{
		s = s->next;
		if (!s)
			s = stack;
	}
	return (lst_indexof(stack, s));
}

static int	calc_move(t_ctx *c, int ia, int ib, int ops[MAXOP])
{
	int	bp;
	int	bn;
	int	apbn;
	int	anbp;
	int	min;

	bp = ft_max(2, ia, ib);
	bn = ft_max(2, c->a_len - ia, c->b_len - ib);
	apbn = ia + c->b_len - ib;
	anbp = c->a_len - ia + ib;
	min = ft_min(4, bp, bn, apbn, anbp);
	if (ops && (min == bp || min == bn))
		ops[RR + 3 * (min != bp)] = (min == bp) * ft_min(2, ia, ib)
			+ (min != bp) * ft_min(2, c->a_len - ia, c->b_len - ib);
	if (ops && (min == bp || min == bn))
		ops[RA + 3 * (min != bp) + ((min == bp && ib > ia) || (min != bp && \
			c->b_len - ib > c->a_len - ia))] = (min == bp) * (bp - ops[RR])
			+ (min != bp) * (bn - ops[RRR]);
	if (ops && (min != bp && min != bn) && (min == apbn || min == anbp))
		ops[RA + 3 * (min != apbn)] = \
				(min == apbn) * ia + (min != apbn) * (c->a_len - ia);
	if (ops && (min != bp && min != bn) && (min == apbn || min == anbp))
		ops[RB + 3 * (min == apbn)] = \
				(min != apbn) * ib + (min == apbn) * (c->b_len - ib);
	return ((ops && ops[PB - c->turk_rev]++), min + 1);
}
