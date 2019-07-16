CC=g++-7
compile_flags := -c -std=c++17 -Wall
LDFLAGS := -lstdc++fs -pthread
CXXFLAGS += -MMD

TARGET := Signature

SRCS := $(wildcard *.cpp)
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
