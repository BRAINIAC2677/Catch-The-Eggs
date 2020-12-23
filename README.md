# Catch-The-Eggs


## Compiling Command:
g++ -IOpenGL\include -w -c iMain.cpp -o iMain.o -g

## Linking:
g++ -Llib iMain.o -o iMain.exe -lGlaux -lGLU32 -lglui32 -lglut32 -lOPENGL32 -lgdi32 -lwinmm
