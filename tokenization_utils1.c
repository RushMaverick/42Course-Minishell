/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelaez- <jpelaez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:22:27 by jpelaez-          #+#    #+#             */
/*   Updated: 2023/07/20 17:31:37 by jpelaez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_type(char operator)
{
	if (operator== '>')
		return (RIGH_R);
	else if (operator== '<')
		return (LEFT_R);
	else
		return (PIPE);
	return (0);
}

int	tok_closed_quotes(char *str, int i, char quote)
{
	int	j;

	j = 0;
	if (str[i + j] == quote)
	{
		j++;
		while (str[i + j] != '\0' && str[i + j] != quote)
			j++;
		j++;
	}
	return (j);
}
int	check_delimiter(char c, char *delimiter)
{
	int	j;

	j = 0;
	while (delimiter[j] != '\0')
	{
		if (delimiter[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	is_whitespace(char *line, int i)
{
	char	*delimiter;
	int		j;

	j = 0;
	delimiter = " \f\n\r\t\v";
	while (check_delimiter(line[i + j], delimiter))
		j++;
	return (j);
}

int	check_token_type(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}


/*we have to delete this at the end*/

void	printList(t_token *node)
{
	t_token *temp;

	temp = node;
	temp = temp->prev;
	if(node == NULL)
	{
		printf("NULL -> ");
		return ;
	}
	while (node != NULL)
	{
		printf("%s -> ", node->tokens);
		node = node->next;
	}
	printf("NULL \n\n");
	printf("NULL -> ");
	while (temp != NULL)
	{
		printf("%d -> ", temp->type);
		temp = temp->next;
	}
	printf("NULL \n");
}