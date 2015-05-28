#include <GL/glut.h> 					
#include <stdlib.h>

GLsizei wh = 500, ww = 500;	/* 초기 윈도우 크기 */
GLfloat size = 5.0;	/* 사각형 변 길이의 절반 */
GLint rx=0, ry=0;
bool trg=true;		//지우개 함수를 위한 논리값
void myinit(void)	{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void drawSquare(int x, int y)	{
	y=wh-y;
	if(trg==true) glColor3ub( (char)rand()%256, (char)rand()%256, (char)rand()%256);
 //stdlib.h rand - 정수를 임의로 생성 unsignedbyte니까 0~255
	else if(trg==false) glColor3ub( (char)0, (char)0,	(char)0);	// 지우개 함수 구현 조건문
	glBegin(GL_POLYGON);
		glVertex2f(x+size, y+size);
		glVertex2f(x-size, y+size);
		glVertex2f(x-size, y-size);
		glVertex2f(x+size, y-size);
	glEnd();
	glFlush();
}
void myReshape(GLsizei w, GLsizei h)
{
	/* 시역의 조절 */
	glViewport(0,0,w,h);
	ww=w;wh=h;
	/* 절단 상자 조절 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void key(unsigned char k, int xx, int yy){
	glColor3f(1.0,1.0,1.0);
	glRasterPos2i(rx,ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,k);
	rx +=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);
	glFlush();
}
void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){	
		drawSquare(x, y);
	}else if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN){
		rx=x;
		ry=wh-y;
		glutKeyboardFunc(key);
	}
}
void mousemove(GLint x, GLint y){
	drawSquare(x, y);
    //glutPostRedisplay( );	//강제로 디스플레이 콜백함수 생성
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();//clear 명령을 즉각 실행
}
void MyMainMenu(int entryID){	
	if(entryID == 1)  { exit(0); glutPostRedisplay();}
	else if (entryID == 2) {	//지우개 함수
		if(trg==true) trg=false;
		else if(trg==false) trg=true;
	}     
}
void MySubMenu(int entryID){				
    if(entryID == 1) size*=2;
    else if (entryID == 2 && size > 1)  size/=2;
}	
int main(int argc, char** argv){
glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("square");
	myinit();
	GLint MySubMenuID = glutCreateMenu(MySubMenu);
    glutAddMenuEntry("Increase square size", 1);
    glutAddMenuEntry("decrease square size", 2);
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("quit", 1);	
	glutAddSubMenu("Resize", MySubMenuID);
	glutAddMenuEntry("erase On/Off", 2);	//
    glutAttachMenu(GLUT_RIGHT_BUTTON);	
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutDisplayFunc(display); 
	glutReshapeFunc(myReshape);
	
    glutMainLoop( );			
    return 0;	
}
