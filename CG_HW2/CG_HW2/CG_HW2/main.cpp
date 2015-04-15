#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"
#include "GLM.h"

#ifndef GLUT_WHEEL_UP
# define GLUT_WHEEL_UP   0x0003
# define GLUT_WHEEL_DOWN 0x0004
#endif

#ifndef max
# define max_cmp(a,b) (((a)>(b))?(a):(b))
# define min_cmp(a,b) (((a)<(b))?(a):(b))
#endif

// Shader attributes
GLint iLocPosition;
GLint iLocColor;
GLint iLocMVP;
int current_obj;
char filename[100][100];

GLMmodel* OBJ;
GLfloat aMVP[16];
GLfloat *obj_color, *obj_vertices;
GLfloat cur_scene_x = 1;

void colorModel()
{


	// TODO:
	//// You should traverse the vertices and the colors of each vertex. 
	//// Normalize each vertex into [-1, 1], which will fit the camera clipping window.

	// number of triangles
	OBJ->numtriangles;

	// number of vertices
	OBJ->numvertices;

	// The center position of the model 
	// (should be calculated by yourself)
	OBJ->position[0];
	OBJ->position[1];
	OBJ->position[2];

	//printf("%f %f %f\n", OBJ->position[0], OBJ->position[1], OBJ->position[2]);
	
	obj_color = new GLfloat[(int)OBJ->numtriangles * 9];
	obj_vertices = new GLfloat[(int)OBJ->numtriangles * 9];
	GLfloat scale = 1;
	
	GLfloat x_max = -1e9;
	GLfloat x_min = 1e9;
	
	GLfloat y_max = -1e9;
	GLfloat y_min = 1e9;

	GLfloat z_max = -1e9;
	GLfloat z_min = 1e9;
	

	for(int i=0, j=0; i<(int)OBJ->numtriangles; i++, j += 3)
	{
		// the index of each vertex
		int indv1 = OBJ->triangles[i].vindices[0];
		int indv2 = OBJ->triangles[i].vindices[1];
		int indv3 = OBJ->triangles[i].vindices[2];

		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		GLfloat vx, vy, vz;
		obj_vertices[j*3+0] = OBJ->vertices[indv1*3+0] * scale;
		obj_vertices[j*3+1]  = OBJ->vertices[indv1*3+1] * scale;
		obj_vertices[j*3+2]  = OBJ->vertices[indv1*3+2] * scale;

		obj_vertices[(j+1)*3+0] = OBJ->vertices[indv2*3+0] * scale;
		obj_vertices[(j+1)*3+1] = OBJ->vertices[indv2*3+1] * scale;
		obj_vertices[(j+1)*3+2] = OBJ->vertices[indv2*3+2] * scale;

		obj_vertices[(j+2)*3+0] = OBJ->vertices[indv3*3+0] * scale;
		obj_vertices[(j+2)*3+1] = OBJ->vertices[indv3*3+1] * scale;
		obj_vertices[(j+2)*3+2] = OBJ->vertices[indv3*3+2] * scale;

		if( i == 0 ){
			x_min = x_max = OBJ->vertices[indv1*3+0];
			y_min = y_max = OBJ->vertices[indv1*3+1];
			z_min = z_max = OBJ->vertices[indv1*3+2];
		}
		else{
			x_max = max_cmp( x_max, OBJ->vertices[indv1*3+0] );
			x_max = max_cmp( x_max, OBJ->vertices[indv2*3+0] );
			x_max = max_cmp( x_max, OBJ->vertices[indv3*3+0] );

			x_min = min_cmp( x_min, OBJ->vertices[indv1*3+0] );
			x_min = min_cmp( x_min, OBJ->vertices[indv2*3+0] );
			x_min = min_cmp( x_min, OBJ->vertices[indv3*3+0] );
			
			y_max = max_cmp( y_max, OBJ->vertices[indv1*3+1] );
			y_max = max_cmp( y_max, OBJ->vertices[indv2*3+1] );
			y_max = max_cmp( y_max, OBJ->vertices[indv3*3+1] );

			y_min = min_cmp( y_min, OBJ->vertices[indv1*3+1] );
			y_min = min_cmp( y_min, OBJ->vertices[indv2*3+1] );
			y_min = min_cmp( y_min, OBJ->vertices[indv3*3+1] );

			z_max = max_cmp( z_max, OBJ->vertices[indv1*3+2] );
			z_max = max_cmp( z_max, OBJ->vertices[indv2*3+2] );
			z_max = max_cmp( z_max, OBJ->vertices[indv3*3+2] );

			z_min = min_cmp( z_min, OBJ->vertices[indv1*3+2] );
			z_min = min_cmp( z_min, OBJ->vertices[indv2*3+2] );
			z_min = min_cmp( z_min, OBJ->vertices[indv3*3+2] );
		}
		// colors
		GLfloat c1, c2, c3;
		obj_color[j*3+0] = OBJ->colors[indv1*3+0];
		obj_color[j*3+1] = OBJ->colors[indv1*3+1];
		obj_color[j*3+2] = OBJ->colors[indv1*3+2];

		obj_color[(j+1)*3+0] = OBJ->colors[indv2*3+0];
		obj_color[(j+1)*3+1] = OBJ->colors[indv2*3+1];
		obj_color[(j+1)*3+2] = OBJ->colors[indv2*3+2];

		obj_color[(j+2)*3+0] = OBJ->colors[indv3*3+0];
		obj_color[(j+2)*3+1] = OBJ->colors[indv3*3+1];
		obj_color[(j+2)*3+2] = OBJ->colors[indv3*3+2];
	}

	GLfloat max_line = max_cmp( x_max - x_min, y_max - y_min );
	max_line = max_cmp( max_line, z_max - z_min);
	scale = 2 / max_line;

	for(int i = 0; i < (int)OBJ->numtriangles * 9; ++i)
		obj_vertices[i] *= scale;
	
	GLfloat x_move = 0,  y_move = 0, z_move = 0;

	x_max *= scale;
	y_max *= scale;
	z_max *= scale;
	
	x_min *= scale;
	y_min *= scale;
	z_min *= scale;
	

	x_move = (x_max + x_min) / 2;
	y_move = (y_max + y_min) / 2;
	z_move = (z_max + z_min) / 2;

	for(int i = 0; i < (int)OBJ->numtriangles * 9; i = i + 3){
		obj_vertices[i] -= x_move;
		obj_vertices[i+1] -= y_move;
		obj_vertices[i+2] -= z_move;
	}
	//printf("scale = %f\n", scale);
}

void loadOBJString(){
	for(int i = 0; i <33; ++i){ 
		sprintf(filename[i], "ColorModels/model (%d).obj", i+1);
	}
}

void loadOBJModel()
{
	// read an obj model here
	loadOBJString();
	OBJ = glmReadOBJ(filename[current_obj]);
	//printf("%s\n", filename[current_obj]);

	// traverse the color model
	colorModel();
}
void idle()
{
	glutPostRedisplay();
}

void renderScene(void)
{
	///TODO(HW2):
	// Calculate your transform matrices and multiply them.
	// Finally, assign the MVP matrix to aMVP.
	// NOTE:
	// You should add comment to describe where are your Model,
	// Viewing, and Projection transform matrices.




	///Example of displaying colorful triangle
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(iLocPosition);
	glEnableVertexAttribArray(iLocColor);

	static GLfloat triangle_color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	static GLfloat triangle_vertex[] = {
		 0.2f, -0.2f, 0.0f,
		 0.0f,  0.2f, 0.0f,
		-0.2f, -0.2f, 0.0f
	};

	// Move example triangle to left by 0.5
	aMVP[0] = cur_scene_x;	aMVP[4] = 0;	aMVP[8] = 0;	aMVP[12] = 0;
	aMVP[1] = 0;	aMVP[5] = cur_scene_x;	aMVP[9] = 0;	aMVP[13] = 0;
	aMVP[2] = 0;	aMVP[6] = 0;	aMVP[10] = cur_scene_x;	aMVP[14] = 0;
	aMVP[3] = 0;	aMVP[7] = 0;	aMVP[11] = 0;	aMVP[15] = 1;
	

	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, obj_vertices);
	glVertexAttribPointer(   iLocColor, 3, GL_FLOAT, GL_FALSE, 0, obj_color);

	glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, aMVP);

	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, 3 * (int)OBJ->numtriangles);
	
	glutSwapBuffers();
}

void showShaderCompileStatus(GLuint shader, GLint *shaderCompiled){
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderCompiled);
	if(GL_FALSE == (*shaderCompiled))
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		GLchar *errorLog = (GLchar*) malloc(sizeof(GLchar) * maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		fprintf(stderr, "%s", errorLog);

		glDeleteShader(shader);
		free(errorLog);
	}
}

void setShaders()
{
	GLuint v, f, p;
	char *vs = NULL;
	char *fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("shader.vert");
	fs = textFileRead("shader.frag");

	glShaderSource(v, 1, (const GLchar**)&vs, NULL);
	glShaderSource(f, 1, (const GLchar**)&fs, NULL);

	free(vs);
	free(fs);

	// compile vertex shader
	glCompileShader(v);
	GLint vShaderCompiled;
	showShaderCompileStatus(v, &vShaderCompiled);
	if(!vShaderCompiled) system("pause"), exit(123);

	// compile fragment shader
	glCompileShader(f);
	GLint fShaderCompiled;
	showShaderCompileStatus(f, &fShaderCompiled);
	if(!fShaderCompiled) system("pause"), exit(456);

	p = glCreateProgram();

	// bind shader
	glAttachShader(p, f);
	glAttachShader(p, v);

	// link program
	glLinkProgram(p);

	iLocPosition = glGetAttribLocation (p, "av4position");
	iLocColor    = glGetAttribLocation (p, "av3color");
	iLocMVP		 = glGetUniformLocation(p, "mvp");

	glUseProgram(p);
}


void processMouse(int who, int state, int x, int y)
{
	printf("(%d, %d) ", x, y);

	switch(who){
	case GLUT_LEFT_BUTTON:   printf("left button   "); break;
	case GLUT_MIDDLE_BUTTON: printf("middle button "); break;
	case GLUT_RIGHT_BUTTON:  printf("right button  "); break; 
	case GLUT_WHEEL_UP:      
		printf("wheel up      "); 
		cur_scene_x = cur_scene_x + 0.01;
		//glutDisplayFunc (renderScene);
		break;
	case GLUT_WHEEL_DOWN:   
		printf("wheel down    "); 
		cur_scene_x = cur_scene_x - 0.01;
		//glutDisplayFunc (renderScene);
		break;
	default:                 printf("%-14d", who);     break;
	}

	switch(state){
	case GLUT_DOWN:          printf("start ");         break;
	case GLUT_UP:            printf("end   ");         break;
	}

	printf("\n");
}

void processMouseMotion(int x, int y){  // callback on mouse drag
	printf("(%d, %d) mouse move\n", x, y);
}


void processNormalKeys(unsigned char key, int x, int y) {
	//printf("key = %d ", key );
	if( key < 97 && key != 27 )  key += 32;

	switch(key) {
		case 27: /* the Esc key */ 
			exit(0); 
			break;
		case 99:
			loadOBJModel();
			glutDisplayFunc (renderScene);
			break;
		case 'n':
			current_obj = ( current_obj + 1 ) % 33;
			loadOBJModel();
			glutDisplayFunc (renderScene);
			break;
		case 'b':
			current_obj  -= 1;
			current_obj += (current_obj < 0 )*33;
			loadOBJModel();
			glutDisplayFunc (renderScene);
			break;
		case 'h':
			printf("===========THIS IS HELP !!!!!==========\n");
			printf("Press 'c' to change mode(solid / wireframe)\n\n");
			printf("Press 'b' to go to last model\n\n");
			printf("Press 'n' to go to next model\n\n");
			printf("If you want to exit, please press 'esc'\n");
			printf("===============================\n");
			break;

			
	}
}

int main(int argc, char **argv) {
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(460, 40);
	glutInitWindowSize(800, 800);
	glutCreateWindow("10320 CS550000 CG HW2 TA");

	glewInit();
	if(glewIsSupported("GL_VERSION_2_0")){
		printf("Ready for OpenGL 2.0\n");
	}else{
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}

	// load obj models through glm
	loadOBJModel();

	// register glut callback functions
	glutDisplayFunc (renderScene);
	glutIdleFunc    (idle);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc   (processMouse);
	glutMotionFunc  (processMouseMotion);

	glEnable(GL_DEPTH_TEST);

	// set up shaders here
	setShaders();

	// main loop
	glutMainLoop();

	// free
	glmDelete(OBJ);

	return 0;
}
