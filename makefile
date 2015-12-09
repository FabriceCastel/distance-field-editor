default:
	g++ -framework OpenGL `pkg-config --cflags glfw3` main.cpp -o field-editor `pkg-config --static --libs glfw3`
