/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:42:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 05:47:41 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rrotate(t_stack **start)
{
	t_stack	**end;

	if (!*start || !(*start)->next)
		return ;
	end = start;
	while ((*end)->next)
		end = &(*end)->next;
	(*end)->next = *start;
	*start = *end;
	*end = NULL;
}

bool	rra(t_ctx *c)
{
	(void) c->b;
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RRA), NULL, false))
		return (false);
	ft_printf("rra\n");
	rrotate(c->a);
	return (true);
}

bool	rrb(t_ctx *c)
{
	(void) c->a;
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RRB), NULL, false))
		return (false);
	ft_printf("rrb\n");
	rrotate(c->b);
	return (true);
}

bool	rrr(t_ctx *c)
{
	if (!c->undo && !lst_add(c->l, lst_create(OPLIST, RRR), NULL, false))
		return (false);
	ft_printf("rrr\n");
	rrotate(c->a);
	rrotate(c->b);
	return (true);
}
