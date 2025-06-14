/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:34:52 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/02 00:34:52 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc != 2)
		return(1);
	// checks for invalid chars and out of bounds numbers
	// throws ft_error before any allocation
	check_args(argv[1]);
	init_stacks(&stack_a, &stack_b);
	load_stack(&stack_a, argv[1]);
	if (stack_a.size < 2)
	{
		ft_error();
		return(1);
	}
	push_swap(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

void	load_stack(t_stack *stack_a, char *list)
{
	int		element;
	t_node	*node;

	while(*list)
	{
		element = get_next_element(&list); // this also increments list
		node = new_node(element);
		if (!node)
			return (free_stack(stack_a), NULL);
		stack_add_bottom(stack_a, node);
	}
	put_sorted_indexes(stack_a);
}

void	stack_add_bottom(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
	if (stack->top == NULL)
	{
		node->next = node;
		node->prev = node;
		stack->top = node;
		stack->size++;
		return ;
	}
	node->prev = stack->top->prev;
	node->next = stack->top;
	stack->top->prev->next = node;
	stack->top->prev = node;
	stack->size++;
}

long	get_next_element(char **list)
{
	long	element;

	while(**list == ' ')
		(*list)++;
	element = ft_atoi(*list);
	*list += ft_numlen(element);
	return (element);
}

int	in_bounds(long number)
{
	return (number <= INT_MAX && number >= INT_MIN);
}

void	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->head = NULL;
	stack_b->head = NULL;
	stack_a->tail = NULL;
	stack_b->tail = NULL;
	stack_a->size = 0;
	stack_b->size = 0;
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	t_plan	plan;

	if (stack_a->size <= 3)
		two_or_three(stack_a);
	push(stack_a, stack_b);
	push(stack_a, stack_b);
	i = 0;
	while (stack_a->size > 3)
	{
		plan = get_cheapest_plan(stack_a, stack_b);
		execute_plan(plan, stack_a, stack_b);
	}
	two_or_three(stack_a);
	while (stack_b->size > 0)
	{
		plan = get_insert_plan(stack_b, stack_a); // mirror of get_cheapest_plan
		execute_plan(plan, stack_b, stack_a);
	}
	rotate_to_min(stack_a);
}
