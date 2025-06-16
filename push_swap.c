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

//	TODO:
//	check_args()
//	swap()
//	ft_error()
//	rr and rrr args

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc != 2)
		return(1);
	// checks for invalid chars and out of bounds numbers
	// throws ft_error before any allocation
	if (!check_args(argv[1]))
		return (0);
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
			return (free_stack(stack_a));
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
	stack_a->top = NULL;
	stack_b->top = NULL;
	stack_a->size = 0;
	stack_b->size = 0;
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	t_plan	plan;

	if (is_sorted(stack_a))
		return ;
	if (stack_a->size <= 3)
		return (three_elements(stack_a));
	push(stack_a, stack_b, "pb");
	push(stack_a, stack_b, "pb");
	i = 0;
	while (stack_a->size > 3)
	{
		plan = best_plan_ab(stack_a, stack_b);
		execute_plan(plan, stack_a, stack_b);
	}
	three_elements(stack_a);
	while (stack_b->size > 0)
	{
		plan = best_plan_ba(stack_b, stack_a); // mirror of get_cheapest_plan
		execute_plan(plan, stack_a, stack_b);
	}
	rotate_to_min(stack_a);
}

void	execute_plan(t_plan plan, t_stack *stack_a, t_stack *stack_b)
{
	if (plan.a_direction == plan.b_direction)
	{
		if (plan.a_direction == ROTATE)
			rr(stack_a, stack_b, plan.a_moves, plan.b_moves);
		else if (plan.a_direction == REVERSE)
			rrr(stack_a, stack_b, plan.a_moves, plan.b_moves);
	}
	else
	{
		if (plan.a_direction == ROTATE)
			rotate(stack_a, plan.a_moves, "ra");
		else if (plan.a_direction == REVERSE)
			reverse(stack_a, plan.a_moves, "rra");
		if (plan.b_direction == ROTATE)
			rotate(stack_b, plan.a_moves, "rb");
		else if (plan.b_direction == REVERSE)
			reverse(stack_b, plan.a_moves, "rrb");
	}
	if (plan.push_flow == A_B)
		push(stack_a, stack_b, "pb");
	else if (plan.push_flow == B_A)
		push(stack_b, stack_a, "pa");
}

void	rr(t_stack *stack_a, t_stack *stack_b, int times, char *move)
{
	while (times--)
	{
		stack_a->top = stack_a->top->next;
		stack_b->top = stack_b->top->next;
		write (1, move, 2);
		write (1, "\n", 1);
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b, int times, char *move)
{
	while (times--)
	{
		stack_a->top = stack_a->top->prev;
		stack_b->top = stack_b->top->prev;
		write (1, move, 3);
		write (1, "\n", 1);
	}
}

void	rotate(t_stack *stack, int times, char *move)
{
	while (times--)
	{
		stack->top = stack->top->next;
		write (1, move, 2);
		write (1, "\n", 1);
	}
}

void	reverse(t_stack *stack, int times, char *move)
{
	while (times--)
	{
		stack->top = stack->top->prev;
		write (1, move, 2);
		write (1, "\n", 1);
	}
}

void	rotate_to_min(t_stack *stack)
{
	if (stack->top->index == 0 || stack->top->index == -1)
		return ;
	stack->top = stack->top->next;
	rotate_to_min(stack);
}

t_plan	best_plan_ab(t_stack *stack_a, t_stack *stack_b)
{
	t_plan	best;
	t_plan	plan;
    t_node	*current;
    int		i;

	current = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		plan.a_index = i;
		plan.b_index = find_b_insert_pos(stack_b, current->index);
		calc_moves(&plan, stack_a, stack_b);
		if (plan.a_direction == plan.b_direction)
			plan.total_cost = ft_max(plan.a_moves, plan.b_moves);
		else
			plan.total_cost = plan.a_moves + plan.b_moves;
		if (i == 0 || plan.total_cost < best.total_cost)
        	best = plan;
		current = current->next;
		i++;
	}
	return (best);
}

t_plan	best_plan_ba(t_stack *stack_b, t_stack *stack_a)
{
	t_plan	best;
	t_plan	plan;
    t_node	*current;
    int		i;

	current = stack_b->top;
	i = 0;
	while (i < stack_b->size)
	{
		plan.b_index = i;
		plan.a_index = find_a_insert_pos(stack_a, current->index);
		calc_moves(&plan, stack_b, stack_a);
		if (plan.b_direction == plan.a_direction)
			plan.total_cost = ft_max(plan.b_moves, plan.a_moves);
		else
			plan.total_cost = plan.b_moves + plan.a_moves;
		if (i == 0 || plan.total_cost < best.total_cost)
        	best = plan;
		current = current->next;
		i++;
	}
	return (best);
}


int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int find_b_insert_pos(t_stack *stack_b, int sorted_idx)
{
	t_node	*current;
	int		i;

	if (stack_b->size == 0)
		return (0);
	if (sorted_idx > stack_b->top->index)
		return (0);
	if (sorted_idx < stack_b->top->prev->index)
		return (stack_b->size);
	current = stack_b->top;
	i = 0;
	while (i < stack_b->size)
	{
		if (current->index > sorted_idx && current->next->index < sorted_idx)
			return (i + 1);
		current = current->next;
		i++;
	}
	return (0);
}

int find_a_insert_pos(t_stack *stack_a, int sorted_idx)
{
	t_node	*current;
	int		i;

	if (stack_a->size == 0)
		return (0);
	if (sorted_idx < stack_a->top->index)
		return (0);
	if (sorted_idx > stack_a->top->prev->index)
		return (stack_a->size);
	current = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		if (current->index < sorted_idx && current->next->index > sorted_idx)
			return (i + 1);
		current = current->next;
		i++;
	}
	return (0);
}

void	calc_moves(t_plan *plan, t_stack *stack_1, t_stack *stack_2)
{
	calc_single_move(plan->a_index, stack_1->size,
		&plan->a_moves, &plan->a_direction);
	calc_single_move(plan->b_index, stack_2->size,
		&plan->b_moves, &plan->b_direction);
}

void	calc_single_move(int position, int size, int *moves, t_dir *dir)
{
    if (position <= size/2)
    {
        *moves = position;
        *dir = ROTATE;
    }
    else
    {
        *moves = size - position;
        *dir = REVERSE;
    }
}


int	is_sorted(t_stack *stack)
{
	int		stack_size;
	t_node	*node;
	int		i;

	stack_size = stack->size;
	node = stack->top;
	i = 0;
	while (i < stack_size)
	{
		if (i != node->index)
			return (0);
		node = node->next;
		i++;
	}
	return (1);
}

void	three_elements(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	if (is_sorted(stack))
		return ;
	a = stack->top->index;
	b = stack->top->next->index;
	c = stack->top->next->next->index;
	if (a < c && c < b)			// 132 | 312 | 123
	{
		swap(stack, "sa");
		rotate(stack, 1, "ra");
	}
	else if (b < a && a < c)	// 213 | 123
		swap(stack, "sa");
	else if (b < c && c < a)	// 312 | 123
		rotate(stack, 1, "ra");
	else if (c < a && a < b)	// 231 | 123
		reverse(stack, 1, "rra");
	else if (c < b && b < a)	// 321 | 231 | 123
	{
		swap(stack, "sa");
		reverse(stack, 1, "rra");
	}
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

int	ft_numlen(int num)
{
	int	len;

	if (num == INT_MIN)
		return (11);
	if (num < 0)
		num = -num;
	len = 1;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ')
		str++;
	if (*str == '-')
		sign = -sign;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}