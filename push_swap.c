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

//	make complex logic only for A to B
//	B to A is simpler, cause A is already sorted, so just need to rotate until
//	(cur->next > idx > cur) for intermediate cases

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

	// print_stack_dbg(&stack_a, "UNSORTED STACK A:");
	// printf("MOVES:\n");

	push_swap(&stack_a, &stack_b);

	// print_stack_dbg(&stack_a, "SORTED STACK A:");

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

void	print_stack_dbg(t_stack *stack_a, char *text)
{
	t_node	*head;

	head = stack_a->top;
	int	i = 0;
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
	// print_stack_dbg(stack_a, "A UNSORTED 3:");
	sort_three(stack_a);
	// print_stack_dbg(stack_a, "A SORTED 3:");
	// print_stack_dbg(stack_b, "SORTED B:");
	push_back(stack_a, stack_b);
	rotate_a_to_top(stack_a);
}

void	push_back(t_stack *stack_a, t_stack *stack_b)
{
	int		idx_in_a;

	while (stack_b->size)
	{
		idx_in_a = find_idx_in_a(stack_a, stack_b->top->index);
		rotate_a_to_position(stack_a, idx_in_a);
		push(stack_b, stack_a, "pa\n");
	}
}

int	find_idx_in_a(t_stack *stack_a, int idx_from_b)
{
	int	big;
	int	small;

	big = biggest_idx(stack_a);
	small = smallest_idx(stack_a);
	if (idx_from_b > big || idx_from_b < small)
		return (small);
	return (find_mid_idx_a(stack_a, idx_from_b));
}

int	find_mid_idx_a(t_stack *stack_a, int idx_from_b)
{
	t_node	*current;
	int 	i;
	int		mid_idx;

	current = stack_a->top;
	i = 0;
	while (i < stack_a->size)
	{
		mid_idx = current->next->index;
		if (current->index < current->next->index)
		{
			if (current->index < idx_from_b && idx_from_b < current->next->index)
				break ;
		}
		current = current->next;
		i++;
	}
	return (mid_idx);
}

void	rotate_a_to_position(t_stack *stack_a, int idx)
{
	t_dir	dir;
	int		n_rot;

	n_rot = min_rotations_to(stack_a, idx, &dir);
	if (dir == DIRECT)
		rotate(stack_a, n_rot, "ra\n");
	else
		reverse(stack_a, n_rot, "rra\n");
}

void	execute_plan(t_plan plan, t_stack *stack_a, t_stack *stack_b)
{
	if (plan.dir_origin == plan.dir_dest)
		rotate_same_dir(&plan, stack_a, stack_b);
	if (plan.moves_origin)
	{
		if (plan.dir_origin == DIRECT)
			rotate(stack_a, plan.moves_origin, "ra\n");
		else
			reverse(stack_a, plan.moves_origin, "rra\n");
	}
	plan.moves_origin = 0;
	if (plan.moves_dest)
	{
		if (plan.dir_dest == DIRECT)
			rotate(stack_b, plan.moves_dest, "rb\n");
		else
			reverse(stack_b, plan.moves_dest, "rrb\n");
	}
	plan.moves_dest = 0;
	// print_stack_dbg(stack_b, "B BEFORE PUSH");
	push(stack_a, stack_b, "pb\n");
}

void	rotate_same_dir(t_plan *plan, t_stack *stack_a, t_stack *stack_b)
{
	while (plan->moves_origin && plan->moves_dest)
	{
		if (plan->dir_origin == DIRECT)
			rr(stack_a, stack_b);
		else
			rrr(stack_a, stack_b);
		plan->moves_origin--;
		plan->moves_dest--;
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

	times_rotated = 0;
	while (times--)
	{
		stack->top = stack->top->prev;
		ft_putstr_fd(move, 1);
		times_rotated++;
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

t_plan	best_plan_ab(t_stack *stack_a, t_stack *stack_b)
{
	t_plan	best;
	t_plan	plan;
    t_node	*current;
    int		i;

	current = stack_a->top;
	i = -1;
	while (++i < stack_a->size)
	{
		plan.moves_origin = i;
		plan.dir_origin = DIRECT;
		if (i > stack_a->size / 2)
		{
			plan.moves_origin = stack_a->size - i;
			plan.dir_origin = REVERSE;
		}
		calc_b_moves(&plan, stack_b, current->index);
		wrap_plan(&plan);
		if (i == 0 || plan.total_cost < best.total_cost)
        	best = plan;
		current = current->next;
	}
	return (best);
}

void	calc_b_moves(t_plan *plan, t_stack *stack_b, int idx)
{
	int	big;
	int	small;
	int	mid;

	big = biggest_idx(stack_b);
	small = smallest_idx(stack_b);
	plan->dir_dest = DIRECT;
	if (idx > big || idx < small)
		plan->moves_dest = min_rotations_to(stack_b, big, &plan->dir_dest);
	else
	{
		mid = find_mid_idx(stack_b, idx);
		plan->moves_dest = min_rotations_to(stack_b, mid, &plan->dir_dest);
	}
}

int	find_mid_idx(t_stack *stack_b, int new_idx)
{
	t_node	*current;
	int 	i;
	int		mid_idx;

	current = stack_b->top;
	i = 0;
	while (i < stack_b->size)
	{
		mid_idx = current->next->index;
		if (current->index > current->next->index)
		{
			if (current->index > new_idx && new_idx > current->next->index)
				break ;
		}
		current = current->next;
		i++;
	}
	return (mid_idx);
}

int	min_rotations_to(t_stack *stack, int idx, t_dir *dir)
{
	int	rot_direct;
	int	rot_reverse;

	rot_direct = min_rot_direct(stack, idx);
	rot_reverse = min_rot_reverse(stack, idx);
	if (rot_direct <= rot_reverse)
	{
		*dir = DIRECT;
		return (rot_direct);
	}
	*dir = REVERSE;
	return (rot_reverse);
}

int	min_rot_direct(t_stack *stack, int idx)
{
	int		rot_direct;
	t_node	*node;

	node = stack->top;
	rot_direct = 0;
	while (rot_direct < stack->size)
	{
		if (idx == node->index)
			break ;
		node = node->next;
		rot_direct++;
	}
	return (rot_direct);
}

int	min_rot_reverse(t_stack *stack, int idx)
{
	int		rot_reverse;
	t_node	*node;

	node = stack->top;
	rot_reverse = 0;
	while (rot_reverse < stack->size)
	{
		if (idx == node->index)
			break ;
		node = node->prev;
		rot_reverse++;
	}
	return (rot_reverse);
}

int	biggest_idx(t_stack *stack)
{
	t_node	*node;
	int		biggest;
	int		i;

	node = stack->top;
	i = 0;
	while(i < stack->size)
	{
		if (i == 0 || node->index > biggest)
			biggest = node->index;
		node = node->next;
		i++;
	}
	return (biggest);
}

int	smallest_idx(t_stack *stack)
{
	t_node	*node;
	int		smallest;
	int		i;

	node = stack->top;
	i = 0;
	while(i < stack->size)
	{
		if (i == 0 || node->index < smallest)
			smallest = node->index;
		node = node->next;
		i++;
	}
	return (smallest);
}

void	calc_mid_position(t_plan *plan, t_stack *stack_b, int idx)
{
	t_node	*current;
	int		i;

	plan->dir_dest = DIRECT;
	current = stack_b->top;
	i = 1;
	while(i < stack_b->size)
	{
		plan->moves_dest = i;
		if (i > stack_b->size / 2)
		{
			plan->moves_dest = (stack_b->size / 2) - (i % (stack_b->size / 2));
			plan->dir_dest = REVERSE;
		}
		if (idx < current->index && idx > current->next->index)
			break ;
		current = current->next;
		i++;
	}
}

void	wrap_plan(t_plan *plan)
{
	if (plan->dir_dest == plan->dir_origin)
	{
		plan->total_cost = ft_max(plan->moves_dest, plan->moves_origin);
		return ;
	}
	plan->total_cost = plan->moves_dest + plan->moves_origin;
}

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
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
