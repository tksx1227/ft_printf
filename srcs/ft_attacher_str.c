/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attacher_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:47:24 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/10 00:26:23 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_status	ft_attach_str_prec(t_printf *info);
static t_status	ft_attach_str_width(t_printf *info);

t_status	ft_attach_str(t_printf *info)
{
	t_status	status;

	status = SUCCESS;
	if (0 <= info->prec && info->prec < info->length)
		status = ft_attach_str_prec(info);
	if (status == SUCCESS && info->length < info->width)
		status = ft_attach_str_width(info);
	return (status);
}

static t_status	ft_attach_str_prec(t_printf *info)
{
	char	*tmp;

	info->length = info->prec;
	tmp = info->content;
	info->content = ft_substr(info->content, 0, info->length);
	free(tmp);
	if (info->content == NULL)
		return (FAIL);
	return (SUCCESS);
}

static t_status	ft_attach_str_width(t_printf *info)
{
	size_t	offset;
	char	*content;

	content = (char *)ft_calloc((size_t)info->width + 1, sizeof(char));
	if (content == NULL)
		return (FAIL);
	if (info->zero_flag && !info->left_align)
		ft_memset(content, '0', info->width);
	else
		ft_memset(content, ' ', info->width);
	if (info->left_align)
		offset = 0;
	else
		offset = info->width - info->length;
	ft_memmove(content + offset, info->content, info->length);
	free(info->content);
	info->content = content;
	info->length = info->width;
	return (SUCCESS);
}
