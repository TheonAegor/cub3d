/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:08:34 by taegor            #+#    #+#             */
/*   Updated: 2021/01/23 10:32:02 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

typedef struct		s_modific
{
	char	type;
	int		precision;
	int		width;
	int		flag;
	int		varg;
	int		result;
	char	*variable;
}					t_modif;

int					ft_parser(char *format, va_list args,
								int *i, t_modif *flag);
int					ft_print_prec_less_neg(t_modif *flag);
int					ft_printf(const char *format, ...);
int					ft_processor(t_modif *flag, va_list args);
int					ft_find_tens(unsigned long x);
int					ft_proc_hex(unsigned int x, t_modif *flag);
int					ft_find_sixteens(unsigned long x);
int					ft_proc_p(unsigned long x, t_modif *flag);
int					ft_proc_s(char *str, t_modif *flag);
int					ft_proc_c(int c, t_modif *flag);
int					ft_proc_u(unsigned int x, t_modif *flag);
int					ft_proc_d(int x, t_modif *flag);
int					ft_proc_percent(t_modif *flag);
int					ft_printspace(t_modif *flag);
int					ft_printzero(t_modif *flag);
int					print_precision(t_modif *flag);
int					ft_calc_flags(t_modif *flag);
int					print_flags(t_modif *flag);
int					ft_check_minus(t_modif *flag);
char				*ft_itoa_unsigned(unsigned long int x);
char				*ft_itoa_base(unsigned long long int x);

#endif
