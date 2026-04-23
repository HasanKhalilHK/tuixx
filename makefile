# default values
CXX = g++
CFLAGS = -std=c++17

SRCS_COMMON = src/shared/main.cpp src/shared/widget_shared.cpp src/shared/container_shared.cpp src/shared/terminal_shared.cpp
OBJS_COMMON = $(patsubst %.cpp, build/objects/shared/%.o, $(notdir $(SRCS_COMMON)))

#windows flags
CXX_WINDOWS = g++

SRCS_WINDOWS = src/windows/terminal_windows.cpp src/windows/widget_windows.cpp \
               src/windows/container_windows.cpp src/windows/style_windows.cpp

OBJS_WINDOWS = $(patsubst %.cpp, build/objects/windows/%.o, $(notdir $(SRCS_WINDOWS)))

CXXFLAGS_WINDOWS = -std=c++17 \
  -IC:/mingw64/include \

WINDOWS_DLL_FLAGS = -shared \
  -DBUILDING_DLL

TARGET_WINDOWS = build/main.exe

DLL_WINDOWS = build/tuixx.dll


#linux flags
CXX_LINUX = g++

SRCS_LINUX = src/linux/terminal_linux.cpp src/linux/widget_linux.cpp \
             src/linux/container_linux.cpp src/linux/style_linux.cpp

OBJS_LINUX = $(patsubst %.cpp, build/objects/linux/%.o, $(notdir $(SRCS_LINUX)))

CXXFLAGS_LINUX = -std=c++17 -Wall -fPIC
SOFLAGS_LINUX = -shared 
SO_LINUX = build/tuixx.so

TARGET_LINUX = build/main


.PHONY: all windows linux clean

windows: $(TARGET_WINDOWS) $(DLL_WINDOWS)
windows: CXX = $(CXX_WINDOWS)
windows: CFLAGS = $(CXXFLAGS_WINDOWS) $(WINDOWS_DLL_FLAGS)

linux: $(TARGET_LINUX) $(SO_LINUX)
linux: CXX = $(CXX_LINUX)
linux: CFLAGS = $(CXXFLAGS_LINUX)


# windows
$(TARGET_WINDOWS): $(OBJS_WINDOWS) $(OBJS_COMMON) 
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS) $(OBJS_WINDOWS) $(OBJS_COMMON) -o $(TARGET_WINDOWS)

$(DLL_WINDOWS): $(OBJS_WINDOWS) $(OBJS_COMMON) 
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS) $(WINDOWS_DLL_FLAGS) $(OBJS_WINDOWS) $(OBJS_COMMON) -o $(DLL_WINDOWS)

# linux
$(TARGET_LINUX): $(OBJS_LINUX) $(OBJS_COMMON)
	$(CXX_LINUX) $(CXXFLAGS_LINUX) $(OBJS_LINUX) $(OBJS_COMMON) -o $(TARGET_LINUX)

$(SO_LINUX): $(OBJS_LINUX) $(OBJS_COMMON)
	$(CXX_LINUX) $(CXXFLAGS_LINUX) $(SOFLAGS_LINUX) $(OBJS_LINUX) $(OBJS_COMMON) -o $(SO_LINUX)

#shared
build/objects/windows/%.o: src/windows/%.cpp
	@mkdir -p build/objects/windows
	$(CXX) $(CFLAGS) -c $< -o $@

build/objects/linux/%.o: src/linux/%.cpp
	@mkdir -p build/objects/linux
	$(CXX) $(CFLAGS) -c $< -o $@

build/objects/shared/%.o: src/shared/%.cpp
	@mkdir -p build/objects/shared
	$(CXX) $(CFLAGS) -c $< -o $@

  

clean:
	rm -rf build
