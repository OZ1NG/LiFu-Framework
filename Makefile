#Makefile
CXX 	 = clang++
CXXFLAGS = -fsanitize=address -no-pie
LIB_DIRS = -L/usr/local/lib 
LIBS 	 = -lcurl -lstdc++fs -lradamsa
SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
BIN_DIR  = ./bin
TARGET   = curl_fuzz

all: $(TARGET)
	mkdir $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$(TARGET) $(OBJS) $(LIB_DIRS) $(LIBS) $(CXXFLAGS)

$(TARGET):
	$(CXX) -c $(SRCS) $(LIB_DIRS) $(LIBS) $(CXXFLAGS) 

clean:
	rm -rf $(OBJS) $(BIN_DIR)
