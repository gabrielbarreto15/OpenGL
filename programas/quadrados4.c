// quadrados4.c
#include <GL/glut.h>
#include <stdlib.h>

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Quadrado inferior esquerdo - vermelho
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.0, 0.5);
    glEnd();

    // Quadrado inferior direito - verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.5, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 0.5);
        glVertex2f(0.5, 0.5);
    glEnd();

    // Quadrado superior esquerdo - azul
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, 1.0);
        glVertex2f(0.0, 1.0);
    glEnd();

    // Quadrado superior direito - amarelo
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.5, 0.5);
        glVertex2f(1.0, 0.5);
        glVertex2f(1.0, 1.0);
        glVertex2f(0.5, 1.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (256, 256); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quadrados Coloridos");

    glClearColor(1.0, 1.0, 1.0, 0.0); // fundo branco
    glShadeModel(GL_FLAT);
    glOrtho(0, 1, 0, 1, -1, 1);       // coordenadas normalizadas
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
