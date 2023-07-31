# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 16:26:11 by kamitsui          #+#    #+#              #
#    Updated: 2023/07/31 19:46:13 by kamitsui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                    #
#       OK Map       #
#                    #

echo "42.fdf map\n"
./fdf_default test_maps/42.fdf &\
./fdf test_maps/42.fdf &\


#                    #
#       NG Map       #
#                    #

# ?? different little
#./fdf_default test_maps/10-2.fdf &\
#./fdf test_maps/10-2.fdf &\

# segumentfault
#./fdf_default test_maps/10-70.fdf &\
#./fdf test_maps/10-70.fdf &\

#./fdf_default test_maps/100-6.fdf &\
#./fdf test_maps/100-6.fdf &\
#
#./fdf_default test_maps/20-60.fdf &\
#./fdf test_maps/20-60.fdf &\
#
#./fdf_default test_maps/50-4.fdf &\
#./fdf test_maps/50-4.fdf &\
#
#./fdf_default test_maps/basictest.fdf &\
#./fdf test_maps/basictest.fdf &\
#
#./fdf_default test_maps/elem-col.fdf &\
#./fdf test_maps/elem-col.fdf &\
#
#./fdf_default test_maps/elem-fract.fdf &\
#./fdf test_maps/elem-fract.fdf &\
#
#./fdf_default test_maps/elem.fdf &\
#./fdf test_maps/elem.fdf &\
#
#./fdf_default test_maps/elem2.fdf &\
#./fdf test_maps/elem2.fdf &\
#
#./fdf_default test_maps/julia.fdf &\
#./fdf test_maps/julia.fdf &\
#
#./fdf_default test_maps/mars.fdf &\
#./fdf test_maps/mars.fdf &\
#
#./fdf_default test_maps/pentenegpos.fdf &\
#./fdf test_maps/pentenegpos.fdf &\
#
#./fdf_default test_maps/plat.fdf &\
#./fdf test_maps/plat.fdf &\
#
#./fdf_default test_maps/pnp_flat.fdf &\
#./fdf test_maps/pnp_flat.fdf &\
#
#./fdf_default test_maps/pylone.fdf &\
#./fdf test_maps/pylone.fdf &\
#
#./fdf_default test_maps/pyra.fdf &\
#./fdf test_maps/pyra.fdf &\
#
#./fdf_default test_maps/pyramide.fdf &\
#./fdf test_maps/pyramide.fdf &\
#
#./fdf_default test_maps/t1.fdf &\
#./fdf test_maps/t1.fdf &\
#
#./fdf_default test_maps/t2.fdf &
#./fdf test_maps/t2.fdf &
#
