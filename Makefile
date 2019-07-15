CC=g++-7
compile_flags := -c -std=c++17 -Wall
LDFLAGS := -lstdc++fs -pthread
CXXFLAGS += -MMD

TARGET := Signature

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(compile_flags) -c $<

-include $(OBJS:.o=.d)

clean:
	@rm -rf ./*.o ./*.d Signature

print-%  : ; @echo $* = $($*)
