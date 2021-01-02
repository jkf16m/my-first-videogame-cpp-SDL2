#OBJS specifies which files to compile as part of the project
OBJS = main.cpp
HEADERS = -I libs/whitecat/GameLibrary.hpp

#CC specifies which compiler we're using
CC = g++

#STD specifies std compiling version
STD= c++17

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main.o


#This is the target that compiles our executable
all : $(OBJS)
	$(CC) -std=$(STD) $(OBJS) $(HEADERS)  $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run :
	./$(OBJ_NAME)