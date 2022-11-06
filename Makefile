#Makefile
CXX 	 = clang++
CXXFLAGS = -fsanitize=address -no-pie
LIB_DIRS = -L/usr/local/lib 
LIBS 	 = -lcurl -lstdc++fs -lradamsa
SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
INC		 = -I./
TARGET   = curl_fuzz

all: $(TARGET)
	$(CXX) -o $(TARGET) $(OBJS) $(INC) $(LIB_DIRS) $(LIBS) $(CXXFLAGS)

$(TARGET):
	$(CXX) -c $(SRCS) $(INC) $(LIB_DIRS) $(LIBS) $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o
