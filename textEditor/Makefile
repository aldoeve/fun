CPPFLAGS = -std=gnu++20 -Wall -Wextra -Werror -Wshadow -Wconversion -O3
NAME_FOR_EDITOR = YATE

all: textEditor

main.cpp: editor.hpp

editor.cpp: editor.hpp

textEditor: main.cpp editor.cpp
	$(CXX) $(CPPFLAGS) -o $(NAME_FOR_EDITOR).out $^

run:
	./$(NAME_FOR_EDITOR).out

test:
	valgrind ./$(NAME_FOR_EDITOR).out

clean:
	rm -f $(NAME_FOR_EDITOR).out