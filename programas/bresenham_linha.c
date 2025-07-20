#include <GL/glut.h>
#include <stdlib.h>
#include <math.h> 

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void drawPixel(int x, int y);
void bresenhamLine(int x1, int y1, int x2, int y2);

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Algoritmo de Bresenham");
  init();
  glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 256, 0, 256, -1 ,1);
}

void drawPixel(int x, int y){
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        drawPixel(x1, y1); // Desenha o pixel atual

        if (x1 == x2 && y1 == y2) break; // Chegou ao ponto final

        int e2 = 2 * err;
        if (e2 > -dy) { // Se o erro for maior que -dy, move em X
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) { // Se o erro for menor que dx, move em Y
            err += dx;
            y1 += sy;
        }
    }
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 1.0, 0.0);
  bresenhamLine(40, 200, 200, 10);
  
  glFlush(); 
}

void keyboard(unsigned char key, int x, int inty){
  switch (key) {
  case 27: // Tecla ESC para sair
    exit(0);
    break;
  }
}