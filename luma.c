/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luma.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/30 19:23:18 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	normalize(t_ctx *c)
{
	t_stack	*new;
	t_stack	*curr;
	t_stack	*s;
	t_val	v;

	new = NULL;
	curr = *c->a;
	while (curr)
	{
		v = 0;
		s = *c->a;
		while (s)
		{
			if (s->value < curr->value)
				v++;
			s = s->next;
		}
		if (!lst_add(&new, lst_create(STACK, v), NULL, false))
			return (free_lst(&new), false);
		curr = curr->next;
	}
	free_lst(c->a);
	*c->a = new;
	return (true);
}

bool	do_split(t_ctx *c, t_val len)
{
	t_val	a;
	t_val	b;
	t_val	v;

	a = len / 3;
	b = len - a;
	v = (*c->a)->value;
	if ((v < b && !pb(c)) // first 2/3
		|| (a < v && v < b && !rb(c)) // middle 1/3
		|| (b <= v && !ra(c))) // last 1/3
		return (false);
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
	return (apply_ops(c, c->l, ops));
}

void	print_stacks(t_ctx *c, t_stack *a, t_stack *b);

bool	luma(t_ctx *c)
{
	t_val	a;
	t_val	b;
	t_val	v;
	t_val	len;

	//ft_printf("[luma] phase 1\n");
	//print_stacks(c, *c->a, *c->b);
	if (c->a_len > 90)
	{
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
	}
	else
	{
		if (!pb(c) || !pb(c))
			return (false);
		while (c->a_len > 2)
		{
			if (!move_min_cost(c))
				return (false);
			//print_stacks(c, *c->a, *c->b);
		}
	}
	//ft_printf("[luma] phase 2\n");
	c->luma_rev = !c->luma_rev;
	while (c->b_len)
	{
		if (!move_min_cost(c))
			return (false);
		//print_stacks(c, *c->a, *c->b);
	}
	c->luma_rev = !c->luma_rev;
	//ft_printf("[luma] fixup...\n");
	if (!fixup(c))
		return (false);
	//print_stacks(c, *c->a, *c->b);
	//ft_printf("\n");
	return (true);
}
