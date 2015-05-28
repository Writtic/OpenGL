#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}

void myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
        glOrtho(-3.0, 3.0, -3.0 * (GLfloat) h / (GLfloat) w,
            3.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-3.0 * (GLfloat) w / (GLfloat) h,
            3.0 * (GLfloat) w / (GLfloat) h, -3.0, 3.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);	//검정색으로
	glutWireTeapot(1.0);
	glFlush();
}

void size_menu( GLint id){
	//크기 변환
	if(id==1)	glScalef(2,1,1);
	else if(id==2)	glScalef(1,2,1);
	else if(id==3)	glScalef(1,1,2);
	else if(id==4)	glScalef(0.5,1,1);
	else if(id==5)	glScalef(1,0.5,1);
	else if(id==6)	glScalef(1,1,0.5);
	glutPostRedisplay();
}
void translate_menu( GLint id){
	//위치 이동
	if(id==1)	glTranslatef(1,0,0);
	else if(id==2)	glTranslatef(0,1,0);
	else if(id==3)	glTranslatef(0,0,1);
	else if(id==4)	glTranslatef(-1,0,0);
	else if(id==5)	glTranslatef(0,-1,0);
	else if(id==6)	glTranslatef(0,0,-1);
	glutPostRedisplay();
}


#define PI 3.1415926535897		//PI값 저장.
void rotate_menu( GLint id){
	//회전
	GLfloat R=10*(PI / 180);
	GLfloat M[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	//참고용 행렬
/* 	[ 00 01 02 03] * 
	*	[ 04 05 06 07] *
	*	[ 08 09 10 11] *
	*	[ 12 13 14 15] */
	if(id==1) //함수가 아닌 실제 변환 행렬을 대입시켜 보았습니다.
{M[0]=cos(R); M[1]=-sin(R); M[4]=sin(R); M[5]=cos(R); glMultMatrixf(M); }		
	else if(id==2)
{M[0]=cos(R); M[2]=-sin(R); M[8]=sin(R); M[10]=cos(R); glMultMatrixf(M);}
	else if(id==3)
{M[5]=cos(R); M[6]=-sin(R); M[9]=sin(R); M[10]=cos(R); glMultMatrixf(M);}
	else if(id==4)	glRotatef(-10,1,0,0);
	else if(id==5)	glRotatef(-10,0,1,0);
	else if(id==6)	glRotatef(-10,0,0,1);
	glutPostRedisplay();
}
void right_menu( GLint id){
	//원래 위치로
		if(id==1){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	glutPostRedisplay();
}
void shearing_menu(GLint id)
{
	GLfloat M[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	//참고용 행렬
/* 	[ 00 01 02 03] * 
	*	[ 04 05 06 07] *
	*	[ 08 09 10 11] *
	*	[ 12 13 14 15] */
	//전단 변환
	if(id==1){
		M[4]=1;
		glMultMatrixf(M);}
	else if(id==2){
		M[1]=1;
		glMultMatrixf(M);}
	else if(id==3){
		M[6]=1;
		glMultMatrixf(M);}
	else if(id==4){
		M[4]=-1;
		glMultMatrixf(M);}
	else if(id==5){
		M[1]=-1;
		glMultMatrixf(M);}
	else if(id==6){
		M[6]=-1;
		glMultMatrixf(M);}
	glutPostRedisplay();
}
int main(void){
	int s_menu, t_menu, r_menu;
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow("teapot transform");
	s_menu = glutCreateMenu(size_menu);
    glutAddMenuEntry("x축 확대 ",1);
    glutAddMenuEntry("y축 확대",2);
    glutAddMenuEntry("z축 확대",3);
	glutAddMenuEntry("x축 축소 ",4);
    glutAddMenuEntry("y축 축소",5);
    glutAddMenuEntry("z축 축소",6);
    t_menu = glutCreateMenu(translate_menu);
    glutAddMenuEntry("x축 이동 ",1);
    glutAddMenuEntry("y축 이동",2);
    glutAddMenuEntry("z축 이동",3);
	glutAddMenuEntry("-x축 이동 ",4);
    glutAddMenuEntry("-y축 이동",5);
    glutAddMenuEntry("-z축 이동",6);
    r_menu = glutCreateMenu(rotate_menu);
    glutAddMenuEntry("x축 +방향회전 ",1);
    glutAddMenuEntry("y축 +방향회전",2);
    glutAddMenuEntry("z축 +방향회전",3);
	glutAddMenuEntry("x축 -방향회전 ",4);
    glutAddMenuEntry("y축 -방향회전",5);
    glutAddMenuEntry("z축 -방향회전",6);
	int sh_menu = glutCreateMenu(shearing_menu);
    glutAddMenuEntry("x +방향 전단 ",1);
    glutAddMenuEntry("y +방향 전단",2);
    glutAddMenuEntry("z +방향 전단",3);
	glutAddMenuEntry("x -방향 전단 ",4);
    glutAddMenuEntry("y -방향 전단",5);
    glutAddMenuEntry("z -방향 전단",6);
    glutCreateMenu(right_menu);
	glutAddMenuEntry("원래 위치로 ",1);
    glutAddSubMenu("Resize", s_menu);
    glutAddSubMenu("Translate by 1", t_menu);
    glutAddSubMenu("Rotate by 10 degree", r_menu);
	glutAddSubMenu("Shearing", sh_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
    glutReshapeFunc(myReshape); 
    glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
