/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:34:52 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/26 12:22:40 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_args(char *input)
{
	long	number;
	int		args_amount;

	args_amount = 0;
	while (*input)
	{
		while (*input == ' ')
			input++;
		number = ft_atoi(input);
		if (number > INT_MAX || number < INT_MIN)
			return (0);
		input += ft_numlen(number);
		args_amount++;
	}
	return (1);
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	t_plan	plan;

	if (is_sorted(stack_a))
		return ;
	if (stack_a->size == 2)
		return ((void)rotate(stack_a, 1, "ra\n"));
	if (stack_a->size == 3)
		return (sort_three(stack_a));
	push(stack_a, stack_b, "pb\n");
	if (stack_a->size > 3)
		push(stack_a, stack_b, "pb\n");
	while (stack_a->size > 3)
	{
		plan = best_plan_ab(stack_a, stack_b);
		execute_plan(plan, stack_a, stack_b);
	}
	sort_three(stack_a);
	push_back(stack_a, stack_b);
	rotate_a_to_top(stack_a);
}

void	sort_three(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	if (is_sorted(stack))
		return ;
	a = stack->top->index;
	b = stack->top->next->index;
	c = stack->top->next->next->index;
	if (a < c && c < b)
	{
		swap(stack, "sa\n");
		rotate(stack, 1, "ra\n");
	}
	else if (b < a && a < c)
		swap(stack, "sa\n");
	else if (b < c && c < a)
		rotate(stack, 1, "ra\n");
	else if (c < a && a < b)
		reverse(stack, 1, "rra\n");
	else if (c < b && b < a)
	{
		swap(stack, "sa\n");
		reverse(stack, 1, "rra\n");
	}
}

/* void	print_stack_dbg(t_stack *stack_a, char *text)
{
	t_node	*head;
	int		i;
	t_node	*temp;
	int		i;

	head = stack_a->top;
	i = 0;
	printf("--------------\n");
	printf("%s\n", text);
	printf("Stack size: %i\n", stack_a->size);
	while (i < stack_a->size)
	{
		printf("%i	idx -> %i\n", head->value, head->index);
		head = head->next;
		i++;
	}
	printf("--------------\n");
} */
