/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:31:31 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:31:33 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long int	ft_pow(int n, int pw)
{
	unsigned long int	nb;

	if (n <= 0 || pw <= 0)
		return (0);
	if (pw == 1 || n == 1)
		return (n);
	nb = (unsigned long int)n;
	while (--pw)
		nb *= (unsigned long int)n;
	return (nb);
}
