#include"iGraphics.h"
void text();
void bulletMethod();
void bubbleMethod();
void lifeMethod();
void High_score_read();
void High_score_Write();
void check_high_score();
void sort_arry();
void draw_input_box();
void start_game();
void menu();
void high_score();
void show_score();
void instruction();
void variable_reinitialization_1();
void variable_reinitialization_2();
void variable_reinitialization_3();
void level();
void bullet_change_and_collision_2();
void level_read();

/////////

int shooterX=180, shooterY=0;
char text_score[20];
char str[100];
char text_high_score[100];
int scr=0;
int end_life= 0;	/// used in lifeMethod() .
int a3[6];
int len = 0;
int l=0, n=0 ,o,r,t;
int active_input;
int page=0;
int life=-30;
int play;


double bulletX[3]={218,218,218};
double bulletY[3]={65,65,65};

int bulletget[3]={1,1,1};
int mode[3]={0,0,0};
int e[3]={0,0,0};
int f[3]={0,0,0};
int s[3]={0,0,0};

int x[3]={1,1,1};
int y[3]={1,1,1};
int z[3]={1,1,1};
int i, j, k;
int p;

int count[5]={1,1,1,1,1};


struct file
{
    char name[25];
    int highscore;
} b,scores[6];


struct bubble
{
	int bubbleX;	////radius of bubble 58.
	int bubbleY;
	int dx;
	int dy;
}	bubble[20]={{50,388,-3,-2},{388,388,2,-3},{200,800,3,-3},{100,1300,0,-3},{300,1800,0,-3}};		



void iDraw()
{
	iClear();
					//iShowBMP(0,0,"gamelevel.bmp");
	start_game();
	menu();
	high_score();
	show_score();
	instruction();
	level();
	
}

void iMouse(int button, int state, int k1, int k2)
{
	if(page==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 115 && k1 <= 364 && k2 >= 180 && k2 <= 212)	/// main manu
			active_input = 1;
	}

	if(page==0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 135 && k1 <= 317 && k2 >= 293 && k2 <= 338)	/// new game
			page = 1;		
		
		else if(k1 >= 127 && k1 <= 325 && k2 >= 230 && k2 <= 275)	/// high score
			page = 2;
		
		else if(k1 >= 133 && k1 <= 317 && k2 >= 166 && k2 <= 212)	/// instruction
			page = 5;
		
		else if(k1 >= 181 && k1 <= 271 && k2 >= 103 && k2 <= 149)	/// level
			page = 6;			
		
		else if(k1 >= 192 && k1 <= 259 && k2 >= 41 && k2 <= 86)		/// exit
			exit(0);
	}


	if(page==5 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)		
	{
		if(k1 >= 8 && k1 <= 144 && k2 >= 28 && k2 <= 70)	/// back from instruction
			page = 0;
	}

	
	if(page==2 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 0 && k1 <= 145 && k2 >= 0 && k2 <= 62)		/// back from high score															
			page = 0;
		else if(k1 >= 182 && k1 <= 270 && k2 >= 280 && k2 <= 330)	/// easy high score
			page =3;
		else if(k1 >= 183 && k1 <= 281 && k2 >= 148 && k2 <= 199)	/// hard high score
			page = 4;
	}

	if(page==3 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 38 && k1 <= 102 && k2 >= 45 && k2 <= 77)		/// back from easy high score
			page = 2;
	}

	if(page==4 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 38 && k1 <= 102 && k2 >= 45 && k2 <= 77)		/// back from hard high score
			page = 2;
	}

	if(page==1 && l!=1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 140 && k1 <= 264 && k2 >= 275 && k2 <= 307)		/// for try again. when game over
			variable_reinitialization_1();
		
		else if(k1 >= 132 && k1 <= 272 && k2 >= 229 && k2 <= 261)		/// back main menu. when game over 
			variable_reinitialization_2();
	}

	if(page==6 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 0 && k1 <= 145 && k2 >= 0 && k2 <= 62)		/// back from level
			page = 0;

		else if(k1 >= 182 && k1 <= 270 && k2 >= 217 && k2 <= 268)	//// for easy level
		{
			play = 1;
			life = 2;
			
			FILE *nakib;
			nakib = fopen("Level.txt","w");
			fprintf(nakib,"%d %d",play,life);
			fclose(nakib);
		}
		
		else if(k1 >= 183 && k1 <= 281 && k2 >= 148 && k2 <= 199)	//// for hard level
		{
			play = 2;
			life = 3;

			FILE *nakib;
			nakib = fopen("Level.txt","w");
			fprintf(nakib,"%d %d",play,life);
			fclose(nakib);
		}

	}
}

void variable_reinitialization_1()	/// if retry
{	
	if(play == 1)
		life = 2;
	else
		life = 3;
	
	l = 0;
	scr = 0;	
	end_life = 0;
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = 0;
	bubble[0].bubbleY = 388;
	bubble[1].bubbleX = 388;
	bubble[1].bubbleY = 388;
	bubble[2].bubbleX = 200;
	bubble[2].bubbleY = 800;
	bubble[3].bubbleX = 100;
	bubble[3].bubbleY = 1300;
	bubble[4].bubbleX = 300;
	bubble[4].bubbleY = 1800;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=218;
	bulletX[1]=218;
	bulletX[2]=218;
	bulletY[0]=65;
	bulletY[1]=65;
	bulletY[2]=65;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	e[0]=0;
	e[1]=0;
	e[2]=0;
	f[0]=0;
	f[1]=0;
	f[2]=0;
	s[0]=0;
	s[1]=0;
	s[2]=0;
}

void variable_reinitialization_2()
{	
	page = 0;
	
	if(play == 1)
		life = 2;
	else
		life = 3;
	
	l = 0;
	scr = 0;
	end_life = 0;
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = 0;
	bubble[0].bubbleY = 388;
	bubble[1].bubbleX = 388;
	bubble[1].bubbleY = 388;
	bubble[2].bubbleX = 200;
	bubble[2].bubbleY = 800;
	bubble[3].bubbleX = 100;
	bubble[3].bubbleY = 1300;
	bubble[4].bubbleX = 300;
	bubble[4].bubbleY = 1800;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=218;
	bulletX[1]=218;
	bulletX[2]=218;
	bulletY[0]=65;
	bulletY[1]=65;
	bulletY[2]=65;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	e[0]=0;
	e[1]=0;
	e[2]=0;
	f[0]=0;
	f[1]=0;
	f[2]=0;
	s[0]=0;
	s[1]=0;
	s[2]=0;
}

void variable_reinitialization_3()		/// if high score occure
{
	page = 0;

	if(play == 1)
		life = 2;
	else
		life = 3;
	
	l = 0;
	scr = 0;	
	end_life = 0;
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = 0;
	bubble[0].bubbleY = 388;
	bubble[1].bubbleX = 388;
	bubble[1].bubbleY = 388;
	bubble[2].bubbleX = 200;
	bubble[2].bubbleY = 800;
	bubble[3].bubbleX = 100;
	bubble[3].bubbleY = 1300;
	bubble[4].bubbleX = 300;
	bubble[4].bubbleY = 1800;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=218;
	bulletX[1]=218;
	bulletX[2]=218;
	bulletY[0]=65;
	bulletY[1]=65;
	bulletY[2]=65;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	e[0]=0;
	e[1]=0;
	e[2]=0;
	f[0]=0;
	f[1]=0;
	f[2]=0;
	s[0]=0;
	s[1]=0;
	s[2]=0;
}

void menu()
{
	if(page == 0)
	{
		iShowBMP(0,0,"menu.bmp");
	}
}

void start_game()
{
	if(page == 1)
	{
		level_read();
		bubbleMethod();
		bulletMethod();	
		lifeMethod();
		draw_input_box();
		text();
					//iLine(200,200,264,200);
					//iLine(200,300,258,300);
					//iLine(218,70,218,59);
		iLine(0,65,450,65);
		iShowBMP(shooterX,shooterY,"shooter.bmp");
		iShowBMP(418,45,"life.bmp");
	}
}

void show_score()
{
	int i, j=311 ;
	
	if(page == 3)
	{
		iShowBMP(38,45,"back.bmp");

		iSetColor(255,0,0);
		iText(176,397,"High Score",GLUT_BITMAP_HELVETICA_18);

		High_score_read();

		for(i=0;i<=4;i++)
		{
			sprintf(text_high_score,"%s", scores[i].name);
			iSetColor(0,255,0);
			iText(135,j,text_high_score,GLUT_BITMAP_HELVETICA_18);
			j -= 35;
		}

		j=311;
		for(i=0;i<=4;i++)
		{
			sprintf(text_high_score,"%d", scores[i].highscore);
			iSetColor(0,255,0);
			iText(281,j,text_high_score,GLUT_BITMAP_HELVETICA_18);
			j -= 35;
		}		
	}

	else if(page == 4)
	{
		iShowBMP(38,45,"back.bmp");

		iSetColor(255,0,0);
		iText(176,397,"High Score",GLUT_BITMAP_HELVETICA_18);

		High_score_read();

		for(i=0;i<=4;i++)
		{
			sprintf(text_high_score,"%s", scores[i].name);
			iSetColor(0,255,0);
			iText(135,j,text_high_score,GLUT_BITMAP_HELVETICA_18);
			j -= 35;
		}

		j=311;
		for(i=0;i<=4;i++)
		{
			sprintf(text_high_score,"%d", scores[i].highscore);
			iSetColor(0,255,0);
			iText(281,j,text_high_score,GLUT_BITMAP_HELVETICA_18);
			j -= 35;
		}		
	}
}

void high_score()
{
	if(page == 2)
	{
		iShowBMP(182,280,"easy.bmp");
		iShowBMP(183,148,"hard.bmp");
		iShowBMP(0,0,"level_back.bmp");
	}
}

void instruction()
{
	if(page == 5)
	iShowBMP(0,0,"instruction.bmp");
}

void level()
{
	if(page == 6)
	{
		iShowBMP(112,398,"gamelevel.bmp");
		iShowBMP(182,217,"easy.bmp");
		iShowBMP(183,148,"hard.bmp");
		iShowBMP(0,0,"level_back.bmp");
		
		FILE *fp;
		fp = fopen("Level.txt", "r");
		fscanf(fp," %d", &play);
		fclose(fp);
		
		iSetColor(255,0,0);
		if(play == 1)
			iText(300,238,"ON",GLUT_BITMAP_HELVETICA_18);
		else if(play ==2)
			iText(309,164,"ON",GLUT_BITMAP_HELVETICA_18);
	}
}

void level_read()
{
	int a,i=0;
	FILE *fp;

	fp = fopen("Level.txt", "r");
	fscanf(fp," %d  %d", &play,&a);
	fclose(fp);

	if(life == -30)
		life = a;
}



void bubbleMethod()
{
	iShowBMP(bubble[0].bubbleX, bubble[0].bubbleY, "Bubble.bmp");
	iShowBMP(bubble[1].bubbleX, bubble[1].bubbleY, "Bubble.bmp");
	iShowBMP(bubble[2].bubbleX, bubble[2].bubbleY, "Bubble.bmp");
	iShowBMP(bubble[3].bubbleX, bubble[3].bubbleY, "Bubble.bmp");
	iShowBMP(bubble[4].bubbleX, bubble[4].bubbleY, "Bubble.bmp");
}

void bulletMethod()
{
	iSetColor(138,69,0);
	iPoint ( bulletX[0],bulletY[0],2);
	iPoint ( bulletX[1],bulletY[1],2);
	iPoint ( bulletX[2],bulletY[2],2);
}

void lifeMethod()
{
	if(life == 0)
	{
		iPauseTimer(0);
		iPauseTimer(1);
		iPauseTimer(2);
		end_life = 1;	/// when game over then end_life = 1 . that's why shooter can not be moven by user.
		shooterX = 180;
	}

	if(life == 0 && l == 0)
	{
		iSetColor(0,255,0);
		iText(155,380,"GAME OVER",GLUT_BITMAP_HELVETICA_18);
		sprintf(text_score,"Your Score is %d",scr);
		iText(142,330,text_score,GLUT_BITMAP_HELVETICA_18);
		iShowBMP(140,275,"try_again.bmp");
		iShowBMP(132,229,"back_main_manu.bmp");
		
	}
}



void High_score_read()
{
	if((life == 0 && play == 1) || page == 3)
	{
		FILE *fp;
		int i;
		char a1[100],a2[100];
		
		fp = fopen("easy_score.txt", "r");    
		if(fp == NULL)
		{
			printf("Error in opening file\n");
			printf("The value of fp = %d\n",fp);
		}		
		
		else
		{               
			for(i=0;i<5;i++)
			{
				fscanf(fp,"%s %s",a1,a2 );
				strcpy(scores[i].name, a1);		
				scores[i].highscore = atoi(a2);
				a3[i]= scores[i].highscore;
						//printf("%s \t %d  %d\n",scores[i].name,scores[i].highscore,a3[i]);		
			}
		}
	fclose(fp);
	
	a3[5] = scr;
	check_high_score(); 	
	}

	
	else if((life == 0 && play == 2) || page == 4)
	{
		FILE *fp;
		int i;
		char a1[100],a2[100];
		
		fp = fopen("hard_score.txt", "r");    
		if(fp == NULL)
		{
			printf("Error in opening file\n");
			printf("The value of fp = %d\n",fp);
		}
		
		else
		{               
			for(i=0;i<5;i++)
			{
				fscanf(fp,"%s %s",a1,a2 );
				strcpy(scores[i].name, a1);		
				scores[i].highscore = atoi(a2);
				a3[i]= scores[i].highscore;
						//printf("%s \t %d  %d\n",scores[i].name,scores[i].highscore,a3[i]);		
			}
		}
	fclose(fp);
	
	a3[5] = scr;
	check_high_score(); 	
	}
}

void check_high_score()
{
	int i,j,k;
	for(i=5;i>0;i--)
        for(j=0;j<i;j++)
        {
            if(a3[j]<a3[j+1])
            {
                k = a3[j];
                a3[j]=a3[j+1];
                a3[j+1] = k;
            }
        }

	if(a3[5] != scr)
	l=1;
}

void sort_arry()
{
	int i,j;
	for(i=5;i>0;i--)
            for(j=0;j<i;j++)
            {
				if(scores[j].highscore < scores[j+1].highscore)
                {
                    b = scores[j];
                    scores[j]=scores[j+1];
                    scores[j+1] = b;
                }
            }
}

void High_score_Write()
{
	int i;
	sort_arry();
	
	if(play == 1)
	{
		FILE *fp;
		fp = fopen("easy_score.txt", "w");
		for(i=0;i<5;i++)
				fprintf(fp,"%s \t\t\t %d \n", scores[i].name, scores[i].highscore );
		fclose(fp);
	}

	else if(play == 2)
	{
		FILE *fp;
		fp = fopen("hard_score.txt", "w");
		for(i=0;i<5;i++)
				fprintf(fp,"%s \t\t\t %d \n", scores[i].name, scores[i].highscore );
		fclose(fp);
	}
}

void draw_input_box()
{
	if(l==1)
	{	
		if(active_input == 1)
		{
			iSetColor(0, 255, 0);
			iRectangle(115, 180, 250, 30);
		}
		else
		{
			iSetColor(150, 150, 150);
			iRectangle(115, 180, 250, 30);
		}

		iSetColor(0, 255, 0);
		iText(180, 190, str,GLUT_BITMAP_HELVETICA_18);
	}
}

void text()
{	
	iSetColor(0,255,0);
	sprintf(text_score,"Score: %d",scr);
	iText(5,30,text_score,GLUT_BITMAP_HELVETICA_18);

	iSetColor(0,255,0);
	char aa1[100];
	sprintf(aa1,"%d",life);
	iText(430,20,aa1,GLUT_BITMAP_HELVETICA_18);
	
	if(l==1)
	{
		iSetColor(255,0,0);
		iText(172,360,"GAME OVER",GLUT_BITMAP_HELVETICA_18);
		iSetColor(0,255,0);
		iText(125,305,"wow!!!  A new high score",GLUT_BITMAP_HELVETICA_18);
		iText(140,265,"So, click in the rectangle.", GLUT_BITMAP_HELVETICA_18);
		iText(152,245,"And enter your name.", GLUT_BITMAP_HELVETICA_18);
	}
}



void iKeyboard(unsigned char mx)
{
	if(mx == 'e' || mx == 'E')
	{
		mode[0] = 1;
		e[0] = 1;
	}

	else if(mx == 'f' || mx == 'F')
	{
		mode[0] = 1;
		f[0] = 1;
	}

	else if(mx == 's' || mx == 'S')
	{
		mode[0] = 1;
		s[0] = 1;
	}

///////

	if( bulletget[0] == 0 && (mx == 'e' || mx == 'E'))
	{
		mode[1] = 1;
		e[1] = 1;
	}
		
	else if( bulletget[0] == 0 && (mx == 'f' || mx == 'F'))
	{
		mode[1] = 1;
		f[1] = 1;
	}

	else if( bulletget[0] == 0  && (mx == 's' || mx == 'S'))
	{
		mode[1] = 1;
		s[1] = 1;
	}

//////
	if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 'e' || mx == 'E') )
	{
		mode[2] = 1;
		e[2] = 1;
	}
	
	else if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 's' || mx == 'S') )
	{
		mode[2] = 1;
		s[2] = 1;
	}

	else if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 'f' || mx == 'F') )
	{
		mode[2] = 1;
		f[2] = 1;
	}


	if(l==1 && active_input == 1 )
	{
		if(mx == '\r')
			{
				strcpy(scores[5].name, str);
				scores[5].highscore = scr;
				active_input = 0;

				for(n = 0; n < len; n++)
					str[n] = 0;
				len = 0;				
				iSetColor(255, 0, 0);
				High_score_Write();
				variable_reinitialization_3();
			}
			else
			{
				str[len] = mx;
				len++;
			}
	}
}

void iSpecialKeyboard(unsigned char  a)
{
	if(a == GLUT_KEY_LEFT && shooterX >0 && end_life==0)
	{
		shooterX -= 10;
		if(bulletget[0] == 1)	bulletX[0] -=10;
		if(bulletget[1] == 1)	bulletX[1] -=10;
		if(bulletget[2] == 1)	bulletX[2] -=10;
	}
	
	if(a == GLUT_KEY_RIGHT && shooterX <360 && end_life==0)
	{
		shooterX += 10;
		if(bulletget[0] == 1)	bulletX[0] +=10;
		if(bulletget[1] == 1)	bulletX[1] +=10;
		if(bulletget[2] == 1)	bulletX[2] +=10;
	}

}

void bubble_change()
{
	if(page == 1)
	{
	for(p=0;p<=4;p++)
	{
		bubble[p].bubbleX += bubble[p].dx;
		bubble[p].bubbleY += bubble[p].dy;	
		if(bubble[p].bubbleX < 0 || bubble[p].bubbleX > 388)
			bubble[p].dx = -bubble[p].dx;
		if(bubble[p].bubbleY < 63 )		//63
		{
			bubble[p].bubbleX = 5 + rand() % 380;
			bubble[p].bubbleY = 450;
			life -=1;
			count[p] = 1;
		}
	}

	High_score_read();

	}
}

bool detect_collision_1(int j)
{
	return (bulletX[i] > ( bubble[j].bubbleX + 4)) && (bulletX[i] < (bubble[j].bubbleX +64-1)) &&  (bulletY[i] > (bubble[j].bubbleY + 2)) && (bulletY[i] < bubble[j].bubbleY +64-2);
}

void bullet_change_and_collision_1()
{

	if(page == 1 && play == 1)
	{
			
		iPauseTimer(1);

		for(i=0;i<=2;i++)
		{
	
			if(mode[i] == 1)
			{
				if(e[i]==1 && x[i]==1 && y[i]==1)
				{
					bulletget[i] = 0;
					bulletY[i] += 5;
				}

				else if (s[i]== 1 && z[i]==1)
				{
					x[i] = 0;
					bulletget[i] = 0;
					bulletX[i] -= 4;
					bulletY[i] += 3;
				}

				else if ( f[i]== 1 )
				{
					y[i] = 0;
					z[i]=0;
					bulletget[i] = 0;
					bulletX[i] += 4;
					bulletY[i] += 3;
				}
		
				for(j=0;j<=4;j++)
				{
					if(detect_collision_1(j))
					{
						scr += 5;
						bulletget[i] = 1;
						mode[i] = 0;
						e[i]=0;
						f[i]=0;
						s[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletX[i] = shooterX + 36;
						bulletY[i] = 65;
						bubble[j].bubbleX = rand() % 388;
						bubble[j].bubbleY = 450;	//388
					}
		
					else if(bulletX[i] > 452 || bulletX[i]<0 || bulletY[i] > 450)
					{
						mode[i] = 0;
						e[i]=0;
						f[i]=0;
						s[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletget[i] = 1;
						bulletX[i] = shooterX + 38;
						bulletY[i] = 65;
					}
				}	
			}
		}
	}
}

void method()
{
	for(i=0;i<=2;i++)
		{
	
			if(mode[i] == 1)
			{
				if(e[i]==1 && x[i]==1 && y[i]==1)
				{
					bulletget[i] = 0;
					bulletY[i] += 5;
				}

				else if (s[i]== 1 && z[i]==1)
				{
					x[i] = 0;
					bulletget[i] = 0;
					bulletX[i] -= 4;
					bulletY[i] += 3;
				}

				else if ( f[i]== 1 )
				{
					y[i] = 0;
					z[i]=0;
					bulletget[i] = 0;
					bulletX[i] += 4;
					bulletY[i] += 3;
				}
		
				for(j=0;j<=4;j++)
				{
					if(detect_collision_1(j))
					{
						count[j] += 2;
						bulletget[i] = 1;
						mode[i] = 0;
						e[i]=0;
						f[i]=0;
						s[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletX[i] = shooterX + 36;
						bulletY[i] = 65;
						
						if(count[j] == 7)
						{
							count[j] = 1;
							scr += 5;
							bubble[j].bubbleX = rand() % 388;
							bubble[j].bubbleY = 450;	//388
						}
					}
		
					else if(bulletX[i] > 452 || bulletX[i]<0 || bulletY[i] > 450)
					{
						mode[i] = 0;
						e[i]=0;
						f[i]=0;
						s[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletget[i] = 1;
						bulletX[i] = shooterX + 38;
						bulletY[i] = 65;
					}
				}	
			}
		}
}

void bullet_change_and_collision_2()
{

	if(page == 1 && play ==2)
	{
	
		iPauseTimer(0);

		method();
		method();
		method();
		method();
	}
}

void main()
{
	    
	iSetTimer(10,bullet_change_and_collision_1);
	iSetTimer(5,bullet_change_and_collision_2);
	iSetTimer(35,bubble_change);	
	iInitialize(452,450,"Baby Bubble Shooter");
}


void iMouseMove(int k3, int k4 ){}
void iPassiveMouseMove(int k5, int k6){}
