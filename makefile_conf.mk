# makefile 配置文件

# 编译器配置
CC := g++
FLAGS := -std=c++11

# 目录配置
INCLUDE_DIR := include
SRC_DIR := src
LIBS_DIR := libs
OBJ_DIR := obj
3RD_SRC_DIR := 3rdsrc



# 第三方库头文件
ASSIMP_INCLUDE := $(3RD_SRC_DIR)/assimp/include
GLFW_INCLUDE := $(3RD_SRC_DIR)/glfw/include
GLAD_INCLUDE := $(3RD_SRC_DIR)/glad/include
GLM_INCLUDE := $(3RD_SRC_DIR)/glm
IMGUI_INCLUDE := $(3RD_SRC_DIR)/imgui
#GL3W_INCLUDE := $(3RD_SRC_DIR)/imgui/examples/libs/gl3w
STB_INCLUDE := $(3RD_SRC_DIR)/stb
WHLIB_INCLUDE := $(3RD_SRC_DIR)/whlib/include


#包含所有第三方头文件
3RD_SRC_INCLUDE := -I$(ASSIMP_INCLUDE) \
-I$(GLFW_INCLUDE) \
-I$(GLAD_INCLUDE) \
-I$(GLM_INCLUDE) \
-I$(IMGUI_INCLUDE) \
-I$(STB_INCLUDE) \
-I$(WHLIB_INCLUDE)