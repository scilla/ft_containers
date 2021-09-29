SRCS =	tester/main.cpp \
		tester/tester.cpp \
		tester/utils.cpp \
		tester/tester_vector.cpp \
		tester/tester_stack.cpp \
		tester/tester_map.cpp

SRCS_SET = \
		tester/tester_set.cpp \
		tester/tester.cpp \
		tester/utils.cpp

INCLUDE = -I. -I.. -Itester

OBJS = $(SRCS:.cpp=.o)

OBJS_SET_S = $(SRCS_SET:.cpp=.os)

OBJS_SET = $(SRCS_SET:.cpp=.o)

CPP = clang++

FLAGS = -g -Wall -Wextra -Werror -std=c++98 -ferror-limit=10 -fstandalone-debug

NAME = ft_containers_tests

TEST_SET_S = set_test_string

TEST_SET = set_test

%.o : %.cpp
	$(CPP) $(FLAGS) -c $< -o $(<:.cpp=.o) $(INCLUDE)

%.os : %.cpp
	$(CPP) -DSTRING_SET $(FLAGS) -c $< -o $(<:.cpp=.os)

all: $(NAME) $(TEST_SET) $(TEST_SET_S)

set: $(TEST_SET) $(TEST_SET_S)

$(NAME): $(OBJS)
	$(CPP) $(OBJS) -o $(NAME)

$(TEST_SET_S) : $(OBJS_SET_S)
	$(CPP) -DSTRING_SET $(FLAGS) $(OBJS_SET_S) -o $(TEST_SET_S)

$(TEST_SET) : $(OBJS_SET)
	$(CPP) $(OBJS_SET) -o $(TEST_SET)

clean:
	rm -rf $(OBJS) $(OBJS_SET) $(OBJS_SET_S)
	rm -rf tester/maps_output tester/vectors_output tester/stacks_output valgrind-out.txt

fclean: clean
	rm -rf $(NAME) $(TEST_SET) $(TEST_SET_S)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: fclean clean all re run
