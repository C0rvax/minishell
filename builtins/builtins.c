/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:49 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/19 17:32:48 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	exec_pwd(t_exec *exec, t_child *child)
{
	char	*pwd;

	// est ce qu'on verifie qu'il n'y ai pas d'autres argv[+1] ??
	pwd = getcwd(NULL, 0);
	if (!pwd)
		clear_built(exec, child, msg_built(PWD, 1));
	ft_printf("%s\n", pwd);
		clear_built(exec, child, 0);
}

char	*ft_getenv(char **env, char *str)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(str);
		if (ft_strnstr(env[i], str, len))
		{
			value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - (len + 1));
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	value = malloc(1);
	if (!value)
		return (NULL);
	value[0] = '\0';
	return (value);
}

void	exec_cd(t_exec *exec, t_child *child)
{
	int		fd;
	int		malloc;
	char	*built;

	malloc = 0;
	built = child->current_cmd->argv[1];	
	if (!built)
	{
		built = ft_getenv(exec->mini_env, "HOME");
		malloc = 1;
	}
	if (!built)
		clear_built(exec, child, msg_built(BMALLOC, 1));
	fd = open(built, O_DIRECTORY);
	if (fd == -1)
	{
		if (malloc)
			free(built);
		clear_built(exec, child, msg_built(CD, 1));
	}
	close(fd);
	chdir(built);
	if (malloc)
		free(built);
	clear_built(exec, child, 0);
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

void	exec_echo(t_exec *exec, t_child *child)
{
	int	i;
	char	**buf;

	buf = child->current_cmd->argv;
	i = 1;
	if (!buf[1])
		ft_printf("\n");
	else if (buf[1] && !check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
	}
	else if (buf[1] && check_flag_echo(buf[1]))
	{
		i = 0;
		while (buf[++i])
			ft_printf("%s", buf[i]);
		ft_printf("\n");
	}
	clear_built(exec, child, 0);
}

int	ft_lenarr(char **arr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		if (arr[i] && ft_strchr(arr[i], '=') != NULL)
			res++;
		i++;
	}
	return (res);
}

char	**ft_joinarr(char **exp, char **env)
{
	int		i;
	int		j;
	char	**new;

	i = ft_lenarr(exp);
	j = ft_lenarr(env);
	if (!i)
		return (NULL);
	new = malloc(sizeof(char *) * (i + j + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env && env[++i])
		new[i] = env[i];
	j = 0;
	while (exp[j])
	{
		if (ft_strchr(exp[j], '=') != NULL)
			new[i + j] = exp[j];
		j++;
	}
	new[i + j] = NULL;
	return (new);
}

void	exec_export(t_exec *exec, t_child *child)
{
	char	**new;
	char	**cpy;

	if (exec->total_cmd != 1)
		clear_built(exec, child, 0);
	cpy = exec->mini_env;
	new = ft_joinarr(child->current_cmd->argv, cpy);
	if (!new)
		clear_built(exec, child, 0);
	exec->mini_env = new;
	ft_freetab(cpy);
}

void	exec_env(t_exec *exec, t_child *child)
{
	int	i;

	i = 0;
	if (!child->current_cmd->argv[1])
	{
		while (exec->mini_env[i])
		{
			ft_printf("%s\n", exec->mini_env[i]);
			i++;
		}
		clear_built(exec, child, 0);
	}
	// on peut ignorer ou erreur si argv[1]
	else
		clear_built(exec, child, msg_built(ENV, 1));
}

void	exec_exit(t_exec *exec, t_child *child)
{
	ft_printf("exit\n");
	clear_built(exec, child, 0);
}

// void	ft_unset(t_env *node, char *arg) // revoir si l'argument de unset sera envoye comme string 
// + voir si on doit gerer la definition de variables
// {
// 	// if (arg) n'existe pas dans env ou ailleurs si ailleurs doit etre couvert
// }
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
		if (!strncmp(builtarr[i], cmd->argv[0], ft_strlen(cmd->argv[0])))
			return (ft_freetab(builtarr), i);
		i++;
	}
	return (ft_freetab(builtarr), -1);
}
void	exec_unset(t_exec *exec, t_child *child)
{
	(void)exec;
	(void)child;
}

int	exec_builtin(t_exec *exec, t_child *child)
{
	int	i;

	ft_printf("dans le builtin\n");
	i = is_a_builtin(child->current_cmd);
	if (i == 0)
		exec_echo(exec, child);
	else if (i == 1)
		exec_cd(exec, child);
	else if (i == 2)
		exec_pwd(exec, child);
	else if (i == 3)
		exec_export(exec, child);
	else if (i == 4)
		exec_unset(exec, child);
	else if (i == 5)
		exec_env(exec, child);
	else if (i == 6)
		exec_exit(exec, child);
	return (0);
}

