#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

#define NUM_POLIGONOS 4

typedef struct {
    int x1, y1, x2, y2;
    float cor_fundo[3];
    float cor_borda[3];
} Poligono;

Poligono polys[NUM_POLIGONOS];

int modo = 0; // 0 = mudar fundo, 1 = mudar borda

void initPoligonos() {
    polys[0] = (Poligono){30, 143, 113, 226, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
    polys[1] = (Poligono){143, 143, 226, 226, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
    polys[2] = (Poligono){30, 30, 113, 113, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
    polys[3] = (Poligono){143, 30, 226, 113, {1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 256, 0, 256);
    initPoligonos();
    srand(time(NULL));
}

void desenhaPoligono(Poligono p) {
    // Preenchimento
    glColor3fv(p.cor_fundo);
    glBegin(GL_POLYGON);
        glVertex2i(p.x1, p.y1);
        glVertex2i(p.x2, p.y1);
        glVertex2i(p.x2, p.y2);
        glVertex2i(p.x1, p.y2);
    glEnd();

    // Borda
    glColor3fv(p.cor_borda);
    glBegin(GL_LINE_LOOP);
        glVertex2i(p.x1, p.y1);
        glVertex2i(p.x2, p.y1);
        glVertex2i(p.x2, p.y2);
        glVertex2i(p.x1, p.y2);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < NUM_POLIGONOS; i++) {
        desenhaPoligono(polys[i]);
    }

    glFlush();
}

int pontoDentro(Poligono p, int x, int y) {
    return x >= p.x1 && x <= p.x2 && y >= p.y1 && y <= p.y2;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int y_invertido = 256 - y;

        for (int i = 0; i < NUM_POLIGONOS; i++) {
            if (pontoDentro(polys[i], x, y_invertido)) {
                float nova_cor[3] = {
                    (float)rand() / RAND_MAX,
                    (float)rand() / RAND_MAX,
                    (float)rand() / RAND_MAX
                };

                if (modo == 0) { // mudar fundo
                    polys[i].cor_fundo[0] = nova_cor[0];
                    polys[i].cor_fundo[1] = nova_cor[1];
                    polys[i].cor_fundo[2] = nova_cor[2];
                } else { // mudar borda
                    polys[i].cor_borda[0] = nova_cor[0];
                    polys[i].cor_borda[1] = nova_cor[1];
                    polys[i].cor_borda[2] = nova_cor[2];
                }

                glutPostRedisplay();
                break;
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'b') {
        modo = 1; // mudar borda
    } else if (key == 'f') {
        modo = 0; // mudar fundo
    } else if (key == 27) {
        exit(0); // ESC
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(256, 256);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Seleção de Polígonos");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
