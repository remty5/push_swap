/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luma.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/23 07:40:11 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// TODO remove
void	print_stacks(t_ctx *c, t_stack *a, t_stack *b);

/*static void	switch_stacks(t_ctx *c)
{
	t_stack	**tmp;
	int		tint;

	tmp = c->a;
	c->a = c->b;
	c->b = tmp;
	tint = c->a_len;
	c->a_len = c->b_len;
	c->b_len = tint;
	c->luma_rev = !c->luma_rev;
}*/

static void	fixup(t_ctx *c, int ops[MAXOP])
{
	t_stack	*min;
	t_stack	*s;
	int		p;
	int		n;

	s = *c->a;
	min = s;
	while (s)
	{
		if (s->value < min->value)
			min = s;
		s = s->next;
	}
	p = lst_indexof(*c->a, min);
	n = c->a_len - p;
	if (p <= n)
		ops[RA] = p;
	else
		ops[RRA] = n;
}

bool	luma(t_ctx *c)
{
	int	ops[MAXOP];

	ft_bzero(ops, sizeof(int [MAXOP]));
	if (!pb(c) || !pb(c))
		return (false);
	//ft_printf("[luma] phase 1\n");
	//print_stacks(c, *c->a, *c->b);
	while (c->a_len > 2)
	{
		if (!move_min_cost(c, NULL, 0))
			return (false);
		//print_stacks(c, *c->a, *c->b);
	}
	//ft_printf("[luma] phase 2\n");
	//ft_printf("[luma] phase 2, switching stacks\n");
	//switch_stacks(c);
	c->luma_rev = !c->luma_rev;
	while (c->b_len)
	{
		if (!move_min_cost(c, NULL, 0))
			return (false);
		//print_stacks(c, *c->a, *c->b);
	}
	//ft_printf("[luma] switching stacks back\n");
	//switch_stacks(c);
	c->luma_rev = !c->luma_rev;
	//print_stacks(c, *c->a, *c->b);
	//ft_printf("[luma] fixup...\n");
	fixup(c, ops);
	if (!apply_ops(c, c->l, ops))
		return (false);
	//print_stacks(c, *c->a, *c->b);
	//ft_printf("\n");
	return (true);
}
