/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/14 17:57:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env with no options or arguments
// env only prints all environment variables

#include "env_parsing.h"

int	exec_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_printf("%s\n", pwd);
	return (0);
}

int	exec_cd(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->argv[1], O_DIRECTORY);
	if (fd == -1)
		return (1);
	close(fd);
	chdir(cmd->argv[1]);
	return (0);
}

int	check_flag_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

int	exec_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
		return (1);
	else if (cmd->argv[1] && !check_flag_echo(cmd->argv[1]))
	{
		while (cmd->argv[++i])
			ft_printf("%s", cmd->argv[i]);
	}
	else if (cmd->argv[1] && check_flag_echo(cmd->argv[1]))
	{
		i = 0;
		while (cmd->argv[++i])
			ft_printf("%s", cmd->argv[i]);
		ft_printf("\n");
	}
	return (0);
}

int	is_a_builtin(t_cmd *cmd)
{
	char	*str;
	char	**builtarr;
	int		i;

	i = 0;
	str = "echo;cd;pwd;export;unset;env;exit";
	builtarr = ft_split(str, ';');
	if (!builtarr)
		return (-2);
	while (builtarr[i])
	{
		if (builtarr[i] == cmd->argv[0])
			return (i);
		i++;
	}
	return (-1);
}

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
