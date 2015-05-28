#include <gl/glut.h>
#include <stdlib.h>

static int year = 0, day = 0, Jupiter = 0;	//목성에 관한 공전각도를 따로 선언
void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
   //작성하시오
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glPushMatrix();				//원점 저장
	glRotatef(Jupiter, 0, 1, 0);		//목성 공전
	glTranslatef(4.0,0.0,0.0);		//목성을 거리 4만큼 놓음
	glColor3f(1, 0.5, 0);			//목성 색깔 : 갈색
	glutWireSphere(0.4,15,12);		//목성 생성
	glPushMatrix();				//저장
	glPopMatrix();
	glPopMatrix();				//좌표계 초기화	태양계 생성
	glColor3f (1.0, 0.0, 0.0);		//태양 색깔 
    glutWireSphere(0.5,20,16);			//태양
	glPushMatrix();
	glRotatef(year, 0, 1, 0);			//공전
	glTranslatef(2.0,0.0,0.0);		//이동
	glRotatef(day, 0, 1, 0);			//자전	
	glColor3f(0, 1, 0);			//지구 색깔
	glutWireSphere(0.25,10,8);		//지구
	glPushMatrix();
		 glRotatef(day, 0, 1, 0);
		 glTranslatef(0.7,0.0,0.0);	//달 위치
		 glColor3f(1, 1, 0);		//달 색깔
		 glutWireSphere(0.1,10,8);	//달
			glPushMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();				//다시 원점 좌표계로 돌아옴
	glutSwapBuffers();	
}




void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-6.0,6.0,-6.0,6.0,-20,20);	//가시거리를 변화 시킴
 }
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
    	case 'd':
         day = (day + 9) % 360;
         glutPostRedisplay();
         break;
 	case 'D':
         day = (day - 9) % 360;
         glutPostRedisplay();
         break;
 	case 'y':
         year = (year + 5) % 360;
	day = (day + 9) % 360;
	Jupiter = (Jupiter + 3) % 360;	//목성 공전 + 
        glutPostRedisplay();
        break;
     	case 'Y':
        year = (year - 5) % 360;
	day = (day - 9) % 360;
	Jupiter = (Jupiter - 3) % 360;	//목성 공전 - 
         glutPostRedisplay();
         break;
case 27:
	exit(0);	  break;
      default:
         break;
   }
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	
//D를 마구 누르면 버퍼가 엄청 생기니 더블버퍼를 쓰겠다.
   glutInitWindowSize (750, 750);			//창을 살짝 키움
   glutInitWindowPosition (150, 150);		//윈도우를 살짝 중앙에 놓기 위해
   glutCreateWindow (argv[0]);
   init ();
   glEnable(GL_DEPTH_TEST);	//어느것이 가까이 있는지 화면에 출력
   glutDisplayFunc(display);	//콜백함수 3가지 등록 -> dusplay를 우리가 구현
   glutReshapeFunc(reshape);	//모양이 바뀌면 어떻게 할 것인가
   glutKeyboardFunc(keyboard);	//d키를 눌렀을 때 반응하기 위함.
   glutMainLoop();
   return 0;
}
