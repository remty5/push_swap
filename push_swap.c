/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:18:11 by rvandepu          #+#    #+#             */
/*   Updated: 2024/05/21 03:46:22 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			ft_printf("%10u %11d |\n", a->s.cost, a->s.value);
			a_len--;
			a = a->next;
		}
		else if (a_len < b_len)
		{
			ft_printf("%10s %11s | %-11d %u\n", "", "", b->s.value, b->s.cost);
			b_len--;
			b = b->next;
		}
		else
		{
			ft_printf("%10u %11d | %-11d %u\n", a->s.cost, a->s.value, b->s.value, b->s.cost);
			a = a->next;
			b = b->next;
		}
	}
	ft_printf("%10s %11c | %c\n", "", '-', '-');
	ft_printf("%10s %11c | %c\n", "", 'a', 'b');
}

int	count_asc(t_stack *s);

// TODO display "Error\n" on error and check that values are integers

int	main(int argc, char *argv[])
{
	t_stack (*a) = NULL, *b = NULL;
	t_oplist (*l) = NULL;
	int (i) = 0;
	t_ctx (c) = {.l = &l, .a = &a, .b = &b};
	while (++i < argc)
		if (!lst_add(&a, lst_create(STACK, ft_atoi(argv[i])), true))
			return (free_lst(&a), EXIT_FAILURE);
	print_stacks(a, b);
	sa(&c);
	pb(&c);
	print_stacks(a, b);
	ft_printf("number of sorted elements: %d\n", count_asc(a));
	ft_printf("number of operations: %d\n", lst_size(l));
	oplist_undo(&c, c.l);
	free_lst(c.l);
	print_stacks(a, b);
	ft_printf("number of sorted elements: %d\n", count_asc(a));
	ft_printf("number of operations: %d\n", lst_size(l));
	free_lst(c.a);
	free_lst(c.b);
	return (EXIT_SUCCESS);
}
