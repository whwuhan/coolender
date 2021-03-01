include makefile_conf.mk
#所有.o文件
OBJS := \
objs/cld_main.o \
objs/cld_camera.o \
objs/cld_coolender_ui.o \
objs/cld_coolender.o \
objs/cld_light.o \
objs/cld_mesh.o \
objs/cld_model.o \
objs/cld_plane.o \
objs/cld_render.o \
objs/cld_scene.o \
objs/cld_shader.o \
objs/cld_sphere.o \
objs/cld_texture_loader.o \
objs/cld_window.o \
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
objs/cld_main.o : cld_main.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c cld_main.cpp -o $@

objs/cld_camera.o : include/cld_camera.h src/cld_camera.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_camera.cpp -o $@

objs/cld_coolender_ui.o : include/cld_coolender_ui.h src/cld_coolender_ui.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_coolender_ui.cpp -o $@

objs/cld_coolender.o : include/cld_coolender.h src/cld_coolender.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_coolender.cpp -o $@

objs/cld_light.o : include/cld_light.h src/cld_light.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_light.cpp -o $@

objs/cld_mesh.o : include/cld_mesh.h src/cld_mesh.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_mesh.cpp -o $@

objs/cld_model.o : include/cld_model.h src/cld_model.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_model.cpp -o $@

objs/cld_plane.o : include/cld_plane.h src/cld_plane.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_plane.cpp -o $@

objs/cld_render.o : include/cld_render.h src/cld_render.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_render.cpp -o $@

objs/cld_scene.o : include/cld_scene.h src/cld_scene.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_scene.cpp -o $@

objs/cld_shader.o : include/cld_shader.h src/cld_shader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_shader.cpp -o $@

objs/cld_sphere.o : include/cld_sphere.h src/cld_sphere.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_sphere.cpp -o $@

objs/cld_texture_loader.o : include/cld_texture_loader.h src/cld_texture_loader.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_texture_loader.cpp -o $@

objs/cld_window.o : include/cld_window.h src/cld_window.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/cld_window.cpp -o $@

objs/stb_image.o : src/stb_image.cpp
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) $(3RD_SRC_INCLUDE) -c $(SRC_DIR)/stb_image.cpp -o $@


.PHONY : clean
clean : 
	-rm -rf Coolender $(OBJS)