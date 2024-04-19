/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 05:40:45 by rvandepu          #+#    #+#             */
/*   Updated: 2024/04/19 05:13:01 by rvandepu         ###   ########.fr       */
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

void	sa(t_stack **a)
{
	ft_printf("sa\n");
	swap(a);
}

void	sb(t_stack **b)
{
	ft_printf("sb\n");
	swap(b);
}

void	ss(t_stack **a, t_stack **b)
{
	ft_printf("ss\n");
	swap(a);
	swap(b);
}
