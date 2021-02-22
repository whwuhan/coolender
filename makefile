include makefile_conf.mk
#所有.o文件
OBJS := \
objs/cool_main.o \
objs/cool_camera.o \
objs/cool_coolender_ui.o \
objs/cool_coolender.o \
objs/cool_light.o \
objs/cool_mesh.o \
objs/cool_model.o \
objs/cool_plane.o \
objs/cool_render.o \
objs/cool_scene.o \
objs/cool_shader.o \
objs/cool_texture_loader.o \
objs/cool_window.o \
objs/stb_image.o 


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
objs/cool_main.o : cool_main.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c cool_main.cpp -o $@

objs/cool_camera.o : include/cool_camera.h src/cool_camera.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_camera.cpp -o $@

objs/cool_coolender_ui.o : include/cool_coolender_ui.h src/cool_coolender_ui.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_coolender_ui.cpp -o $@

objs/cool_coolender.o : include/cool_coolender.h src/cool_coolender.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_coolender.cpp -o $@

objs/cool_light.o : include/cool_light.h src/cool_light.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_light.cpp -o $@

objs/cool_mesh.o : include/cool_mesh.h src/cool_mesh.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_mesh.cpp -o $@

objs/cool_model.o : include/cool_model.h src/cool_model.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_model.cpp -o $@

objs/cool_plane.o : include/cool_plane.h src/cool_plane.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_plane.cpp -o $@

objs/cool_render.o : include/cool_render.h src/cool_render.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_render.cpp -o $@

objs/cool_scene.o : include/cool_scene.h src/cool_scene.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_scene.cpp -o $@

objs/cool_shader.o : include/cool_shader.h src/cool_shader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_shader.cpp -o $@

objs/cool_texture_loader.o : include/cool_texture_loader.h src/cool_texture_loader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_texture_loader.cpp -o $@

objs/cool_window.o : include/cool_window.h src/cool_window.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cool_window.cpp -o $@

objs/stb_image.o : src/stb_image.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/stb_image.cpp -o $@


.PHONY : clean
clean : 
	-rm -rf Coolender $(OBJS)