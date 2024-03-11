/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:11:31 by ctruchot          #+#    #+#             */
/*   Updated: 2024/03/11 18:08:18 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	ft_cmd_lstsize(t_cmd *lst);
int error_check(t_cmd *cmd);
int	ft_inout_lstsize(t_redirect *lst);
int	check_in(t_redirect *in);
int	check_infile(char *path);
int	check_out(t_redirect *out);
int	check_outfile(char *path);


