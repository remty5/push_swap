/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 19:03:51 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_sorted(t_ctx *c)
{
	t_stack	*min;
	t_stack	*s;
	t_stack	*next;

	s = *c->a;
	min = s;
	while (s)
	{
		if (s->value < min->value)
			min = s;
		s = s->next;
	}
	s = min;
	while (s)
	{
		next = s->next;
		if (!next)
			next = *c->a;
		if (next == min)
			break ;
		if (s->value > next->value)
			return (false);
		s = next;
	}
	return (true);
}

bool	fixup(t_ctx *c)
{
	int		ops[MAXOP];
	t_stack	*max;
	t_stack	*s;
	int		i;

	if (*c->a == NULL)
		return (false);
	ft_bzero(ops, sizeof(ops));
	s = *c->a;
	max = s;
	while (s)
	{
		if (s->value > max->value)
			max = s;
		s = s->next;
	}
	i = lst_indexof(*c->a, max);
	if (i + 1 < c->a_len - i - 1)
		ops[RA] = i + 1;
	else
		ops[RRA] = c->a_len - i - 1;
	return (apply_ops(c, NULL, ops));
}

// Thanks kodokai for this optimization
static bool	do_split(t_ctx *c)
{
	t_val	len;
	t_val	a;
	t_val	b;
	t_val	v;

	len = c->a_len;
	while (c->a_len > len / 3)
	{
		a = len / 3;
		b = len - a;
		v = (*c->a)->value;
		if ((v < b && !pb(c))
			|| (b <= v && !ra(c))
			|| (a < v && v < b && !rb(c)))
			return (false);
	}
	while (c->a_len > 2)
		if (!pb(c))
			return (false);
	return (true);
}

bool	sort(t_ctx *c)
{
	if (c->a_len > 90)
		do_split(c);
	else
	{
		if (!pb(c) || !pb(c))
			return (false);
		while (c->a_len > 2)
			if (!move_min_cost(c))
				return (false);
	}
	c->turk_rev = !c->turk_rev;
	while (c->b_len)
		if (!move_min_cost(c))
			return (false);
	c->turk_rev = !c->turk_rev;
	if (!fixup(c))
		return (false);
	return (true);
}
