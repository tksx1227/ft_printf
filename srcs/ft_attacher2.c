/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_attacher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:39:51 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/10 03:20:53 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_status	ft_attach_num(t_printf *info)
{
	char		prefix[2];
	t_status	status;

	status = SUCCESS;
	if ((info->is_zero && info->prec == 0) || info->length < info->prec)
		status = ft_attach_prec_common(info);
	if (status == SUCCESS)
	{
		if (info->sign != 0 && !info->is_unsigned)
		{
			prefix[0] = info->sign;
			prefix[1] = '\0';
			if (info->length < info->width - 1)
				status = ft_attach_width_with_prefix_common(info, prefix);
			else
				status = ft_attch_prefix_common(info, prefix);
		}
		else
		{
			if (info->length < info->width)
				status = ft_attach_width_common(info);
		}
	}
	return (status);
}

t_status	ft_attach_ptr(t_printf *info)
{
	t_status	status;

	status = SUCCESS;
	if ((info->is_zero && info->prec == 0) || info->length < info->prec)
		status = ft_attach_prec_common(info);
	if (status == SUCCESS)
	{
		if (info->length < info->width - 2)
			status = ft_attach_width_with_prefix_common(info, "0x");
		else
			status = ft_attch_prefix_common(info, "0x");
	}
	return (status);
}

t_status	ft_attach_hex(t_printf *info)
{
	t_status	status;

	status = SUCCESS;
	if (info->length < info->prec)
		status = ft_attach_prec_common(info);
	if (status == SUCCESS)
	{
		if (info->sharp_flag && !info->is_zero)
		{
			if (info->length < info->width - 2)
				status = ft_attach_width_with_prefix_common(info, "0x");
			else
				status = ft_attch_prefix_common(info, "0x");
		}
		else
		{
			if (info->length < info->width)
				status = ft_attach_width_common(info);
		}
	}
	if (status == SUCCESS && info->spec == 'X')
		ft_toupper_str(info->content);
	return (status);
}