# This one expects several variables to be set:
# APP - binary file to be built
# OBJS - list of obj files to be used

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDOPT) -o $(APP) $(OBJS) $(LIBS)
	$(STRIP) $(APP)

clean:
	rm -rf $(APP) $(OBJS)

uno: all
	uno -I../lib -w $(subst .o,.c,$(OBJS))
