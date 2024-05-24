/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luma.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/24 06:43:40 by rvandepu         ###   ########.fr       */
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

void	print_lst(t_stack *l)
{
	while (l)
	{
		if (l->next)
			ft_printf("%d, ", l->value);
		else
			ft_printf("%d\n", l->value);
		l = l->next;
	}
}

void	print_lst_arr(t_stack **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (i < len - 1)
			ft_printf("%d, ", arr[i]->value);
		else
			ft_printf("%d\n", arr[i]->value);
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (i < len - 1)
			ft_printf("%d, ", arr[i]->luma_ex);
		else
			ft_printf("%d\n", arr[i]->luma_ex);
		i++;
	}
}

void	print_arr(int *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (i < len - 1)
			ft_printf("%d, ", arr[i]);
		else
			ft_printf("%d\n", arr[i]);
		i++;
	}
}

void	apply_lst_ex(t_stack **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		arr[i++]->luma_ex = true;
}

// TODO Longest Increasing Subsequence problem
static int	lis(t_ctx *c, bool apply)
{
	(void)apply;
	int (N) = lst_size(*c->a);
	t_stack **(X) = ft_calloc(N, sizeof(t_stack *));
	int *(P) = ft_calloc(N, sizeof(*P));
	int *(M) = ft_calloc(N + 1, sizeof(*M));
	M[0] = -1;
	int (L) = 0;
	int (i) = 0;
	t_stack *(s) = *c->a;
	//ft_printf("[lis] X: ");
	//print_lst(s);
	while (s)
	{
		X[i] = s;
		//ft_printf("\n[lis] M: ");
		//print_arr(M, N + 1);
		//ft_printf("[lis] P: ");
		//print_arr(P, N);
		//ft_printf("[lis] s %p: {.value = %d)\n", s, s->value);
		t_i (lo) = 1;
		t_i (hi) = L + 1;
		//ft_printf("[lis] lo: %d, hi: %d\n", lo, hi);
		while (lo < hi)
		{
			t_i (mid) = lo + (hi - lo) / 2;
			//ft_printf("[lis] lo: %d, mid: %d, hi: %d\n", lo, mid, hi);
			//ft_printf("[lis] M[mid]: %d, X[M[mid]]: %d, X[i]: %d\n", M[mid], X[M[mid]]->value, s->value);
			if (X[M[mid]]->value >= s->value)
				hi = mid;
			else
				lo = mid + 1;
		}
		t_i (newL) = lo;
		//ft_printf("[lis] newL: %d\n", newL);
		P[i] = M[newL - 1];
		M[newL] = i;
		if (newL > L)
			L = newL;
		s = s->next;
		i++;
	}
	//ft_printf("\n[lis] done, reconstructing...\n");
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
	{
		apply_lst_ex(S, L);
		ft_printf("[lis] S\n");
		print_lst_arr(S, L);
	}
	return (L);
}

bool	find_apply_lis(t_ctx *c)
{
	static int	ops[MAXOP] = {0};
	int			max_len;
	int			max_n;
	int			lis_len;
	int			n;

	max_len = 0;
	n = lst_size(*c->a);
	int (i) = 0;
	while (n)
	{
		lis_len = lis(c, false);
		ft_printf("i: %d, len: %d\n", i++, lis_len);
		if (lis_len > max_len)
		{
			ft_printf("new max\n");
			max_len = lis_len;
			max_n = n;
		}
		if (!ra(c))
			return (false);
		n--;
	}
	free_lst(c->l);
	ops[RA] = lst_size(*c->a) - max_n;
	ft_printf("max len: %d at i: %d\n", max_len, ops[RA]);
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

	find_apply_lis(c);
	ft_bzero(ops, sizeof(ops));
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
