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

void	put_sorted_indexes(t_stack *stack)
{
	int		index;
	int		i;
	t_node	*node;
	t_node	*min_node;

	index = -1;
	while (++index < stack->size)
	{
		node = stack->top;
		min_node = NULL;
		i = -1;
		while (++i < stack->size)
		{
			if (node->index == -1 && (!min_node || node->value < min_node->value))
				min_node = node;
			node = node->next;
		}
		min_node->index = index;
	}
}

t_node	*new_node(int element)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = element;
	node->index = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
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
	push(stack_a, stack_b, "pb");
	push(stack_a, stack_b, "pb");
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

void	push(t_stack *stack_1, t_stack *stack_2, char *move)
{
	t_node	*node;

	node = pop(stack_1);
	if (!node)
		return ;
	if (stack_2->top == NULL)
	{
		node->next = node;
		node->prev = node;
		stack_2->top = node;
	}
	else
	{
		node->next = stack_2->top;
		node->prev = stack_2->top->prev;
		stack_2->top->prev->next = node;
		stack_2->top->prev = node;
		stack_2->top = node;
	}
	stack_2->size++;
	write(1, move, 2);
	write(1, "\n", 1);
}

t_node	*pop(t_stack *stack)
{
	t_node	*node;

	if (!stack || !stack->top)
		return (NULL);
	node = stack->top;
	if (stack->size == 1)
		stack->top = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		stack->top = node->next;
	}
	stack->size--;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
