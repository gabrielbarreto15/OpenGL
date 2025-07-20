#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[30]={
  0.0,  30.0, 30.0,  // 0
  20.0, 30.0, 30.0,  // 1
  30.0, 20.0, 30.0,  // 2
  30.0,  0.0, 30.0,  // 3
  0.0,   0.0, 30.0,  // 4
  0.0,  30.0,  0.0,  // 5
  30.0, 30.0,  0.0,  // 6
  30.0,  0.0,  0.0,  // 7
  0.0,   0.0,  0.0,  // 8
  30.0, 30.0, 20.0   // 9
}; 

static GLubyte frenteIndices[]    = {0,4,3,2,1};
static GLubyte trasIndices[]      = {5,6,7,8};
static GLubyte esquerdaIndices[]  = {0,5,8,4};
static GLubyte direitaIndices[]   = {2,3,7,6,9};
static GLubyte topoIndices[]      = {0,1,9,6,5};
static GLubyte fundoIndices[]     = {3,4,8,7};
static GLubyte trianguloIndices[] = {1,2,9};

static int eixoy, eixox;
int largura, altura;

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Tipos de Projeções");
  init();
  glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glOrtho (-50, 50, -50, 50, -50 , 50);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  largura = w; 
  altura = h;
}

void display(void){
  glPushMatrix();
  glRotatef((GLfloat) eixoy, 0.0, 1.0, 0.0);
  glRotatef((GLfloat) eixox, 1.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);

  glColor3f(AZUL);      glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, frenteIndices);
  glColor3f(AMARELO);   glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);
  glColor3f(VERMELHO);  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trasIndices);
  glColor3f(VERDE);     glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, direitaIndices);
  glColor3f(CYAN);      glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, topoIndices);
  glColor3f(LARANJA);   glDrawElements(GL_QUADS,   4, GL_UNSIGNED_BYTE, fundoIndices);
  glColor3f(CINZA);     glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, trianguloIndices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27: exit(0); break;

    case 'p': // perspectiva
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(65.0, (GLfloat)largura/(GLfloat)altura, 20.0, 120.0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;

    case 'o': // ortográfica
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-50, 50, -50, 50, -50 , 50);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glutPostRedisplay();
      break;

    // Vistas adicionais
    case 't': // topo
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 90, 0,  0, 0, 0,  0, 0, -1);
      glutPostRedisplay();
      break;
    case 'f': // fundo
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, -90, 0,  0, 0, 0,  0, 0, 1);
      glutPostRedisplay();
      break;
    case 'F': // frente
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 0, 90,  0, 0, 0,  0, 1, 0);
      glutPostRedisplay();
      break;
    case 'T': // traseira
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 0, -90,  0, 0, 0,  0, 1, 0);
      glutPostRedisplay();
      break;
    case 'e': // esquerda
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(-90, 0, 0,  0, 0, 0,  0, 1, 0);
      glutPostRedisplay();
      break;
    case 'd': // direita
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(90, 0, 0,  0, 0, 0,  0, 1, 0);
      glutPostRedisplay();
      break;
    case 'c': // canto
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(60, 60, 60, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
  }
}
