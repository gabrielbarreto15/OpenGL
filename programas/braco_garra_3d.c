#include <GL/glut.h>
#include <stdlib.h>

static int base = 0;
static int shoulder = 0, elbow = 0;
static int dedo_indicador = 0, dedo_medio = 0, dedo_polegar = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Rotação da base
    glRotatef((GLfloat) base, 0.0, 1.0, 0.0);

    // Ombro
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);

    // Braço superior
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // vermelho
    glScalef(2.0, 0.4, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cotovelo
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);

    // Braço inferior
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0); // verde
    glScalef(2.0, 0.4, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Base da garra
    glTranslatef(1.0, 0.0, 0.0);

    // === Dedo Indicador ===
    glPushMatrix();
    glTranslatef(0.2, 0.2, 0.0);
    glRotatef((GLfloat)dedo_indicador, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // azul
    glScalef(0.6, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // === Dedo Médio ===
    glPushMatrix();
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef((GLfloat)dedo_medio, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0); // ciano
    glScalef(0.6, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // === Dedo Polegar ===
    glPushMatrix();
    glTranslatef(0.2, -0.2, 0.0);
    glRotatef((GLfloat)dedo_polegar, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); // amarelo
    glScalef(0.6, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -8.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'b': base = (base + 5) % 360; break;
        case 'B': base = (base - 5) % 360; break;
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'i': dedo_indicador = (dedo_indicador + 5) % 360; break;
        case 'I': dedo_indicador = (dedo_indicador - 5) % 360; break;
        case 'm': dedo_medio = (dedo_medio + 5) % 360; break;
        case 'M': dedo_medio = (dedo_medio - 5) % 360; break;
        case 'p': dedo_polegar = (dedo_polegar + 5) % 360; break;
        case 'P': dedo_polegar = (dedo_polegar - 5) % 360; break;
        case 27: exit(0); break; // ESC
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Braco com Garra 3D");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
