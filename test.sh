#!/bin/bash

case $1 in
    0)
        echo "MAIN FT test:" && make re && time > /dev/null ./containers 42 > t1 && make fclean && make stl && echo "MAIN STL TEST:" && time > /dev/null ./containers_stl 42 > t2
        echo "OUTPUT diff:" && diff t1 t2
        ;;
    1)
        make -C tester1 re && ./tester1/ft_containers_tests
        ;;
    2)
        cd tester2 && bash ./do.sh
        ;;
    *)
        echo "Usage: ./test.sh [test index 0-2]"
        ;;
esac