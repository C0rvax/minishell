/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:17:24 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/22 14:35:30 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PARSING_H
# define ENV_PARSING_H

# include "minishell.h"

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}		t_env;

t_env	*parse_env_list(char **env);
char	**env_list_to_array(t_env *env);
void	parse_env_array(t_persistent *pers, char **env);

#endif
