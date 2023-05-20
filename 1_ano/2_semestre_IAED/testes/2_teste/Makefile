# -*- MakeFile -*-

NAME = Teste_2

CC = @cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c

OBJ = $(SRC:.c=.o)

Color_Off='\033[0m'

IGreen='\033[0;92m'
IYellow='\033[0;93m'
ICyan='\033[0;96m'
IRed='\033[0;91m'

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}
HOWTO = @echo ${IRed}"To run the program do: ./${NAME} <csv-file>"${Color_Off}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	$(MSG1)
	${HOWTO}

covid: $(NAME)
	@./${NAME} ./covid.csv

clean:
	@/bin/rm -f $(OBJ)
	$(MSG2)

fclean: clean
	@/bin/rm -f $(NAME)
	$(MSG3)

re: fclean all