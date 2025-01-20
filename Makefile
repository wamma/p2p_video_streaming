# 컴파일러 및 플래그 설정
CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I/opt/homebrew/include/opencv4
LDFLAGS = -L/opt/homebrew/lib -lavcodec -lavformat -lavutil -lboost_system `pkg-config --cflags --libs opencv4`

# 빌드 대상 및 디렉토리 설정
TARGET = p2p-streaming
SRCDIR = src
OBJDIR = obj

# 소스 및 객체 파일
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린업 규칙
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)

# 헬프 메시지
help:
	@echo "사용 가능한 명령어:"
	@echo "  make          - 빌드 실행"
	@echo "  make clean    - 객체 파일 제거"
	@echo "  make fclean   - 객체 파일 및 실행 파일 제거"
	@echo "  make re       - 빌드 초기화 후 다시 빌드"
