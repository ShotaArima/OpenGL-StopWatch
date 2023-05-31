#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define KEY_ESC 27

//カウント系変数の宣言
	int count=0;
	int system_key=0;
	int count_sec=0 ;
	int count_min=0;

//角度系変数の宣言
	float theta = 0;//thetaの宣言
	float theta_min=0;

//時間系変数の宣言
	time_t start_time;
	time_t current_time;
	time_t prev_time=0;

//関数の宣言
	void polarview(void);
	void resetview(void);

//ライトの位置の宣言
	float light_position[] = { 0.0, 1.0, 0.0, 0.0 };

//位置についての変数の宣言
	int mButton;
	float distance,twist,elevation,azimuth;


//シェーディングについて

	//白
	float diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular1[] = { 0.5, 0.5, 0.5, 1.0 };
	float ambient1[] = { 0.2, 0.2, 1.0, 1.0 };
	float shininess1 = 60.0;

	//赤
	float diffuse2[] = { 0.7, 0.1, 0.0, 1.0 };
	float specular2[] = { 0.8, 0.0, 0.0, 1.0 };
	float ambient2[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess2 = 100.0;

	//青
	float diffuse3[] = { 0.0, 0.4, 7.0, 1.0 };
	float specular3[] = { 0, 0, 0, 1.0 };
	float ambient3[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess3 = 128.0;

	//黒
	float diffuse4[] = { 0.0, 0.0, 0.0, 1.0 };
	float specular4[] = { 0, 0, 0, 1.0 };
	float ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
	float shininess4 = 128.0;

void display(void)
{
//はじめ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	polarview();
	glEnable(GL_DEPTH_TEST);/*Z Buffer enable*/
	glEnable(GL_LIGHTING);/*Shading計算の開始*/
	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
	glRotatef(-150.0 ,0.0 ,1.0 ,0.0);//theta角にx軸,y軸,z軸に回転させる
	
//秒針の記述

	//秒針の設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse2);
 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular2);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient2);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess2);
	glNormal3f(0.0,1.0,0.0);

	//秒針の描画
	glPushMatrix();
		glRotatef(-theta ,0.0 ,1.0 ,0.0);//theta角にx軸,y軸,z軸に回転させる
		glBegin(GL_POLYGON);
			glVertex3f( 0.05,0.05,0.0);
			glVertex3f( 0.0,0.05,0.9);
			glVertex3f(-0.05,0.05,0.0);
		glEnd();
	glPopMatrix();

//分針の記述
	//分針の設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse3);
 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular3);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient3);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess3);
	glNormal3f(0.0,1.0,0.0);

	//分針の描画
	glPushMatrix();
		glRotatef(-theta_min ,0.0 ,1.0 ,0.0);//theta角にx軸,y軸,z軸に回転させる
		glBegin(GL_POLYGON);
			glVertex3f( 0.05,0.05,0.0);
			glVertex3f( 0.0,0.05,0.9);
			glVertex3f(-0.05,0.05,0.0);
		glEnd();
	glPopMatrix();

//時計盤の記述

	//時計盤の設定
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse1);
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular1);
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient1);
	glMaterialf( GL_FRONT, GL_SHININESS, shininess1);

	//時計盤の描画
	glBegin(GL_POLYGON);
		glNormal3f(0.0,1.0,0.0);
		const int numSegments = 50; /* 円の分割数 */
		const float radius = 1.0; /* 円の半径 */
		for (int i = 0; i < numSegments; ++i) 
		{
		    float theta_cir = 2.0 * 3.14159 * ((float)i / (float)numSegments);//角度
		    float x = radius * cos(theta_cir); /* x座標の計算 */
		    float z = radius * sin(theta_cir); /* z座標の計算 */
		    glVertex3f(x, 0.0, z); /* 頂点の追加 */
		}
	glEnd();

//目盛りの記述
	//目盛りの設定
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse4);
	 	glMaterialfv( GL_FRONT, GL_SPECULAR, specular4);
		glMaterialfv( GL_FRONT, GL_AMBIENT, ambient4);
		glMaterialf( GL_FRONT, GL_SHININESS, shininess4);
		glNormal3f(0.0,1.0,0.0);
		for(int i=0;i<60;i++)
		{
			glPushMatrix();
				glRotatef(i*6 ,0.0 ,1.0 ,0.0);//6°毎にx軸,y軸,z軸に回転させる
				glBegin(GL_POLYGON);
					glVertex3f( 0.01,0.05,0.9);//左下
					glVertex3f( 0.01,0.05,0.95);//左上
					glVertex3f(-0.01,0.05,0.95);//右上
					glVertex3f(-0.01,0.05,0.9);//右下
				glEnd();
			glPopMatrix();
		}
		for(int i=0;i<12;i++)
		{
			glPushMatrix();
				glRotatef(i*30 ,0.0 ,1.0 ,0.0);//6°毎にx軸,y軸,z軸に回転させる
				glBegin(GL_POLYGON);
					glVertex3f( 0.017,0.05,0.85);//左下
					glVertex3f( 0.017,0.05,0.95);//左上
					glVertex3f(-0.017,0.05,0.95);//右上
					glVertex3f(-0.017,0.05,0.85);//右下
				glEnd();
			glPopMatrix();
		}

	glPopMatrix();

//まとめ
	glDisable(GL_LIGHTING);/*Shading計算終了*/
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

//追加:idle関数
void idle(void)
{
	//system_key=1:ストップウオッチの動作中
	if (system_key == 1) 
	{
	    // ストップウォッチが動作中の処理
	    //現在時刻の取得⇒スペース押された時刻
		time_t current_time=time(NULL);

	    //スタート時間からの差を取得
	    double elapsed_time=difftime(current_time, start_time);

	    //1秒間のタイミングを生成 & 角度の調整
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

//キーボードアクション
void myKbd(unsigned char key, int x, int y)
{
	switch(key)
	{
		//r=リセット
		case 'r':
			system_key=0;
			printf("%2d:%2dでストップウオッチがリセットします。\n",count_min,count_sec);
			count=0;
			count_sec=0;
			count_min=0;
			break;

		//space(32)=スタート、ストップ
		case 32:
			count++;

			//ストップウオッチの停止指示
			if (count%2==0)
			{
				system_key=0;
				printf("%2d:%2dでストップウオッチが停止します。\n",count_min,count_sec);
			}

			//ストップウオッチの動作開始指示
			else
			{
				system_key=1;
			//スタート時刻の設定
				printf("ストップウオッチが動作します。\n");
			}
			break;

		//ESC=画面を閉じる
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
	glEnable(GL_LIGHT0);/*0番のライトを利用可能にする*/
}

//描画の画質設定を変更する関数
void myReshape(int width,int height)
{
	float aspect =(float)width/(float)height;
	
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0,aspect,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
}

//極座標変換する関数
void polarview(void)
{
	glTranslatef(0.0,0.0,-distance);
	glRotatef(-twist,0.0,0.0,1.0);
	glRotatef(-elevation,1.0,0.0,0.0);
	glRotatef(-azimuth,0.0,1.0,0.0);
}

//各パラメータを初期状態に戻す関数
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
	glutIdleFunc(idle);//追加
	glutMainLoop();
	exit(0);
}