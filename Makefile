target=Calculator
all: $(target)
	
$(target): Main.c Stack.c
	gcc $^ -o $@
