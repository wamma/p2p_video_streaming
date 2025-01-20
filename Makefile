# 컴파일러 및 플래그 설정
CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I/opt/homebrew/include/opencv4
LDFLAGS = -L/opt/homebrew/lib -lavcodec -lavformat -lavutil -lboost_system `pkg-config --cflags --libs opencv4`

# 빌드 대상 및 디렉토리 설정
TARGET = p2p-streaming
SRC_DIR = src
OBJ_DIR = obj

# 소스 및 객체 파일
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린업 규칙
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)
