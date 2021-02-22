include makefile_conf.mk
#所有.o文件
OBJS := \
objs/main.o \
objs/camera.o \
objs/coolender_ui.o \
objs/coolender.o \
objs/light.o \
objs/mesh.o \
objs/model.o \
objs/plane.o \
objs/render.o \
objs/scene_wh.o \
objs/shader.o \
objs/stb_image.o \
objs/texture_loader.o \
objs/window.o

Coolender : $(OBJS)
	$(CC) $(FLAGS) \
	-I$(INCLUDE_DIR) \
	$(3RD_SRC_INCLUDE) \
	-L$(LIBS_DIR) -lassimp -lzlibstatic -lglfw3 -lglad -limgui -limguifiledialog -lwhlib \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	$(OBJS) \
	-o Coolender
	./Coolender

# 注意：如果指定了.o文件的存放目录，target也要指定路径，否则每次编译都会重新编译.o文件
#目标文件
objs/main.o : main.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c main.cpp -o $@

objs/camera.o : include/camera.h src/camera.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/camera.cpp -o $@

objs/coolender_ui.o : include/coolender_ui.h src/coolender_ui.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/coolender_ui.cpp -o $@

objs/coolender.o : include/coolender.h src/coolender.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/coolender.cpp -o $@

objs/light.o : include/light.h src/light.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/light.cpp -o $@

objs/mesh.o : include/mesh.h src/mesh.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/mesh.cpp -o $@

objs/model.o : include/model.h src/model.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/model.cpp -o $@

objs/plane.o : include/plane.h src/plane.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/plane.cpp -o $@

objs/render.o : include/render.h src/render.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/render.cpp -o $@

objs/scene_wh.o : include/scene_wh.h src/scene_wh.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/scene_wh.cpp -o $@

objs/shader.o : include/shader.h src/shader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/shader.cpp -o $@

objs/stb_image.o : src/stb_image.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/stb_image.cpp -o $@

objs/texture_loader.o : include/texture_loader.h src/texture_loader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/texture_loader.cpp -o $@

objs/window.o : include/window.h src/window.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/window.cpp -o $@

.PHONY : clean
clean : 
	-rm -rf Coolender $(OBJS)