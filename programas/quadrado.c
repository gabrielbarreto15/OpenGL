#include <GL/glut.h>
#include <stdlib.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

// Variável global para cor: 0 = vermelho, 1 = azul
int cor = 0;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(256, 256); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Quadrado com Teclado");
    init();
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fundo branco
    glOrtho(0, 256, 0, 256, -1, 1);   // Coordenadas em pixels
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    // Define cor do quadrado
    if (cor == 0)
        glColor3f(1.0, 0.0, 0.0); // Vermelho
    else
        glColor3f(0.0, 0.0, 1.0); // Azul

    // Desenha quadrado
    glBegin(GL_POLYGON);
        glVertex2i(30, 226);  // Superior esquerdo
        glVertex2i(226, 226); // Superior direito
        glVertex2i(226, 30);  // Inferior direito
        glVertex2i(30, 30);   // Inferior esquerdo
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'a':
        case 'A':
            cor = 1; // azul
            glutPostRedisplay();
            break;
        case 'v':
        case 'V':
            cor = 0; // vermelho
            glutPostRedisplay();
            break;
        case 27: // ESC
            exit(0);
            break;
    }
}
