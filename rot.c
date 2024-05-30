/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:19:13 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/25 20:10:07 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack **start)
{
	t_stack	*end;

	if (!*start || !(*start)->next)
		return ;
	end = *start;
	while (end->next)
		end = end->next;
	end->next = *start;
	*start = (*start)->next;
	end->next->next = NULL;
}

bool	ra(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RA), NULL, false))
		return (false);
	rotate(c->a);
	return (true);
}

bool	rb(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RB), NULL, false))
		return (false);
	rotate(c->b);
	return (true);
}

bool	rr(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RR), NULL, false))
		return (false);
	rotate(c->a);
	rotate(c->b);
	return (true);
}
