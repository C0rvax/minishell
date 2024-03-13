/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/13 10:48:15 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env with no options or arguments
// env only prints all environment variables

#include "env_parsing.h"

void free_exit(t_cmd *cmd, char **mini_env)
{
	t_cmd	*buff;

	if (!cmd)
		return ;
	while (cmd->next)
	{
		buff = cmd->next;
		if (cmd->argv)
			free_tab(cmd->argv);
		if (cmd->in)
			ft_in_lstclear(cmd->in)
		if (cmd->out)			
			ft_in_lstclear(cmd->out)
		if (cmd->path_cmd)
			free(cmd->path_cmd)
		free(cmd);
		cmd = buff;
	}
	free_tab(mini_env);
}

void	ft_exit(t_cmd *cmd, char **mini_env)
{
	free_exit(cmd, mini_env);
	ft_printf("exit\n");
	exit(0);
}

void	ft_env(t_env *node)
{
	while (node != NULL)
	{
		printf("%s\n", node->var); // remplacer par ft_printf
		node = node->next;
	}
}

// void	ft_unset(t_env *node, char *arg) // revoir si l'argument de unset sera envoye comme string 
// + voir si on doit gerer la definition de variables
// {
// 	// if (arg) n'existe pas dans env ou ailleurs si ailleurs doit etre couvert
// }
