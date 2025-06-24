/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:53:58 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:53:58 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	t_node	*temp;
	int		i;

	i = -1;
	while (++i < stack->size)
	{
		temp = stack->top->next;
		free(stack->top);
		stack->top = temp;
	}
	stack->top = NULL;
	stack->size = 0;
}

void	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = NULL;
	stack_b->top = NULL;
	stack_a->size = 0;
	stack_b->size = 0;
}

void	rotate_a_to_top(t_stack *stack)
{
	if (stack->top->index > stack->size / 2)
	{
		while (stack->top->index != 0)
			rotate(stack, 1, "ra\n");
	}
	else
	{
		while (stack->top->index != 0)
			reverse(stack, 1, "rra\n");
	}
}

int	is_sorted(t_stack *stack)
{
	t_node	*node;
	int		i;

	node = stack->top;
	i = 0;
	while (i < stack->size)
	{
		if (i != node->index)
			return (0);
		node = node->next;
		i++;
	}
	return (1);
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
