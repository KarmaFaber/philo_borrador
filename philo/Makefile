#◉────▣───▢◇▢───▣────◉•◉───▣───▢   Colors:   ▢───▣───◉•◉───▣────▢◇▢───▣───◉#

BLACK   := \033[0;30m
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m

CURRENT_COLOR := \033[0;34m
RESET   := \033[0m


#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

NAME        := philo
CC          := cc
CFLAGS      := -Wall -Werror -Wextra 
RM          := rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Formatting:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

# Run 'make re MODE=pretty' for color formatting.
# Run 'make re MODE=debug' for debug formatting.

MODE	= none

ifeq ($(MODE), pretty)
	CFLAGS	+= -D DEBUG_FORMATTING=1
endif

ifeq ($(MODE), debug)
	CFLAGS	+= -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

#◉───▣───▢◇▢───▣───◉•◉───▣───▢    philo srcs:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

PHILO_SRCS  := main.c parce.c utils.c exit.c
PHILO_OBJS  := $(PHILO_SRCS:.c=.o)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(NAME)

$(NAME): $(PHILO_OBJS) 
	@$(CC) $(CFLAGS) $(PHILO_OBJS) -o $(NAME)
	@echo "$(CURRENT_COLOR) ✅ $(NAME) created.\n$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -lpthread -c $< -o $@

clean:
	$(RM) $(PHILO_OBJS)
	@echo "$(CURRENT_COLOR)🧹 Object files cleaned.\n$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(CURRENT_COLOR) 🧹 $(NAME) binary cleaned.\n$(RESET)"

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Valgrind   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

VALGRIND := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --log-file=test/valgrind_outputs/valgrind_output_$(shell date +%Y%m%d_%H%M%S).log -s

valgrind: all

	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──Running Valgrind..──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──$(RESET)"
#	@-$(VALGRIND) ./$(NAME) <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
#	@-$(VALGRIND) ./$(NAME) 
	@-$(VALGRIND) ./$(NAME) 4 800 200 200 5
	@test/hs_files/./open_valgrind_log.sh
	@echo "$(CURRENT_COLOR)➵⤐╌╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣── Valgrind completed. Check valgrind_output.log for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(RESET)"
	
clean_valgrind:
	test/hs_files/./clean_valgrind.sh

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Test    ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

test: all
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Starting test: ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(RESET)"
	@test/hs_files/./test_philo.sh
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── End of test. ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(RESET)"

clean_test:
	test/hs_files/./clean_test.sh

clean_all: clean_test fclean clean_valgrind
	
#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Norminette ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

norm:
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Checking Norminette: ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(RESET)"
	@norminette $(PHILO_SRCS) philo.h
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Norminette completed. Check your output for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(RESET)"

#◉───▣───▢◇▢───▣───◉•◉───▣───▢  Format ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

format: 
	c_formatter_42 $(PHILO_SRCS) philo.h

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re format norm valgrind test clean_valgrind clean_test clean_all