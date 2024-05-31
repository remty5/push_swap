/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 04:09:34 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 17:59:27 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	push(t_stack **from, t_stack **to)
{
	t_stack	*node;

	if (!*from)
		return (false);
	node = *from;
	*from = (*from)->next;
	node->next = *to;
	*to = node;
	return (true);
}

bool	pa(t_ctx *c)
{
	if (!lst_add(c->l, lst_create(OPLIST, PA), NULL, false))
		return (false);
	if (push(c->b, c->a))
	{
		c->b_len--;
		c->a_len++;
	}
	return (true);
}

bool	pb(t_ctx *c)
{
	if (!lst_add(c->l, lst_create(OPLIST, PB), NULL, false))
		return (false);
	if (push(c->a, c->b))
	{
		c->a_len--;
		c->b_len++;
	}
	return (true);
}
