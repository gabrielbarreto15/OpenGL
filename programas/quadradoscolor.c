// quadradoscolor.c
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846

typedef struct {
    float r, g, b;
} Color;

Color hsiToRgb(float H) {
    float R, G, B;
    float S = 1.0, I = 1.0;

    H = fmod(H, 360.0); // Garante que H esteja em [0,360)
    float radH = H * PI / 180.0;

    if (H < 120) {
        R = I * (1 + S * cos(radH) / cos(PI / 3 - radH));
        G = 3 * I - (R + 0);
        B = 0;
    } else if (H < 240) {
        H -= 120;
        radH = H * PI / 180.0;
        G = I * (1 + S * cos(radH) / cos(PI / 3 - radH));
        B = 3 * I - (G + 0);
        R = 0;
    } else {
        H -= 240;
        radH = H * PI / 180.0;
        B = I * (1 + S * cos(radH) / cos(PI / 3 - radH));
        R = 3 * I - (B + 0);
        G = 0;
    }

    // Normaliza valores para [0,1]
    R = fmin(fmax(R, 0), 1);
    G = fmin(fmax(G, 0), 1);
    B = fmin(fmax(B, 0), 1);

    Color color = { R, G, B };
    return color;
}

// Hue inicial para cada vértice
float hue[4] = { 0, 90, 180, 270 };

void timer(int value) {
    for (int i = 0; i < 4; i++) {
        hue[i] += 1.0;
        if (hue[i] >= 360.0)
            hue[i] -= 360.0;
    }

    glutPostRedisplay();
    glutTimerFunc(33, timer, 1); // ~30 fps
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    Color c0 = hsiToRgb(hue[0]);
    Color c1 = hsiToRgb(hue[1]);
    Color c2 = hsiToRgb(hue[2]);
    Color c3 = hsiToRgb(hue[3]);

    glBegin(GL_POLYGON);
        glColor3f(c0.r, c0.g, c0.b);
        glVertex2f(0.25, 0.25);

        glColor3f(c1.r, c1.g, c1.b);
        glVertex2f(0.75, 0.25);

        glColor3f(c2.r, c2.g, c2.b);
        glVertex2f(0.75, 0.75);

        glColor3f(c3.r, c3.g, c3.b);
        glVertex2f(0.25, 0.75);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (256, 256); 
    glutInitWindowPosition (100, 100); 
    glutCreateWindow("Quadrado Colorido HSI");

    glClearColor(1.0, 1.0, 1.0, 0.0); // Fundo branco

    // Comentado para permitir interpolação (degradê)
    // glShadeModel(GL_FLAT);

    glOrtho(0, 1, 0, 1, -1, 1);

    glutDisplayFunc(display);
    glutTimerFunc(33, timer, 1); // Inicia temporizador

    glutMainLoop();
    return 0;
}
