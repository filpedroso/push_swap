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

//	fix rr and rrr args

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc != 2)
		return(1);
	if (!check_args(argv[1]))
	{
		ft_putstr_fd("Error: check_args returned 0\n", 2);
		return(1);
	}
	init_stacks(&stack_a, &stack_b);
	load_stack(&stack_a, argv[1]);

	printf("UNSORTED STACK A:\n");
	dbg_print_indexes(&stack_a);
	printf("-----MOVES-----\n");

	push_swap(&stack_a, &stack_b);

	printf("---------------\n");
	printf("SORTED STACK A:\n");
	dbg_print_indexes(&stack_a);

	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

int	check_args(char *input)
{
	long	number;
	int		args_amount;

	args_amount = 0;
	while(*input)
	{
		while (*input == ' ')
			input++;
		number = ft_atoi(input);
		if (number > INT_MAX || number < INT_MIN)
			return (0);
		input += ft_numlen(number);
		args_amount++;
	}
	if (args_amount < 2)
		return (0);
	return (1);
}

void	print_stack_dbg(t_stack *stack_a)
{
	t_node	*head;

	head = stack_a->top;
	int	i = 0;
	printf("Stack size: %i\n", stack_a->size);
	while (i < stack_a->size)
	{
		printf("%i\n", head->value);
		head = head->next;
		i++;
	}
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
	if (has_duplicate(stack_a))
	{
		free_stack(stack_a);
		ft_putstr_fd("Error: has duplicate\n", 2);
		exit(1);
	}
	put_sorted_indexes(stack_a);
}


int	has_duplicate(t_stack *stack)
{
	t_node	*head;
	t_node	*head_2;
	int		i;
	int		j;

	head = stack->top;
	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		head_2 = head->next;
		while (j < stack->size)
		{
			if (head->value == head_2->value)
				return (1);
			head_2 = head_2->next;
			j++;
		}
		head = head->next;
		i++;
	}
	return (0);
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

void	dbg_print_indexes(t_stack *stack)
{
	t_node	*head;

	head = stack->top;
	int	i = 0;
	while (i < stack->size)
	{
		printf("%i	idx-> %i\n", head->value, head->index);
		head = head->next;
		i++;
	}
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	t_plan	plan;

	if (is_sorted(stack_a))
		return ;
	if (stack_a->size == 2)
		return ((void)rotate(stack_a, 1, "ra\n"));
	if (stack_a->size == 3)
		return(sort_three(stack_a));
	push(stack_a, stack_b, "pb\n");
	if (stack_a->size > 3)
		push(stack_a, stack_b, "pb\n");
	while (stack_a->size > 3)
	{
		plan = best_plan_ab(stack_a, stack_b);
		execute_plan(plan, stack_a, stack_b);
	}
	sort_three(stack_a);
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
		rotate_same_dir(&plan, stack_a, stack_b);
	if (plan.a_moves)
	{
		if (plan.a_direction == ROTATE)
			plan.a_moves -= rotate(stack_a, plan.a_moves, "ra\n");
		else
			plan.a_moves -= reverse(stack_a, plan.a_moves, "rra1\n");
	}
	if (plan.b_moves)
	{
		if (plan.b_direction == ROTATE)
			plan.b_moves -= rotate(stack_b, plan.b_moves, "rb\n");
		else
			plan.b_moves -= reverse(stack_b, plan.b_moves, "rrb\n");
	}
	if (plan.push_flow == A_B)
	{
		push(stack_a, stack_b, "pb\n");
	}
	else if (plan.push_flow == B_A)
	{
		push(stack_b, stack_a, "pa\n");
	}
}

void	rotate_same_dir(t_plan *plan, t_stack *stack_a, t_stack *stack_b)
{
	while (plan->a_moves && plan->b_moves)
	{
		if (plan->a_direction == ROTATE)
			rr(stack_a, stack_b);
		else
			rrr(stack_a, stack_b);
		plan->a_moves--;
		plan->b_moves--;
	}
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = stack_a->top->next;
	stack_b->top = stack_b->top->next;
	ft_putstr_fd("rr\n", 1);
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = stack_a->top->prev;
	stack_b->top = stack_b->top->prev;
	ft_putstr_fd("rrr\n", 1);
}

int	rotate(t_stack *stack, int times, char *move)
{
	int	times_rotated;

	times_rotated = 0;
	while (times > 0)
	{
		stack->top = stack->top->next;
		ft_putstr_fd(move, 1);
		times_rotated++;
		times--;
	}
	return (times_rotated);
}

int	reverse(t_stack *stack, int times, char *move)
{
	int	times_rotated;

	times_rotated = 0;
	while (times > 0)
	{
		stack->top = stack->top->prev;
		ft_putstr_fd(move, 1);
		times_rotated++;
		times--;
	}
	return (times_rotated);
}

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

void	rotate_to_min(t_stack *stack)
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
	best.push_flow = A_B;
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
	best.push_flow = B_A;
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
    t_node *current = stack_b->top;
    int i = 0;
    int pos = 0;
    int min_diff = INT_MAX;
    int min_index = INT_MAX;
    int min_pos = 0;

    // Find the position before the largest index < sorted_idx
    while (i < stack_b->size)
    {
        if (current->index < sorted_idx && sorted_idx - current->index < min_diff)
        {
            min_diff = sorted_idx - current->index;
            pos = i;
        }
        if (current->index < min_index)
        {
            min_index = current->index;
            min_pos = i;
        }
        current = current->next;
        i++;
    }
    // If no index < sorted_idx, insert after the min (i.e., at the bottom)
    return (min_diff == INT_MAX) ? (min_pos + 1) % stack_b->size : pos;
}


int find_a_insert_pos(t_stack *stack_a, int sorted_idx)
{
    t_node *current = stack_a->top;
    int i = 0;
    int pos = 0;
    int min_diff = INT_MAX;
    int max_index = INT_MIN;
    int max_pos = 0;

    // Find the position before the smallest index > sorted_idx
    while (i < stack_a->size)
    {
        if (current->index > sorted_idx && current->index - sorted_idx < min_diff)
        {
            min_diff = current->index - sorted_idx;
            pos = i;
        }
        if (current->index > max_index)
        {
            max_index = current->index;
            max_pos = i;
        }
        current = current->next;
        i++;
    }
    // If no index > sorted_idx, insert after the max (i.e., at the bottom)
    return (min_diff == INT_MAX) ? (max_pos + 1) % stack_a->size : pos;
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
	if (a < c && c < b)			// 132 | 312 | 123
	{
		swap(stack, "sa\n");
		rotate(stack, 1, "ra\n");
	}
	else if (b < a && a < c)	// 213 | 123
		swap(stack, "sa\n");
	else if (b < c && c < a)	// 312 | 123
		rotate(stack, 1, "ra\n");
	else if (c < a && a < b)	// 231 | 123
		reverse(stack, 1, "rra\n");
	else if (c < b && b < a)	// 321 | 231 | 123
	{
		swap(stack, "sa\n");
		reverse(stack, 1, "rra\n");
	}
}

void	swap(t_stack *stack, char *move)
{
	t_node	*a;

	if (!stack || stack->size < 2)
		return;
	a = pop(stack);
	reinsert_after(stack->top, a);
	stack->size++;
	ft_putstr_fd(move, 1);
}

void	reinsert_after(t_node *position, t_node *node)
{
	node->prev = position;
	node->next = position->next;
	position->next->prev = node;
	position->next = node;

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
	ft_putstr_fd(move, 1);
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
	len = 1;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

long	ft_atoi(const char *str)
{
	int	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		str++;
		sign = -sign;
	}
	if (!*str || *str < '0' || *str > '9')
		return (LONG_MAX);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}
