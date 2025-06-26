/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:26:49 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/26 20:07:39 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_sorted_indexes(t_stack *stack);
static long	get_next_element(char **list);
static int	has_duplicate(t_stack *stack);

void	load_stack(t_stack *stack_a, char *list)
{
	int		element;
	t_node	*node;
	char	*ptr;

	ptr = list;
	while (*list)
	{
		element = get_next_element(&list);
		node = new_node(element);
		if (!node)
			return (free_stack(stack_a));
		stack_add_bottom(stack_a, node);
	}
	if (has_duplicate(stack_a))
	{
		free(ptr);
		free_stack(stack_a);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	put_sorted_indexes(stack_a);
}

static int	has_duplicate(t_stack *stack)
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

static void	put_sorted_indexes(t_stack *stack)
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
			if (node->index == -1 && (!min_node
					|| node->value < min_node->value))
				min_node = node;
			node = node->next;
		}
		min_node->index = index;
	}
}

static long	get_next_element(char **list)
{
	long	element;

	while (**list == ' ')
		(*list)++;
	element = ft_atoi(*list);
	*list += ft_numlen(element);
	return (element);
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
