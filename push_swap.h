/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:02:32 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/02 22:02:32 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

/* ************************************************************************** */
/*                              INSTRUCTIONS                                  */
/* ************************************************************************** */

# define SA		1
# define SB		2
# define SS		3
# define PA		4
# define PB		5
# define RA		6
# define RB		7
# define RR		8
# define RRA	9
# define RRB	10
# define RRR	11


/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */


typedef enum	e_dir
{
    ROTATE,
    REVERSE
}				t_dir;


typedef enum	e_flow
{
    A_B,
    B_A
}				t_flow;


/* ************************************************************************** */
/*                                 STRUCTS                                    */
/* ************************************************************************** */


typedef struct		s_node
{
    long			value;
    int				index;
    struct s_node	*next;
    struct s_node	*prev;
}					t_node;


typedef struct	s_stack
{
	t_node		*head;
	t_node		*tail;
	int			size;
}				t_stack;


typedef struct	s_plan
{
    int			a_index;
    int			b_index;
    int			a_moves;
    int			b_moves;
    t_dir		a_direction;
    t_dir		b_direction;
    int			total_cost;
    t_flow		push_flow;
}				t_plan;


/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */


void	push_swap(t_stack *stack_a, t_stack *stack_b);


#endif