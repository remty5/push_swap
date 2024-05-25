/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luma.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/24 07:33:24 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// TODO remove
void	print_stacks(t_ctx *c, t_stack *a, t_stack *b);

void	apply_lst_ex(t_stack **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		arr[i++]->luma_ex = true;
}

static int	lis(t_ctx *c, bool apply)
{
	int (N) = lst_size(*c->a);
	t_stack **(X) = ft_calloc(N, sizeof(t_stack *));
	int *(P) = ft_calloc(N, sizeof(*P));
	int *(M) = ft_calloc(N + 1, sizeof(*M));
	int (L) = 0;
	int (i) = 0;
	t_stack *(s) = *c->a;
	while (s)
	{
		X[i] = s;
		t_i (lo) = 1;
		t_i (hi) = L + 1;
		while (lo < hi)
		{
			t_i (mid) = lo + (hi - lo) / 2;
			if (X[M[mid]]->value >= s->value)
				hi = mid;
			else
				lo = mid + 1;
		}
		t_i (newL) = lo;
		P[i] = M[newL - 1];
		M[newL] = i;
		if (newL > L)
			L = newL;
		s = s->next;
		i++;
	}
	t_stack **(S) = ft_calloc(L, sizeof(t_stack *));
	int (k) = M[L];
	i = L - 1;
	while (i >= 0)
	{
		S[i] = X[k];
		k = P[k];
		i--;
	}
	if (apply)
		apply_lst_ex(S, L);
	return (L);
}

// TODO delete this shit and focus on more important stuff

bool	find_apply_lis(t_ctx *c, int *max_len)
{
	static int	ops[MAXOP] = {0};
	int			max_n;
	int			lis_len;
	int			n;

	*max_len = 0;
	n = lst_size(*c->a) + 1;
	while (--n)
	{
		lis_len = lis(c, false);
		if (lis_len > *max_len)
		{
			*max_len = lis_len;
			max_n = n;
		}
		if (!ra(c))
			return (false);
	}
	free_lst(c->l);
	ops[RA] = lst_size(*c->a) - max_n;
	if (!apply_ops(c, c->l, ops))
		return (false);
	lis(c, true);
	undo_oplist(c, c->l);
	return (true);
}

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
	int	lis_len;

	//ft_printf("[luma] LIS phase\n");
	if (!find_apply_lis(c, &lis_len))
		return (false);
	//ft_printf("[luma] LIS result: len %d\n", lis_len);
	ft_bzero(ops, sizeof(ops));
	if (!pb(c) || !pb(c))
		return (false);
	(*c->b)->next->luma_ex = ((*c->b)->luma_ex = false);
	//ft_printf("[luma] phase 1\n");
	//print_stacks(c, *c->a, *c->b);
	while (c->a_len > lis_len)
	{
		if (!move_min_cost(c, NULL, 0))
			return (false);
		//print_stacks(c, *c->a, *c->b);
	}
	//ft_printf("[luma] phase 2\n");
	c->luma_rev = !c->luma_rev;
	while (c->b_len)
	{
		if (!move_min_cost(c, NULL, 0))
			return (false);
		//print_stacks(c, *c->a, *c->b);
	}
	c->luma_rev = !c->luma_rev;
	//ft_printf("[luma] fixup...\n");
	fixup(c, ops);
	if (!apply_ops(c, c->l, ops))
		return (false);
	//print_stacks(c, *c->a, *c->b);
	//ft_printf("\n");
	return (true);
}
