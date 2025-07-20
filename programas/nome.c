#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

// Padrão 32x32 com um G e um B simples em ASCII pixelado
GLubyte gbPattern[128] = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00011111, 0b00000000, 0b00000000, 0b00000000,  // G
  0b00100000, 0b00000000, 0b00000000, 0b00000000,
  0b00100000, 0b00000000, 0b00000000, 0b00000000,
  0b00100011, 0b10000000, 0b00000000, 0b00000000,
  0b00100001, 0b00000000, 0b00000000, 0b00000000,
  0b00100001, 0b00000000, 0b00000000, 0b00000000,
  0b00011110, 0b00000000, 0b00000000, 0b00000000,
  
  0b00111100, 0b00000000, 0b00000000, 0b00000000,  // B
  0b00100010, 0b00000000, 0b00000000, 0b00000000,
  0b00111100, 0b00000000, 0b00000000, 0b00000000,
  0b00100010, 0b00000000, 0b00000000, 0b00000000,
  0b00100010, 0b00000000, 0b00000000, 0b00000000,
  0b00111100, 0b00000000, 0b00000000, 0b00000000,

  // Resto do padrão é preenchido com zeros
};

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); // fundo branco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void desenhaHexagono() {
    float cx = 150.0; // centro x
    float cy = 150.0; // centro y
    float raio = 100.0; // raio do círculo que envolve o hexágono

    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(gbPattern);

    glColor3f(0.0, 0.0, 1.0); // azul
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        float ang = 2 * PI * i / 6;
        float x = cx + raio * cos(ang);
        float y = cy + raio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();

    glDisable(GL_POLYGON_STIPPLE);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaHexagono();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hexágono com padrão GB");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
