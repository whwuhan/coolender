include makefile_conf.mk

Coolender :
	$(CC) $(FLAGS) \
	-I$(INCLUDE_DIR) \
	-I$(3RD_SRC) \
	-L$(LIB_DIR) -lglad -lglfw3 -lassimp -lcamera \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	main.cpp -o Coolender \
	
.PHONY : clean
clean : 
	-rm -rf Coolender