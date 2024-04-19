/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:42:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/04/19 05:51:36 by rvandepu         ###   ########.fr       */
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

void	rra(t_stack **a)
{
	ft_printf("rra\n");
	rrotate(a);
}

void	rrb(t_stack **b)
{
	ft_printf("rrb\n");
	rrotate(b);
}

void	rrr(t_stack **a, t_stack **b)
{
	ft_printf("rrr\n");
	rrotate(a);
	rrotate(b);
}
