/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 04:09:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 03:13:01 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack **from, t_stack **to)
{
	t_stack	*node;

	if (!*from)
		return ;
	node = *from;
	*from = (*from)->next;
	node->next = *to;
	*to = node;
}

bool	pa(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, PA), false))
		return (false);
	ft_printf("pa\n");
	push(c->b, c->a);
	return (true);
}

bool	pb(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, PB), false))
		return (false);
	ft_printf("pb\n");
	push(c->a, c->b);
	return (true);
}
