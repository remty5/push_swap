/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:41:33 by rvandepu          #+#    #+#             */
/*   Updated: 2024/06/03 20:53:27 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	parse_val(const char *val, t_val *ret)
{
	int		i;
	int		j;
	char	sign;
	long	n;

	while (*val == ' ' || ('\t' <= *val && *val <= '\r'))
		val++;
	sign = 1;
	if (*val == '-' || *val == '+')
		if (*(val++) == '-')
			sign = -sign;
	i = 0;
	while (val[i] == '0')
		i++;
	j = 0;
	n = 0;
	while ('0' <= val[i] && val[i] <= '9')
		n = (j++, n * 10 + (val[i++] - '0'));
	n = n * sign;
	if (i == 0 || j > 10 || n < INT_MIN || INT_MAX < n)
		return (false);
	*ret = n;
	return (val[i] == '\0');
}

bool	init_stacks(t_ctx *c, int argc, char **argv)
{
	t_val	val;
	int		i;

	*c->a = NULL;
	*c->b = NULL;
	*c->l = NULL;
	i = 0;
	while (++i < argc)
		if (!parse_val(argv[i], &val)
			|| !lst_add(c->a, lst_create(STACK, val), &c->a_len, true))
			return (false);
	if (!normalize(c))
		return (false);
	return (true);
}

bool	normalize(t_ctx *c)
{
	t_stack	*new;
	t_stack	*curr;
	t_stack	*s;
	t_val	v;

	new = NULL;
	curr = *c->a;
	while (curr)
	{
		v = 0;
		s = *c->a;
		while (s)
		{
			if (s->value < curr->value)
				v++;
			s = s->next;
		}
		if (!lst_add(&new, lst_create(STACK, v), NULL, false))
			return (free_lst(&new), false);
		curr = curr->next;
	}
	free_lst(c->a);
	*c->a = new;
	return (true);
}
