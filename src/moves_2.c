/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:45:40 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:45:40 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_stack *stack_a, t_stack *stack_b, t_print print)
{
	if (!stack_a || !stack_a->top || stack_a->size == 0 || !stack_b
		|| !stack_b->top || stack_b->size == 0)
		return ;
	stack_a->top = stack_a->top->next;
	stack_b->top = stack_b->top->next;
	if (print)
		ft_putstr_fd("rr\n", 1);
}

void	rrr(t_stack *stack_a, t_stack *stack_b, t_print print)
{
	if (!stack_a || !stack_a->top || stack_a->size == 0 || !stack_b
		|| !stack_b->top || stack_b->size == 0)
		return ;
	stack_a->top = stack_a->top->prev;
	stack_b->top = stack_b->top->prev;
	if (print)
		ft_putstr_fd("rrr\n", 1);
}

int	rotate(t_stack *stack, int times, char *move)
{
	int	times_rotated;

	if (!stack || !stack->top || stack->size == 0)
		return (0);
	times_rotated = 0;
	while (times--)
	{
		stack->top = stack->top->next;
		ft_putstr_fd(move, 1);
		times_rotated++;
	}
	return (times_rotated);
}

int	reverse(t_stack *stack, int times, char *move)
{
	int	times_rotated;

	if (!stack || !stack->top || stack->size == 0)
		return (0);
	times_rotated = 0;
	while (times--)
	{
		stack->top = stack->top->prev;
		ft_putstr_fd(move, 1);
		times_rotated++;
	}
	return (times_rotated);
}
