include makefile_conf.mk
#所有.o文件
OBJS := obj/main.o obj/camera.o obj/mesh.o obj/model.o \
obj/plane.o obj/shader.o obj/stb_image.o obj/texture_loader.o obj/window.o

Coolender : $(OBJS)
	$(CC) $(FLAGS) \
	-I$(INCLUDE_DIR) \
	$(3RD_SRC_INCLUDE) \
	-L$(LIBS_DIR) -lassimp -lzlibstatic -lglfw3 -lglad -limgui \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	$(OBJS) \
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

obj/plane.o : include/plane.h src/plane.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/plane.cpp -o $@

obj/shader.o : include/shader.h src/shader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/shader.cpp -o $@

obj/stb_image.o : src/stb_image.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/stb_image.cpp -o $@

obj/texture_loader.o : include/texture_loader.h src/texture_loader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/texture_loader.cpp -o $@

obj/window.o : include/window.h src/window.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/window.cpp -o $@

.PHONY : clean
clean : 
	-rm -rf Coolender $(OBJS)