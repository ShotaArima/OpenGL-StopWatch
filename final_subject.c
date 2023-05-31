#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define KEY_ESC 27

//�J�E���g�n�ϐ��̐錾
	int count=0;
	int system_key=0;
	int count_sec=0 ;
	int count_min=0;

//�p�x�n�ϐ��̐錾
	float theta = 0;//theta�̐錾
	float theta_min=0;

//���Ԍn�ϐ��̐錾
	time_t start_time;
	time_t current_time;
	time_t prev_time=0;

//�֐��̐錾
	void polarview(void);
	void resetview(void);

//���C�g�̈ʒu�̐錾
	float light_position[] = { 0.0, 1.0, 0.0, 0.0 };

//�ʒu�ɂ��Ă̕ϐ��̐錾
	int mButton;
	float distance,twist,elevation,azimuth;


//�V�F�[�f�B���O�ɂ���

	//��
	float diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular1[] = { 0.5, 0.5, 0.5, 1.0 };
	float ambient1[] = { 0.2, 0.2, 1.0, 1.0 };
	float shininess1 = 60.0;

	//��
	float diffuse2[] = { 0.7, 0.1, 0.0, 1.0 };
	float specular2[] = { 0.8, 0.0, 0.0, 1.0 };
	float ambient2[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess2 = 100.0;

	//��
	float diffuse3[] = { 0.0, 0.4, 7.0, 1.0 };
	float specular3[] = { 0, 0, 0, 1.0 };
	float ambient3[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess3 = 128.0;

	//��
	float diffuse4[] = { 0.0, 0.0, 0.0, 1.0 };
	float specular4[] = { 0, 0, 0, 1.0 };
	float ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess4 = 128.0;

void display(void)
{
//�͂���
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	polarview();
	glEnable(GL_DEPTH_TEST);/*Z Buffer enable*/
	glEnable(GL_LIGHTING);/*Shading�v�Z�̊J�n*/
	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
	glRotatef(-150.0 ,0.0 ,1.0 ,0.0);//theta�p��x��,y��,z���ɉ�]������
	
//�b�j�̋L�q

	//�b�j�̐ݒ�
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse2);
 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular2);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient2);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess2);
	glNormal3f(0.0,1.0,0.0);

	//�b�j�̕`��
	glPushMatrix();
		glRotatef(-theta ,0.0 ,1.0 ,0.0);//theta�p��x��,y��,z���ɉ�]������
		glBegin(GL_POLYGON);
			glVertex3f( 0.05,0.05,0.0);
			glVertex3f( 0.0,0.05,0.9);
			glVertex3f(-0.05,0.05,0.0);
		glEnd();
	glPopMatrix();

//���j�̋L�q
	//���j�̐ݒ�
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse3);
 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular3);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess3);
	glNormal3f(0.0,1.0,0.0);

	//���j�̕`��
	glPushMatrix();
		glRotatef(-theta_min ,0.0 ,1.0 ,0.0);//theta�p��x��,y��,z���ɉ�]������
		glBegin(GL_POLYGON);
			glVertex3f( 0.05,0.05,0.0);
			glVertex3f( 0.0,0.05,0.9);
			glVertex3f(-0.05,0.05,0.0);
		glEnd();
	glPopMatrix();

//���v�Ղ̋L�q

	//���v�Ղ̐ݒ�
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular1);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess1);

	//���v�Ղ̕`��
	glBegin(GL_POLYGON);
		glNormal3f(0.0,1.0,0.0);
		const int numSegments = 50; /* �~�̕����� */
		const float radius = 1.0; /* �~�̔��a */
		for (int i = 0; i < numSegments; ++i) 
		{
		    float theta_cir = 2.0 * 3.14159 * ((float)i / (float)numSegments);//�p�x
		    float x = radius * cos(theta_cir); /* x���W�̌v�Z */
		    float z = radius * sin(theta_cir); /* z���W�̌v�Z */
		    glVertex3f(x, 0.0, z); /* ���_�̒ǉ� */
		}
	glEnd();

//�ڐ���̋L�q
	//�ڐ���̐ݒ�
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse4);
	 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular4);
		glMaterialfv( GL_FRONT, GL_AMBIENT, ambient4);
		glMaterialf( GL_FRONT, GL_SHININESS, shininess4);
		glNormal3f(0.0,1.0,0.0);
		for(int i=0;i<60;i++)
		{
			glPushMatrix();
				glRotatef(i*6 ,0.0 ,1.0 ,0.0);//6������x��,y��,z���ɉ�]������
				glBegin(GL_POLYGON);
					glVertex3f( 0.01,0.05,0.9);//����
					glVertex3f( 0.01,0.05,0.95);//����
					glVertex3f(-0.01,0.05,0.95);//�E��
					glVertex3f(-0.01,0.05,0.9);//�E��
				glEnd();
			glPopMatrix();
		}
		for(int i=0;i<12;i++)
		{
			glPushMatrix();
				glRotatef(i*30 ,0.0 ,1.0 ,0.0);//6������x��,y��,z���ɉ�]������
				glBegin(GL_POLYGON);
					glVertex3f( 0.017,0.05,0.85);//����
					glVertex3f( 0.017,0.05,0.95);//����
					glVertex3f(-0.017,0.05,0.95);//�E��
					glVertex3f(-0.017,0.05,0.85);//�E��
				glEnd();
			glPopMatrix();
		}

	glPopMatrix();

//�܂Ƃ�
	glDisable(GL_LIGHTING);/*Shading�v�Z�I��*/
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

//�ǉ�:idle�֐�
void idle(void)
{
	//system_key=1:�X�g�b�v�E�I�b�`�̓��쒆
	if (system_key == 1) 
	{
	    // �X�g�b�v�E�H�b�`�����쒆�̏���
	    //���ݎ����̎擾�˃X�y�[�X�����ꂽ����
		time_t current_time=time(NULL);

	    //�X�^�[�g���Ԃ���̍����擾
	    double elapsed_time=difftime(current_time, start_time);

	    //1�b�Ԃ̃^�C�~���O�𐶐� & �p�x�̒���
        if (current_time!=prev_time) 
        {
        	count_sec++;
        	if(count_sec>59)
    		{
    			count_sec=0;
    			count_min++;
    		}
            // printf("%2d:%2d\n",count_min,count_sec);
            prev_time=current_time;
        }
    }
    theta=count_sec*6;
    theta_min=count_min*6;
	glutPostRedisplay();
}

//�L�[�{�[�h�A�N�V����
void myKbd(unsigned char key, int x, int y)
{
	switch(key)
	{
		//r=���Z�b�g
		case 'r':
			system_key=0;
			printf("%2d:%2d�ŃX�g�b�v�E�I�b�`�����Z�b�g���܂��B\n",count_min,count_sec);
			count=0;
			count_sec=0;
			count_min=0;
			break;

		//space(32)=�X�^�[�g�A�X�g�b�v
		case 32:
			count++;

			//�X�g�b�v�E�I�b�`�̒�~�w��
			if (count%2==0)
			{
				system_key=0;
				printf("%2d:%2d�ŃX�g�b�v�E�I�b�`����~���܂��B\n",count_min,count_sec);
			}

			//�X�g�b�v�E�I�b�`�̓���J�n�w��
			else
			{
				system_key=1;
			//�X�^�[�g�����̐ݒ�
				printf("�X�g�b�v�E�I�b�`�����삵�܂��B\n");
			}
			break;

		//ESC=��ʂ����
		case KEY_ESC:
			exit(0);
	}
}


//
void myInit(char * progname)
{
	int width = 600, height =600;
	
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor(0.0,0.0,0.0,1.0);
	glutKeyboardFunc(myKbd);
	resetview();
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHT0);/*0�Ԃ̃��C�g�𗘗p�\�ɂ���*/
}

//�`��̉掿�ݒ��ύX����֐�
void myReshape(int width,int height)
{
	float aspect =(float)width/(float)height;
	
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0,aspect,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
}

//�ɍ��W�ϊ�����֐�
void polarview(void)
{
	glTranslatef(0.0,0.0,-distance);
	glRotatef(-twist,0.0,0.0,1.0);
	glRotatef(-elevation,1.0,0.0,0.0);
	glRotatef(-azimuth,0.0,1.0,0.0);
}

//�e�p�����[�^��������Ԃɖ߂��֐�
void resetview(void)
{
	distance = 6.0;
	twist=0.0;
	elevation=-90.0;
	azimuth=30.0;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	myInit(argv[0]);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);//�ǉ�
	glutMainLoop();
	exit(0);
}