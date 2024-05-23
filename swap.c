/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 05:40:45 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 03:13:00 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack **start)
{
	t_stack	*node;

	if (!*start || !(*start)->next)
		return ;
	node = *start;
	*start = (*start)->next;
	node->next = (*start)->next;
	(*start)->next = node;
}

bool	sa(t_ctx *c)
{
	(void) c->b;
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, SA), false))
		return (false);
	ft_printf("sa\n");
	swap(c->a);
	return (true);
}

bool	sb(t_ctx *c)
{
	(void) c->a;
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, SB), false))
		return (false);
	ft_printf("sb\n");
	swap(c->b);
	return (true);
}

bool	ss(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, SS), false))
		return (false);
	ft_printf("ss\n");
	swap(c->a);
	swap(c->b);
	return (true);
}
