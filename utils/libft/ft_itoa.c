/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:56:01 by caqueiro          #+#    #+#             */
/*   Updated: 2023/11/01 15:16:56 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_size(int n, int base)
{
	int	size;

	size = 0;
	while (n)
	{
		n = n / base;
		size++;
	}
	return (size);
}

static	void	fill_itoa(char *itoa, long n, int base, int negative)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (n)
	{
		r = n % base;
		if (r > 9)
			itoa[i++] = (r - 10) + 'a';
		else
			itoa[i++] = r + '0';
		n = n / base;
	}
	if (negative)
		itoa[i++] = '-';
	reverse(itoa, i);
}

char	*ft_itoa_base(long n, int base)
{
	char	*itoa;
	int		negative;
	long	nbr;

	nbr = (long)n;
	if (nbr == 0)
		return (ft_strdup("0"));
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		nbr = n * -1;
	}
	itoa = (char *)ft_calloc((itoa_size(n, base) + negative + 1),
			sizeof (char));
	if (!itoa)
		return (NULL);
	fill_itoa(itoa, nbr, base, negative);
	return (itoa);
}

char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, 10));
}

/*int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
}*/
