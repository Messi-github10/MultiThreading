SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SRCS))
CC:=g++
FLAGS:=-g
EXE:=test.exe

$(EXE):$(OBJS)
	$(CC)  $^ -o $@ $(FLAGS)

%.o:%.cc 
	$(CC) -c  $^ -o $@ $(FLAGS)

clean:
	rm -rf $(OBJS)  $(EXE)

echo:
	@echo $(SRCS)
	@echo $(OBJS)