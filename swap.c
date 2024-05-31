/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 05:40:45 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/31 17:59:17 by rvandepu         ###   ########.fr       */
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
	if (!lst_add(c->l, lst_create(OPLIST, SA), NULL, false))
		return (false);
	swap(c->a);
	return (true);
}

bool	sb(t_ctx *c)
{
	if (!lst_add(c->l, lst_create(OPLIST, SB), NULL, false))
		return (false);
	swap(c->b);
	return (true);
}

bool	ss(t_ctx *c)
{
	if (!lst_add(c->l, lst_create(OPLIST, SS), NULL, false))
		return (false);
	swap(c->a);
	swap(c->b);
	return (true);
}
