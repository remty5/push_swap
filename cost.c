/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:10:14 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/23 03:56:00 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// TODO Longest Increasing Subsequence problem
int	count_asc(t_stack *s)
{
	t_val	last;
	int		n;

	if (!s)
		return (0);
	n = 1;
	last = s->value;
	while (s)
	{
		if (last < s->value)
		{
			last = s->value;
			n++;
		}
		s = s->next;
	}
	return (n);
}

// TODO move these when splitting
static int	calc_b_index(t_ctx *c, t_stack *a);
static int	calc_move_cost(t_ctx *c, int ia, int ib, int ops[MAXOP]);
// TODO del this
void	print_stacks(t_ctx *c, t_stack *a, t_stack *b);

#include <limits.h>

bool	move_min_cost(t_ctx *c, int *ret, int depth)
{
	t_oplist	*mem;
	t_stack		*s;
	int			s_i;
	static int	ops[MAXOP];
	char		d[COSTMAXDEPTH + 2];
	int			bi;
	// TODO get rid of cheapest stack pointer, keep indexes in a & b
	t_stack		*cheapest;
	int			cheapest_cost;
	int			cost;

	ft_bzero(d, COSTMAXDEPTH + 2);
	ft_memset(d, '\t', depth);
	//ft_printf("%s[move_min_cost d:%d] ret: %p\n\tprinting...\n", d, depth, ret);
	//print_stacks(c, *c->a, *c->b);
	mem = NULL;
	if (depth > COSTMAXDEPTH)
		return (ft_printf("%s[move_min_cost d:%d] max depth exceeded, returning\n", d, depth), print_stacks(c, *c->a, *c->b), true);
	s = *c->a;
	s_i = 0;
	cheapest = NULL;
	while (s)
	{
		ft_printf("%s[move_min_cost d:%d] s %p: {.value = %d, .next = %p}\n", d, depth, s, s->value, s->next);
		print_stacks(c, *c->a, *c->b);
		bi = calc_b_index(c, s);
		cost = calc_move_cost(c, s_i, bi, ops);
		ft_printf("%s[move_min_cost d:%d] cost: %d for si: %d bi: %d\n", d, depth, cost, s_i, bi);
		if (depth <= COSTMAXDEPTH)
		{
			ft_printf("%s[move_min_cost d:%d] not at max depth, continuing...\n", d, depth);
			//ft_printf("%s[move_min_cost d:%d] ops listing:\n\tPA: %d\n\tPB: %d\n\tRA: %d\n\tRB: %d\n\tRR: %d\n\tRRA: %d\n\tRRB: %d\n\tRRR: %d\n", d, depth, ops[PA], ops[PB], ops[RA], ops[RB], ops[RR], ops[RRA], ops[RRB], ops[RRR]);
			ft_printf("%s[move_min_cost d:%d] applying ops...\n", d, depth);
			if (!apply_ops(c, &mem, ops))
				return (false);
			//ft_printf("%s[move_min_cost d:%d] ops listing:\n\tPA: %d\n\tPB: %d\n\tRA: %d\n\tRB: %d\n\tRR: %d\n\tRRA: %d\n\tRRB: %d\n\tRRR: %d\n", d, depth, ops[PA], ops[PB], ops[RA], ops[RB], ops[RR], ops[RRA], ops[RRB], ops[RRR]);
			ft_printf("%s[move_min_cost d:%d] recursing...\n", d, depth);
			// TODO dont recurse if not necessary
			if (!move_min_cost(c, &cost, depth + 1))
				return (false);
			ft_printf("%s[move_min_cost d:%d] cost is now: %d\n", d, depth, cost);
			ft_printf("%s[move_min_cost d:%d] undoing...\n", d, depth);
			oplist_undo(c, &mem);
		}
		if (cheapest == NULL || cost < cheapest_cost)
		{
			ft_printf("%s[move_min_cost d:%d] CHEAPEST IS NOW s %p: {.value = %d, .next = %p} with cost: %d\n", d, depth, s, s->value, s->next, cost);
			cheapest = s;
			cheapest_cost = cost;
		}
		s = s->next;
		s_i++;
	}
	if (cheapest == NULL)
		return (true);
	ft_printf("%s[move_min_cost d:%d] cheapest s %p: {.value = %d, .next = %p} with cost: %d\n", d, depth, cheapest, cheapest->value, cheapest->next, cheapest_cost);
	if (depth > 0)
		*ret += cheapest_cost;
	if (depth == 0)
	{
		calc_move_cost(c, lst_indexof(*c->a, cheapest), calc_b_index(c, cheapest), ops);
		if (!apply_ops(c, &mem, ops))
			return (false);
		lst_add(c->l, mem, NULL, false);
	}
	return (true);
}

static int	calc_b_index(t_ctx *c, t_stack *a)
{
	t_stack	*min;
	t_stack	*max;
	t_stack	*s;

	s = *c->b;
	max = s;
	min = s;
	while (s)
	{
		if (s->value < min->value)
			min = s;
		else if (s->value > max->value)
			max = s;
		s = s->next;
	}
	//ft_printf("[calc_b_index] max s %p: {.value = %d, .next = %p}\n", max, max->value, max->next);
	//ft_printf("[calc_b_index] min s %p: {.value = %d, .next = %p}\n", min, min->value, min->next);
	if (a->value < min->value || max->value < a->value)
		return (lst_indexof(*c->b, max));
	s = max;
	while (s->value > a->value)
	{
		s = s->next;
		if (!s)
			s = *c->b;
	}
	return (lst_indexof(*c->b, s));
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
	return ((ops && ops[PB]++), min + 1);
}
