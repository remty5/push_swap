/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luma_heart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:10:14 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/24 07:02:29 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// TODO move these when splitting
static int	calc_pos_in(t_stack *elem, t_stack *stack, bool descending);
static int	calc_move_cost(t_ctx *c, int ia, int ib, int ops[MAXOP]);
// TODO del this
void		print_stacks(t_ctx *c, t_stack *a, t_stack *b);

bool	move_min_cost(t_ctx *c, int *ret, int depth)
{
	t_oplist	*mem;
	t_stack		*s;
	int			i;
	static int	ops[MAXOP] = {0};
	t_stack		*min;
	int			min_cost;
	int			cost;

	mem = NULL;
	if (c->luma_rev)
		s = *c->b;
	else
		s = *c->a;
	i = 0;
	min = NULL;
	while (s)
	{
		if (!s->luma_ex)
		{
			if (c->luma_rev)
				cost = calc_move_cost(c, calc_pos_in(s, *c->a, false), i, NULL);
			else
				cost = calc_move_cost(c, i, calc_pos_in(s, *c->b, true), NULL);
			if (min == NULL || cost < min_cost)
			{
				min = s;
				min_cost = cost;
			}
		}
		s = s->next;
		i++;
	}
	if (min == NULL)
		return (true);
	if (depth > 0)
		*ret += min_cost;
	if (depth == 0)
	{
		if (c->luma_rev)
			calc_move_cost(c, calc_pos_in(min, *c->a, false),
				lst_indexof(*c->b, min), ops);
		else
			calc_move_cost(c, lst_indexof(*c->a, min),
				calc_pos_in(min, *c->b, true), ops);
		if (!apply_ops(c, &mem, ops))
			return (free_lst(&mem), false);
		lst_add(c->l, mem, NULL, false);
	}
	return (true);
}

static int	calc_pos_in(t_stack *e, t_stack *stack, bool desc)
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

static int	calc_move_cost(t_ctx *c, int ia, int ib, int ops[MAXOP])
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
	return ((ops && ops[PB - c->luma_rev]++), min + 1);
}
