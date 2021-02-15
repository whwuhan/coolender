include makefile_conf.mk
#所有.o文件
OBJ_SRC := obj/main.o obj/camera.o obj/mesh.o obj/model.o

Coolender : $(OBJ_SRC)
	$(CC) $(FLAGS) \
	-I$(INCLUDE_DIR) \
	$(3RD_SRC_INCLUDE) \
	-L$(LIB_DIR) -lassimp -lglfw3 -lglad \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	$(OBJ_SRC) \
	3rdsrc/imgui/imgui_draw.cpp 3rdsrc/imgui/imgui_tables.cpp \
	3rdsrc/imgui/imgui_widgets.cpp 3rdsrc/imgui/imgui.cpp \
	3rdsrc/imgui/imgui_demo.cpp \
	3rdsrc/imgui/backends/imgui_impl_glfw.cpp 3rdsrc/imgui/backends/imgui_impl_opengl3.cpp \
	-o Coolender

# 注意：如果指定了.o文件的存放目录，target也要指定路径，否则每次编译都会重新编译.o文件
#目标文件
obj/main.o : main.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c main.cpp -o $@

obj/camera.o : include/camera.h src/camera.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/camera.cpp -o $@

obj/mesh.o : include/mesh.h src/mesh.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/mesh.cpp -o $@

obj/model.o : include/model.h src/model.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/model.cpp -o $@

.PHONY : clean
clean : 
	-rm -rf Coolender