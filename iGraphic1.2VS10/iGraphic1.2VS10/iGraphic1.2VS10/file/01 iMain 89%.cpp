// for timer/couter --> int my_time, update_time(),  iSetTimer(1000, update_time), iResumeTimer(3), iPauseTimer(3) 

#include"iGraphics.h"
void show_score_and_life_in_text();
void bulletMethod();
void bubbleMethod();
void lifeMethod();
void High_score_read();
void High_score_Write();
void check_high_score();
void sort_arry();

void start_game();
void menu();
void high_score();
void show_score();
void instruction();
void about_us();
void game_over();
void game_over_and_high_score();
void variable_reinitialization_1();
void variable_reinitialization_2();
void variable_reinitialization_3();

void bubble_change();
bool detect_collision_1(int j);
void bullet_change_and_collision_1();
void bullet_change_and_collision_2();
void method();
void level();
void level_read();
void update_time();

/////////

int shooterX=640, shooterY=20;
char text_score[20], text_score_value[20], text_life[20], text_life_value[20], aa1[20];
char str[100];
char text_high_score[100];
int scr=0;
int end_life= 0;	/// used in lifeMethod() .
int a3[6];
int len = 0;
int highScoreFound = 0, n = 0 ,o,r,t;
int page = 0;
int life=-30;
int play;
int pause = 0;
int my_time = 0, time_minute;
float time_second;
char text_time[10], text_time_value[30];

double bulletX[3]={685.5,685.5,685.5};
double bulletY[3]={80,80,80};

int bulletget[3]={1,1,1};
int mode[3]={0,0,0};
int w[3]={0,0,0};
int a[3]={0,0,0};
int d[3]={0,0,0};

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
}	bubble[20]={{(245+rand() % 820),212,-3.5,-3},{(245+rand() % 820),712,4,-2.5},{(245+rand() % 820),1050,3,-3},
																		{(245+rand() % 820),1550,-3,-4},{(245+rand() % 820),1800,-4,-3.5}};		



void iDraw()
{
	iClear();	
	start_game();
	menu();
	high_score();
	show_score();
	instruction();
	about_us();
	level();	
	game_over();
	game_over_and_high_score();
}

void bubble_change()
{
	if(page == 1)
	{
		for(p=0;p<=4;p++)
		{
			bubble[p].bubbleX += bubble[p].dx;
			bubble[p].bubbleY += bubble[p].dy;	
			if(bubble[p].bubbleX < 240 || bubble[p].bubbleX > 1068)
				bubble[p].dx = -bubble[p].dx;
			if(bubble[p].bubbleY < 84 )	
			{
				bubble[p].bubbleX =(245+rand() % 820);
				bubble[p].bubbleY = 712;
				life -=1;
				count[p] = 1;
			}
		}

		High_score_read();

	}
}

void lifeMethod()
{
	if(life <= 0)
	{		
		iPauseTimer(0);
		iPauseTimer(1);		
		iPauseTimer(2);
		end_life = 1;	/// when game over(or pause) then end_life = 1 . that's why shooter can not be moven by user.

		iPauseTimer(3); // for pause the time counter ( iSetTimer(1000, update_time) )		

		/*for (int temp =0; temp <= 1000; temp++)
			printf("wait a moment\n");*/
	}

	if(life <= 0 && highScoreFound == 0)
	{		
		page = 7;	
	}

	if(life <= 0 && highScoreFound == 1)
	{
		page = 8;
	}
	
}

void game_over()
{
	if(page == 7){

		//for (int temp =0; temp <= 1000; temp++)
		//	printf("wait a moment\n");

		iShowBMP(233,0,"image/game_over_p7.bmp");

		iSetColor(255,255,255);
		sprintf(text_score,"%d",scr);
		iText(775,488,text_score,GLUT_BITMAP_HELVETICA_18);
				
		if(my_time < 60){		
			sprintf(text_time_value,"%d s",my_time);
			iText(795,430,text_time_value,GLUT_BITMAP_HELVETICA_18);
		}
		else{		
			sprintf(text_time_value,"%d m %.0f s",time_minute, time_second);
			iText(795,430,text_time_value,GLUT_BITMAP_HELVETICA_18);
		}
	}
}

void start_game()
{
	if(page == 1)
	{
		level_read();
		bubbleMethod();  // just show the all bubble using iShowBMP()
		bulletMethod();	 // just show the all bullet using iShowBMP()
		lifeMethod();		
		show_score_and_life_in_text();
	
		iShowBMP(shooterX,shooterY,"image/object/shooter.bmp");

	// side line of play or start game
		iSetColor(168,38,147);
		//iFilledRectangle(232,0,3,712);
		iFilledRectangle(1132,0,3,712);

		iSetColor(255,255,255);
		//iLine(236,0,236,712);
		//iLine(1136,0,1136,712);

		iSetColor(168,38,147);
		iFilledRectangle(236,0,3,712);
		//iFilledRectangle(1136,0,3,712);

	// side line of play or start game
		iSetColor(168,38,147);
		iLine(239,85,1133,85);	
	}
}



void iMouse(int button, int state, int k1, int k2)
{	
	if(page==0 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if(k1 >= 548 && k1 <= 815 && k2 >= 479 && k2 <= 539)	/// go to play page
		{
			page = 1;
			my_time = 0;
			iResumeTimer(3);
		}
	
		else if(k1 >= 548 && k1 <= 815 && k2 >= 316 && k2 <= 376)	/// go to (score/high score) page
			page = 2;
		
		else if(k1 >= 548 && k1 <= 815 && k2 >= 234 && k2 <= 294)	/// go to instruction page
			page = 5;
		
		else if(k1 >= 548 && k1 <= 815 && k2 >= 396 && k2 <= 456)	/// go to (setting/level) page
			page = 6;

		else if(k1 >= 548 && k1 <= 815 && k2 >= 150 && k2 <= 210)	/// go to about us page
			page = 9;
		
		else if(k1 >= 548 && k1 <= 815 && k2 >= 68 && k2 <= 128)		/// exit from the game
			exit(0);
	}

	if(page==5 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)		
	{
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)	/// back from instruction
			page = 0;
	}

	if(page==9 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)		
	{
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)	/// back from about us
			page = 0;
	}
	
	if(page==2 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)		/// back from high score															
			page = 0;		
		else if(k1 >= 570 && k1 <= 800 && k2 >= 430 && k2 <= 488)	/// go to easy high score
			page = 3;
		else if(k1 >= 570 && k1 <= 800 && k2 >= 330 && k2 <= 388)	/// go to hard high score
			page = 4;
	}

	if(page==3 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{		
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)		/// back from easy high score
			page = 2;
	}

	if(page==4 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)		/// back from hard high score
			page = 2;
	}

	if(page==6 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(k1 >= 342 && k1 <= 534 && k2 >= 94 && k2 <= 154)		/// back from (settings/level)
			page = 0;

		//
		else if(k1 >= 564 && k1 <= 804 && k2 >= 430 && k2 <= 490)	//// for easy level
		{
			play = 1;
			life = 1;
			
			FILE *nakib;
			nakib = fopen("Level.txt","w");
			fprintf(nakib,"%d %d",play,life);
			fclose(nakib);
		}
		
		else if(k1 >= 564 && k1 <= 804 && k2 >= 330 && k2 <= 388)	//// for hard level
		{
			play = 2;
			life = 3;

			FILE *nakib;
			nakib = fopen("Level.txt","w");
			fprintf(nakib,"%d %d",play,life);
			fclose(nakib);
		}
	}

	//when game is running
	if(page==1 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{				
		if(k1 >= 1000 && k1 <= 1080 && k2 >= 665 && k2 <= 700)		/// back to the main menu (when game is running)
			variable_reinitialization_2();

		else if(k1 >= 865 && k1 <= 945 && k2 >= 665 && k2 <= 700)		/// for restart the game (when game is running)
			variable_reinitialization_1();

		else if(k1 >= 730 && k1 <= 810 && k2 >= 665 && k2 <= 700 && pause == 0)		/// for pause the game (when game is running)
		{
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			pause = 1;
			end_life = 1;   /// when game over(or pause) then end_life = 1 . that's why shooter can not be moven by user.
			iPauseTimer(3);
		}
		else if(k1 >= 730 && k1 <= 810 && k2 >= 665 && k2 <= 700 && pause == 1)		/// for resume the game (when game is running)
		{
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
			pause = 0;
			end_life = 0;  /// when game over(or pause) then end_life = 1 . that's why shooter can not be moven by user.
			iResumeTimer(3);
		}
	}

	//when game is over
	if(page==7 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{				
		if(k1 >= 548 && k1 <= 811 && k2 >= 186 && k2 <= 248)		/// back to the main menu (when game is running)
			variable_reinitialization_2();

		else if(k1 >= 548 && k1 <= 811 && k2 >= 280 && k2 <= 342)		/// for restart the game (when game is running)
			variable_reinitialization_1();
	}

	// when game over and highScore is occur
	if(page==8 && button == GLUT_RIGHT_BUTTON && state == GLUT_UP)  /// when click the enter button ( to insert the name of the highScorer )
	{
		if(k1 >= 548 && k1 <= 812 && k2 >= 135 && k2 <= 195)	
		{
			if(len != 0)
			{
				strcpy(scores[5].name, str);
				scores[5].highscore = scr;			

				for(n = 0; n < len; n++)
					str[n] = 0;
				len = 0;				
				iSetColor(255, 0, 0);
				High_score_Write();
				variable_reinitialization_3();
			}	
		}
	}
}

void update_time()
{
	my_time++;
}

void level_read()
{
	int temp,i=0;
	FILE *fp;

	fp = fopen("Level.txt", "r");
	fscanf(fp," %d  %d", &play,&temp);   // read the value of a from the level.txt file
	fclose(fp);

	if(life == -30)		// initial declared value of life=-30
		life = temp;
}

void bubbleMethod()
{
	iShowBMP(bubble[0].bubbleX, bubble[0].bubbleY, "image/object/bubble.bmp");
	iShowBMP(bubble[1].bubbleX, bubble[1].bubbleY, "image/object/bubble.bmp");
	iShowBMP(bubble[2].bubbleX, bubble[2].bubbleY, "image/object/bubble.bmp");
	iShowBMP(bubble[3].bubbleX, bubble[3].bubbleY, "image/object/bubble.bmp");
	iShowBMP(bubble[4].bubbleX, bubble[4].bubbleY, "image/object/bubble.bmp");
}

void bulletMethod()
{
	iSetColor(168,38,147);
	iFilledCircle(bulletX[0],bulletY[0],3);
	iFilledCircle(bulletX[1],bulletY[1],3);
	iFilledCircle(bulletX[2],bulletY[2],3);
}



void variable_reinitialization_1()	// for try again. when game is running or over
{	
	page = 1;

	FILE *fp;
	fp = fopen("Level.txt", "r");
	fscanf(fp," %d  %d", &play,&life);
	fclose(fp);
	
	highScoreFound = 0;
	scr = 0;	
	end_life = 0;

	pause = 0;
	my_time = 0;  // for reset the time counter
	iResumeTimer(3);

	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	shooterX = 640;

	bubble[0].bubbleX = (245+rand() % 820);
	bubble[0].bubbleY = 212;
	bubble[1].bubbleX = (245+rand() % 820);
	bubble[1].bubbleY = 712;
	bubble[2].bubbleX = (245+rand() % 820);
	bubble[2].bubbleY = 1050;
	bubble[3].bubbleX = (245+rand() % 820);
	bubble[3].bubbleY = 1550;
	bubble[4].bubbleX = (245+rand() % 820);
	bubble[4].bubbleY = 1800;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=685.5;
	bulletX[1]=685.5;
	bulletX[2]=685.5;
	bulletY[0]=80;
	bulletY[1]=80;
	bulletY[2]=80;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	w[0]=0;
	w[1]=0;
	w[2]=0;
	a[0]=0;
	a[1]=0;
	a[2]=0;
	d[0]=0;
	d[1]=0;
	d[2]=0;	
}

void variable_reinitialization_2()  // back main menu. when game is running or over
{	
	page = 0;

	FILE *fp;
	fp = fopen("Level.txt", "r");
	fscanf(fp," %d  %d", &play,&life);
	fclose(fp);
	
	highScoreFound = 0;
	scr = 0;
	end_life = 0;	

	pause = 0;
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = (245+rand() % 820);
	bubble[0].bubbleY = 212;
	bubble[1].bubbleX = (245+rand() % 820);
	bubble[1].bubbleY = 712;
	bubble[2].bubbleX = (245+rand() % 820);
	bubble[2].bubbleY = 1050;
	bubble[3].bubbleX = (245+rand() % 820);
	bubble[3].bubbleY = 1550;
	bubble[4].bubbleX = (245+rand() % 820);
	bubble[4].bubbleY = 1800;

	shooterX = 640;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=685.5;
	bulletX[1]=685.5;
	bulletX[2]=685.5;
	bulletY[0]=80;
	bulletY[1]=80;
	bulletY[2]=80;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	w[0]=0;
	w[1]=0;
	w[2]=0;
	a[0]=0;
	a[1]=0;
	a[2]=0;
	d[0]=0;
	d[1]=0;
	d[2]=0;
}

void variable_reinitialization_3()		/// if high score occure
{
	page = 0;

	FILE *fp;
	fp = fopen("Level.txt", "r");
	fscanf(fp," %d  %d", &play,&life);
	fclose(fp);
	
	highScoreFound = 0;
	scr = 0;	
	end_life = 0;
	pause = 0;
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = (245+rand() % 820);
	bubble[0].bubbleY = 712;
	bubble[1].bubbleX = (245+rand() % 820);
	bubble[1].bubbleY = 712;
	bubble[2].bubbleX = (245+rand() % 820);
	bubble[2].bubbleY = 1050;
	bubble[3].bubbleX = (245+rand() % 820);
	bubble[3].bubbleY = 1550;
	bubble[4].bubbleX = (245+rand() % 820);
	bubble[4].bubbleY = 1800;

	shooterX = 640;

	bulletget[0] = 1;
	bulletget[1] = 1;
	bulletget[2] = 1;

	bulletX[0]=685.5;
	bulletX[1]=685.5;
	bulletX[2]=685.5;
	bulletY[0]=80;
	bulletY[1]=80;
	bulletY[2]=80;
	count[0]=1;
	count[1]=1;
	count[2]=1;
	count[3]=1;
	count[4]=1;
	w[0]=0;
	w[1]=0;
	w[2]=0;
	a[0]=0;
	a[1]=0;
	a[2]=0;
	d[0]=0;
	d[1]=0;
	d[2]=0;
}

void menu()
{
	if(page == 0)
	{
		iShowBMP(233,0,"image/home_page.bmp");
	}
}


void show_score()
{
	int i, j=311, temp=1;
	
	if(page == 3)	// show easy high scores
	{
		High_score_read();
		iShowBMP(233,0,"image/show_high_score_page.bmp");

		iSetColor(168,38,147);
		iRectangle(552,250, 258, 232);		
		iRectangle(551,249, 260, 234);		
		iRectangle(550,248, 262, 236);		
		iRectangle(549,247, 264, 238);		
		iRectangle(548,246, 266, 240);		
		
		iSetColor(255,255,255);
		iRectangle(547,245, 268, 242);
		iRectangle(546,244, 270, 244);

		iSetColor(168,38,147);
		iRectangle(545,243, 272, 246);
		iRectangle(544,242, 274, 248);
		iRectangle(543,241, 276, 250);
		iRectangle(542,240, 278, 252);
		iRectangle(541,239, 280, 254);
		

		iLine(552,434,810,434);
		iLine(552,390,810,390);
		iLine(552,343,810,343);
		iLine(552,298,810,298);

		iLine(552,435,810,435);
		iLine(552,391,810,391);
		iLine(552,344,810,344);
		iLine(552,299,810,299);
		
		iSetColor(255,255,255);
		j=450;

		for(i=0;i<=4;i++)	// show sequence number
		{
			sprintf(text_high_score,"%d.", temp++);			
			iText(565,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}
		
		j=450;
		for(i=0;i<=4;i++)	// show easy high score's holder name
		{
			sprintf(text_high_score,"%s", scores[i].name);			
			iText(595,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}

		j=450;
		for(i=0;i<=4;i++)	// show easy high scores
		{
			sprintf(text_high_score,"%d", scores[i].highscore);			
			iText(751,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}				
	}

	else if(page == 4)	// show hard high scores
	{
		High_score_read();
		iShowBMP(233,0,"image/show_high_score_page.bmp");

		iSetColor(168,38,147);
		iRectangle(552,250, 258, 232);		
		iRectangle(551,249, 260, 234);		
		iRectangle(550,248, 262, 236);		
		iRectangle(549,247, 264, 238);		
		iRectangle(548,246, 266, 240);		
		
		iSetColor(255,255,255);
		iRectangle(547,245, 268, 242);
		iRectangle(546,244, 270, 244);

		iSetColor(168,38,147);
		iRectangle(545,243, 272, 246);
		iRectangle(544,242, 274, 248);
		iRectangle(543,241, 276, 250);
		iRectangle(542,240, 278, 252);
		iRectangle(541,239, 280, 254);
		

		iLine(552,434,810,434);
		iLine(552,390,810,390);
		iLine(552,343,810,343);
		iLine(552,298,810,298);

		iLine(552,435,810,435);
		iLine(552,391,810,391);
		iLine(552,344,810,344);
		iLine(552,299,810,299);
		
		iSetColor(255,255,255);
		j=450;

		for(i=0;i<=4;i++)	// show sequence number
		{
			sprintf(text_high_score,"%d.", temp++);			
			iText(565,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}
		
		j=450;
		for(i=0;i<=4;i++)	// show hard high score's holder name
		{
			sprintf(text_high_score,"%s", scores[i].name);			
			iText(595,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}

		j=450;
		for(i=0;i<=4;i++)	// show easy hard scores
		{
			sprintf(text_high_score,"%d", scores[i].highscore);			
			iText(751,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}				
	}
}

void high_score()
{
	if(page == 2)
	{
		iShowBMP(233,0,"image/score_page.bmp");
	}
}

void instruction()
{
	if(page == 5){
		iShowBMP(233,0,"image/instruction_page.bmp");		
	}
}

void about_us()
{
	if(page == 9){		
		iShowBMP(233,0,"image/about_us_p9.bmp");
	}
}

void game_over_and_high_score()
{
	if(page == 8){
		iShowBMP(233,0,"image/high_score_p8.bmp");

		iSetColor(255,255,255);
		sprintf(text_score,"%d",scr);
		iText(772,411,text_score,GLUT_BITMAP_HELVETICA_18);

		if(my_time < 60){		
			sprintf(text_time_value,"%d s",my_time);
			iText(792,368,text_time_value,GLUT_BITMAP_HELVETICA_18);
		}
		else{		
			sprintf(text_time_value,"%d m %.0f s",time_minute, time_second);
			iText(792,368,text_time_value,GLUT_BITMAP_HELVETICA_18);
		}
		//iSetColor(168,38,147);
			
		iSetColor(255,255,255);
		iRectangle(754, 244, 118, 30);
		iRectangle(755, 245, 118, 30);

		iSetColor(255, 255, 255);
		iText(762, 253, str,GLUT_BITMAP_HELVETICA_18);
	}
}

void level()
{
	if(page == 6)
	{
		iShowBMP(233,0,"image/setting_page.bmp");
		
		FILE *fp;
		fp = fopen("Level.txt", "r");
		fscanf(fp," %d", &play);
		fclose(fp);
		
		iSetColor(255,255,255);		
		if(play == 1)
			iText(835,455,"ON",GLUT_BITMAP_HELVETICA_18);
		else if(play ==2)
			iText(836,353,"ON",GLUT_BITMAP_HELVETICA_18);
	}
}

void High_score_read()
{
	if((life == 0 && play == 1) || page == 3)	// play = 1 means easy level
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

	
	else if((life == 0 && play == 2) || page == 4)	// play = 2 means hard level
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
		highScoreFound = 1;
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

void show_score_and_life_in_text()
{	
	iSetColor(168,38,147);
	iFilledRectangle(240,652,891,60);

	//score
	iSetColor(255,255,255);
	sprintf(text_score,"Score");
	iText(285,689,text_score,GLUT_BITMAP_HELVETICA_18);

	sprintf(text_score_value,"%d",scr);
	iText(295,665,text_score_value,GLUT_BITMAP_HELVETICA_18);
	
	//Time
	sprintf(text_time,"Time");
	iText(400,689,text_time,GLUT_BITMAP_HELVETICA_18);

	time_minute = my_time/60;
	time_second =((my_time/60.0)-time_minute)*60;
	
	if(my_time < 10){		
		sprintf(text_time_value,"%d s",my_time);
		iText(410,665,text_time_value,GLUT_BITMAP_HELVETICA_18);
	}
	else if(my_time < 60){		
		sprintf(text_time_value,"%d s",my_time);
		iText(405,665,text_time_value,GLUT_BITMAP_HELVETICA_18);
	}
	else if( time_second < 10 ){		
		sprintf(text_time_value,"%d m %.0f s",time_minute, time_second);
		iText(393,665,text_time_value,GLUT_BITMAP_HELVETICA_18);
	}
	else{				
		sprintf(text_time_value,"%d m %.0f s",time_minute, time_second);
		iText(388,665,text_time_value,GLUT_BITMAP_HELVETICA_18);
	}

	//life		
	sprintf(text_life,"Life");
	iText(500,689,text_life,GLUT_BITMAP_HELVETICA_18);

	sprintf(text_life_value,"%d",life);
	iText(508,665,text_life_value,GLUT_BITMAP_HELVETICA_18);
	//iShowBMP(850,687,"life.bmp");
	
	//level
	iText(590,689,"Level",GLUT_BITMAP_HELVETICA_18);

	if (play == 1)
		iText(592,665,"Easy",GLUT_BITMAP_HELVETICA_18);
	else if(play == 2)
		iText(592,665,"Hard",GLUT_BITMAP_HELVETICA_18);

	//Pause
	iSetColor(255,255,255);
	if(pause == 0)
	{
		iText(745,677,"Pause",GLUT_BITMAP_HELVETICA_18);	
		iRectangle(730, 665, 80, 35);
	}
	else
	{
		iText(738,677,"Resume",GLUT_BITMAP_HELVETICA_18);
		iRectangle(730, 665, 80, 35);
	}

	//Restart
	iText(877,677,"Restart",GLUT_BITMAP_HELVETICA_18);
	iRectangle(865, 665, 80, 35);
	
	//Manu
	iText(1018,677,"Manu",GLUT_BITMAP_HELVETICA_18);
	iRectangle(1000, 665, 80, 35);




	// high score
	/*if(highScoreFound == 1)
	{
		iSetColor(255,0,0);
		iText(172,360,"GAME OVER",GLUT_BITMAP_HELVETICA_18);
		iSetColor(0,255,0);
		iText(125,305,"wow!!!  A new high score",GLUT_BITMAP_HELVETICA_18);
		iText(140,265,"So, click in the rectangle.", GLUT_BITMAP_HELVETICA_18);
		iText(152,245,"And enter your name.", GLUT_BITMAP_HELVETICA_18);
	}*/
}



void iKeyboard(unsigned char mx)
{
	if(mx == 'w' || mx == 'W')
	{
		mode[0] = 1;
		w[0] = 1;
	}

	else if(mx == 'd' || mx == 'D')
	{
		mode[0] = 1;
		d[0] = 1;
	}

	else if(mx == 'a' || mx == 'A')
	{
		mode[0] = 1;
		a[0] = 1;
	}

///////

	if( bulletget[0] == 0 && (mx == 'w' || mx == 'W'))
	{
		mode[1] = 1;
		w[1] = 1;
	}
		
	else if( bulletget[0] == 0 && (mx == 'd' || mx == 'D'))
	{
		mode[1] = 1;
		d[1] = 1;
	}

	else if( bulletget[0] == 0  && (mx == 'a' || mx == 'A'))
	{
		mode[1] = 1;
		a[1] = 1;
	}

//////
	if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 'w' || mx == 'W') )
	{
		mode[2] = 1;
		w[2] = 1;
	}
	
	else if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 'a' || mx == 'A') )
	{
		mode[2] = 1;
		a[2] = 1;
	}

	else if( bulletget[0] == 0 && bulletget[1] == 0 && (mx == 'd' || mx == 'D') )
	{
		mode[2] = 1;
		d[2] = 1;
	}


	if(highScoreFound == 1)
	{
		if(mx == 8)	/// if backspace is pressed from keyboard
		{			
			if(len != 0 )
			{
				len -- ;
				str[len] = ' ' ;				
			}
		}

		else if(len == 8 )	/// if name length exceed 8 
		{
			/// Do nothing
		}

		else if(mx == 32)  /// if space is pressed from keyboard
		{			
			/// Do nothing
		}

		else if(mx == '\r')	/// if enter is pressed from keyboard
		{
			if(len != 0)
			{
				strcpy(scores[5].name, str);
				scores[5].highscore = scr;			

				for(n = 0; n < len; n++)
					str[n] = 0;
				len = 0;				
				iSetColor(255, 0, 0);
				High_score_Write();
				variable_reinitialization_3();
			}			
		}
	
		else	/// insert the character to str[] 
		{
			str[len] = mx;
			len ++ ;
		}
	}
}

void iSpecialKeyboard(unsigned char  a)
{
	if(a == GLUT_KEY_LEFT && shooterX >240 && end_life==0)
	{
		shooterX -= 10;
		if(bulletget[0] == 1)	bulletX[0] -=10;
		if(bulletget[1] == 1)	bulletX[1] -=10;
		if(bulletget[2] == 1)	bulletX[2] -=10;
	}
	
	if(a == GLUT_KEY_RIGHT && shooterX <1040 && end_life==0)
	{
		shooterX += 10;
		if(bulletget[0] == 1)	bulletX[0] +=10;
		if(bulletget[1] == 1)	bulletX[1] +=10;
		if(bulletget[2] == 1)	bulletX[2] +=10;
	}

}

bool detect_collision_1(int j)
{
	return (bulletX[i] > ( bubble[j].bubbleX + 4)) && (bulletX[i] < (bubble[j].bubbleX +64-1)) &&  (bulletY[i] > (bubble[j].bubbleY + 2)) &&
																												(bulletY[i] < bubble[j].bubbleY +64-2);
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
				if(w[i]==1 && x[i]==1 && y[i]==1)
				{
					bulletget[i] = 0;
					bulletY[i] += 5;
				}

				else if (a[i]== 1 && z[i]==1)
				{
					x[i] = 0;
					bulletget[i] = 0;
					bulletX[i] -= 4;
					bulletY[i] += 3;
				}

				else if ( d[i]== 1 )
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
						w[i]=0;
						a[i]=0;
						d[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletX[i] = shooterX + 46;
						bulletY[i] = 80;
						bubble[j].bubbleX = (245+rand() % 820);
						bubble[j].bubbleY = 712;
					}
		
					else if(bulletX[i] > 1133 || bulletX[i]<240 || bulletY[i] > 652)
					{
						mode[i] = 0;
						w[i]=0;
						a[i]=0;
						d[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletget[i] = 1;
						bulletX[i] = shooterX + 46;
						bulletY[i] = 80;
					}
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

void method()
{
	for(i=0;i<=2;i++)
		{
	
			if(mode[i] == 1)
			{
				if(w[i]==1 && x[i]==1 && y[i]==1)
				{
					bulletget[i] = 0;
					bulletY[i] += 5;
				}

				else if (a[i]== 1 && z[i]==1)
				{
					x[i] = 0;
					bulletget[i] = 0;
					bulletX[i] -= 4;
					bulletY[i] += 3;
				}

				else if ( d[i]== 1 )
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
						w[i]=0;
						a[i]=0;
						d[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletX[i] = shooterX + 46;
						bulletY[i] = 80;
						
						if(count[j] == 3) // for 1 shot 3, for 2 shot 5, for 3 shot 7
						{
							count[j] = 1;
							scr += 5;
							bubble[j].bubbleX = (245+rand() % 820);
							bubble[j].bubbleY = 712;
						}
					}
		
					else if(bulletX[i] > 1133 || bulletX[i]<240 || bulletY[i] > 652)
					{
						mode[i] = 0;
						w[i]=0;
						a[i]=0;
						d[i]=0;
						x[i]=1;
						y[i]=1;
						z[i]=1;
						bulletget[i] = 1;
						bulletX[i] = shooterX + 46;
						bulletY[i] = 80;
					}
				}	
			}
		}
}

void main()
{
	    
	iSetTimer(10,bullet_change_and_collision_1);
	iSetTimer(5,bullet_change_and_collision_2);
	iSetTimer(35,bubble_change);	
	iSetTimer(1000, update_time);
	iInitialize(1366,712,"Air Strike");	
}

void iMouseMove(int k3, int k4 ){}
void iPassiveMouseMove(int k5, int k6){
	printf("%d %d \n",k5,k6);
}
