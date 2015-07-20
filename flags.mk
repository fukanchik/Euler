#CFLAGS=-D_POSIX_C_SOURCE=200809L -O0 -ggdb -Wall -std=c99 -pedantic -I../lib
#LDOPT=-O0 -ggdb

#CFLAGS=-D_POSIX_C_SOURCE=200809L -O0 -pg -Wall -std=c99 -pedantic -I../lib
#LDOPT=-O0 -pg

CFLAGS=-D_POSIX_C_SOURCE=200809L -O3 -Wall -fomit-frame-pointer -std=c99 -Winit-self -Wuninitialized -Wmissing-declarations -Winit-self -pedantic-errors -I../lib
CXXFLAGS=-O3 -Wall -fomit-frame-pointer -pedantic -ansi -I../lib

LIBS=-L../lib -lueuler -lm

