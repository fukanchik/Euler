# This one expects several variables to be set:
# APP - binary file to be built
# OBJS - list of obj files to be used

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDOPT) -o $(APP) $(OBJS) $(LIBS)
	#$(STRIP) $(APP)

clean:
	rm -rf $(APP) $(OBJS)

uno: all
	uno -I../lib -w $(subst .o,.c,$(OBJS))

valgrind: all
	valgrind -q --leak-resolution=high --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(APP)

