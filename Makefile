target=Calculator
all: $(target)
	
$(target): Main.c
	gcc $^ -o $@
