#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"
#include "GLM.h"

#define NO_UPDATE 0

extern GLfloat aMVP[][16];
extern GLfloat x_center[], y_center[], z_center[];
extern GLfloat scale[];
extern GLfloat x_range_max, x_range_min;
extern GLfloat y_range_max, y_range_min;

void print_aMVP();
void update_center(GLfloat A[]);
void transMatrix(GLfloat *A);
void copyMatrix(GLfloat *A, const GLfloat B[][4]);
void multiMatrix(GLfloat A[][4], GLfloat *B);
void multiMatrix(GLfloat A[][4], GLfloat B[][4], GLfloat C[][4]);
void scaleAll();
void scaling(GLfloat x, GLfloat y, GLfloat z);
void transport(GLfloat x, GLfloat y, GLfloat z);
void transport(GLfloat x, GLfloat y, GLfloat z, bool no_update);
void rotate(GLfloat x, GLfloat y, GLfloat z);
void multiple_all_matrix(GLfloat M[][4]);
void multiple_all_matrix();
void multiple_range(int i);
void matrixInit();