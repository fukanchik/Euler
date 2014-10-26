#
#
#
all:
	cd lib && make && cd ..
	@$(foreach f, $(basename $(wildcard [0-9][0-9][0-9])), echo "Entering $f"; cd $f; make; cd ..;)

clean:
	cd lib && make clean && cd ..
	@$(foreach f, $(basename $(wildcard [0-9][0-9][0-9])), echo "Entering $f"; cd $f; make clean; cd ..;)

test: all
	echo "Test"
	@$(foreach f, $(basename $(wildcard [0-9][0-9][0-9])), echo "Entering $f"; cd $f; ./euler$f; cd ..;)

