/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:39:59 by kamitsui          #+#    #+#             */
/*   Updated: 2023/03/20 13:12:46 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa_binary(int n)
{
	char	*binary;
	int		i;

	binary = (char *)malloc(sizeof(char) * (32 + 1 + 7));
	if (binary == NULL)
		return (NULL);
	i = 0;
	while (i < 32 + 7)
	{
		if ((i % 4 == 0) && (i != 0))
			binary[i + (i / 4 - 1)] = ' ';
		if (n & (0x80000000) >> i)
			binary[i + (i / 4)] = '1';
		else
			binary[i + (i / 4)] = '0';
		i++;
	}
	binary[i] = '\0';
	return (binary);
}
//image
//ft_itoa_binary(0x100)
//0000 0000 0000 0000 0001 0000 0000 0000
//12bit ON

//debug code
//#include <stdio.h>
//#include <stdlib.h>
//#include "libft.h"
//
//int main(void)
//{
//	int		n = 0x00000008;
//	n = 0x80000000;//INT_MIN
//	n = 0x40000000;
//	n = 0x08000000;
//	n = 0x10000000;
//	n = 0x7FFFFFFF;//INT_MAX
//	char	*bin;
//
//	bin = ft_itoa_binary(n);
//	printf("%s:%d\n", bin, n);
//	free(bin);
//	return (0);
//}
