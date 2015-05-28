#include <gl/glut.h>
#include <stdio.h>
GLint shoulder=0, elbow=0;	//어깨, 팔꿈치 회전각
void init(void) 
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_DEPTH_TEST);
}
void display(void)
{
   
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//뎁스 버퍼도 클리어를 시켜야한다.
   glColor3f (0.35, 0.35, 0.35);	//상자 색깔 회색
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   // 카메라 위치 지정할 것
   gluLookAt(1,1,5,0,0,0,0,1,0);
   // 어깨의 회전을 위한 변환 작성 할 것: 회전중심이 왼쪽 끝임
   glTranslatef(-1.0,0.0,0.0);		//회전축을 어깨로 설정하기 위해 좌표축 이동
   glRotatef(shoulder, 0, 0, 1);		//어깨 회전
   glPushMatrix();
		glTranslatef(1.0,0.0,0.0);//박스가 좌표계 중심에서 생성되므로 다시 돌아옴.
   		glScalef (2.0, 0.4, 1.0);	//팔 마디 확대
   		glutWireCube (1.0);	//상자 생성
   	glPopMatrix();					
	//팔꿈치의 회전을 위한 변환 작성할 것 : 회전 중심이 관절임.
	glTranslatef(2.0,0.0,0.0);//초기 좌표값을 -1.0 해주어서 상자 길이인 2.0만큼 이동
	glRotatef(elbow, 0, 0, 1);//관절 회전
   	glPushMatrix();					
		glTranslatef(1.0,0.0,0.0);//박스가 좌표계 중심에서 생성되므로 1만큼 이동
   		glScalef (2.0, 0.4, 1.0);	//팔 마디 확대
   		glutWireCube (1.0);	//상자 생성
   	glPopMatrix();
	glutSwapBuffers();
}
void reshape (int w, int h)	//처음으로 화면이 생길때 호출이 된다.
{
	//뷰포트 변환
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	//투상 행렬
	gluPerspective(70, (GLfloat)w/(GLfloat)h, 3, 20);
}



void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 's':
		if(shoulder <= 120)
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		if(elbow <= 100)
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		if(shoulder >= 0)
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		if(elbow >= 0)
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		//exit(0);
		break;
	default:
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glEnable(GL_DEPTH_TEST);		//후위곱셈
	glutDisplayFunc(display);		//뷰 행렬 - 모델 행렬
	glutReshapeFunc(reshape);		//뷰포트 변환 - 투상 행렬
	glutKeyboardFunc(keyboard);	//키보드 제어
	glutMainLoop();
	return 0;
}
