/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:37:43 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/26 12:17:19 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		reinsert_after(t_node *position, t_node *node);
static t_node	*pop(t_stack *stack);

void	swap(t_stack *stack, char *move)
{
	t_node	*a;

	if (!stack || stack->size < 2)
		return ;
	a = pop(stack);
	reinsert_after(stack->top, a);
	stack->size++;
	ft_putstr_fd(move, 1);
}

void	push(t_stack *stack_1, t_stack *stack_2, char *move)
{
	t_node	*node;

	if (stack_1->size == 0)
		return;
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
	ft_putstr_fd(move, 1);
}

static void	reinsert_after(t_node *position, t_node *node)
{
	node->prev = position;
	node->next = position->next;
	position->next->prev = node;
	position->next = node;
}

static t_node	*pop(t_stack *stack)
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
