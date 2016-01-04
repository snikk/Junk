CC = g++
SRC_ASSEMBLER = main.cpp \
			    ../../common/data_structures.c \
			    ../../common/commands.c \
			    ../../common/util.c
SRC_INTERPRETER = interpreter.cpp \
			   	  ../../common/data_structures.c \
			      ../../common/commands.c \
				  ../../common/util.c
DEBUG = -g
LIBS = -I../../common/

assembler: $(SRC_ASSEMBLER)
	$(CC) $(SRC_ASSEMBLER) $(LIBS) -o assembler $(DEBUG)

