#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define N_VERTICES 6
GLfloat vertices[N_VERTICES][3] = {
  {-4.0,  0.0, 0.0}, 
  {-4.0, +4.0, 0.0}, 
  {+4.0, -4.0, 0.0}, 
  {-4.0, -4.0, 0.0}, 
  {+4.0, +4.0, 0.0}, 
  {+4.0,  0.0, 0.0}
};

GLint largura, altura;
GLint tipoNURBS = 0; // 0 = uniforme, 1 = uniforme aberto, 2 = não uniforme

GLfloat esquerda = -5, direita = +5;
GLfloat fundo = -5, topo = +5;
GLfloat longe = +5, perto = -5;

GLUnurbsObj *nc;

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);

  // Define vetor de nós de acordo com o tipo
  GLfloat knots_uniforme[10]       = {0,1,2,3,4,5,6,7,8,9};
  GLfloat knots_uniforme_aberto[10]= {0,0,0,0,1,2,3,3,3,3}; // grau 3
  GLfloat knots_nao_uniforme[10]   = {0,0,0,0,1,2.5,3,3,3,3};

  GLfloat* nos = NULL;

  switch(tipoNURBS){
    case 0: nos = knots_uniforme; break;
    case 1: nos = knots_uniforme_aberto; break;
    case 2: nos = knots_nao_uniforme; break;
  }

  gluBeginCurve(nc);
  gluNurbsCurve(nc, 10, nos, 3, &vertices[0][0], 4, GL_MAP1_VERTEX_3);
  gluEndCurve(nc);

  // desenha controle
  glPointSize(5.0);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < N_VERTICES; i++) 
    glVertex3fv(vertices[i]);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < N_VERTICES; i++) 
    glVertex3fv(vertices[i]);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  nc = gluNewNurbsRenderer();
  gluNurbsProperty(nc, GLU_SAMPLING_TOLERANCE, 5.0);
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  largura = w; altura = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(esquerda, direita, fundo, topo, perto, longe);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'u':
      tipoNURBS = 0; // uniforme
      break;
    case 'o':
      tipoNURBS = 1; // uniforme aberto
      break;
    case 'n':
      tipoNURBS = 2; // não uniforme
      break;
    case 27:
      exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("NURBS com Tipos de Vetor de Nós");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
