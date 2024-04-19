/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/04/19 05:53:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	stack_add(t_stack **start, int val)
{
	t_stack	**new;
	t_stack	*s;

	new = start;
	s = *start;
	while (s)
	{
		if (s->value == val)
			return (false);
		new = &s->next;
		s = s->next;
	}
	*new = malloc(sizeof(t_stack));
	if (*new == NULL)
		return (false);
	(*new)->value = val;
	(*new)->next = NULL;
	return (true);
}

static inline void	print_stacks(t_stack *a, t_stack *b)
{
	t_stack	*s;
	int		a_len;
	int		b_len;

	a_len = 0;
	s = a;
	while (s)
		s = (a_len++, s->next);
	b_len = 0;
	s = b;
	while (s)
		s = (b_len++, s->next);
	while (a || b)
	{
		if (a_len > b_len)
		{
			ft_printf("%11d |\n", a->value);
			a_len--;
			a = a->next;
		}
		else if (a_len < b_len)
		{
			ft_printf("%11s | %d\n", "", b->value);
			b_len--;
			b = b->next;
		}
		else
		{
			ft_printf("%11d | %d\n", a->value, b->value);
			a = a->next;
			b = b->next;
		}
	}
	ft_printf("%11c | %c\n", '-', '-');
	ft_printf("%11c | %c\n", 'a', 'b');
}

static void	free_stack(t_stack **s)
{
	t_stack	*to_free;

	while (*s)
	{
		to_free = *s;
		*s = (*s)->next;
		free(to_free);
	}
}

int	main(int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	a = NULL;
	b = NULL;
	i = 0;
	while (++i < argc)
		if (!stack_add(&a, ft_atoi(argv[i])))
			return (free_stack(&a), EXIT_FAILURE);
	pb(&a, &b);
	pb(&a, &b);
	print_stacks(a, b);
	rr(&a, &b);
	print_stacks(a, b);
	rrr(&a, &b);
	print_stacks(a, b);
	free_stack(&a);
	free_stack(&b);
	return (EXIT_SUCCESS);
}
