// for timer/couter --> int my_time, update_time(),  iSetTimer(1000, update_time), iResumeTimer(3), iPauseTimer(3) 
// for wait a moment after gave over --> int waitAMoment
// int play, value of play = 1 means easy level, value of play = 2 means hard level

#include"iGraphics.h"
void iMouse(int button, int state, int k1, int k2);
void iKeyboard(unsigned char mx);					// ..., enter the name
void iSpecialKeyboard(unsigned char a);				// manage the movement of shooter

void iMouseMove(int k3, int k4 );
void iPassiveMouseMove(int k5, int k6);

void show_score_and_life_in_text();		// when game is running show the score, time, life, level, pause, resume, restart, Manu
void bulletMethod();					// create 3 bullet
void bubbleMethod();					// show bubble.bmp 
void lifeMethod();						// if life = 0 then this function will be relevent

void High_score_read();					// read the high scores from text file and call check_high_score() function
void High_score_Write();				// call the high_score_sort() function and write the scores into a text file
void check_high_score();				// check high score found or not.
void high_score_sort();					// sort the high scores

void start_game();
void home();							//(p0) show the p0_home_page.bmp 
void score_page();						//(p2) show the p2_score_page.bmp
void show_score();						//(p3) show the p3_show_high_score_page.bmp and print/display the high scores
void instruction();						//(p5) show the p5_instruction_page.bmp
void setting();							//(p6) show the p6_setting_page.bmp and select the level
void level_read();
void game_over();						//(p7) show the p7_game_over.bmp , game score and time
void game_over_and_high_score();		//(p8) show the p8_game_over_and_high_score.bmp, game score, time and input rectangle
void about_us();						//(p9) show the p9_about_us.bmp

void common_variable_reinitialization();
void variable_reinitialization_1();		// for try again. when game is running or over
void variable_reinitialization_2();		// back to the main menu. when game is running or over

void bubble_change();					// change the bubble movement and inside this function life-- statement execute
bool detect_collision(int j);			// detect bubble and bullet collision

void bullet_change_and_collision_level_wise(); // manage and work on (level wise) bullet collision
void bullet_change_and_collision();			   // this function is called by bullet_change_and_collision_level_wise() function

void update_time();


//*** variable declaration ***//

int shooterX=640, shooterY=20;
char text_score[20], text_score_value[20], text_life[20], text_life_value[20], aa1[20];
char str[100];
char text_high_score[100];
int scr=0;
int end_life= 0;	// used in lifeMethod() .
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
int waitAMoment = 0;	// for wait a moment after gave over

double bulletX[3]={685.5,685.5,685.5};
double bulletY[3]={80,80,80};

// ** warking with bullet start **

int bulletget[3]={1,1,1};
int mode[3]={0,0,0};
int w[3]={0,0,0};
int a[3]={0,0,0};
int d[3]={0,0,0};

int x[3]={1,1,1};
int y[3]={1,1,1};
int z[3]={1,1,1};
int i, j, k;	// for loop incremental variable

int count[5]={1,1,1,1,1};

// ** warking with bullet end **

int p; // for loop incremental variable

struct file
{
    char name[25];
    int highscore;	
	int second;
	int minute;
} b,scores[6];

struct bubble
{
	int bubbleX;	////radius of bubble 58.
	int bubbleY;
	float dx;
	float dy;
}	bubble[20]={{340,660,2,-1},{1020,660,-2,-2},{(260+rand() % 800),1300,2,-3},
						{(260+rand() % 800),1700,-3,-2},{(260+rand() % 800),3000,-3,-3}};

void iDraw()
{
	iClear();	
	start_game();
	home();
	score_page();
	show_score();
	instruction();
	about_us();
	setting();	
	game_over();
	game_over_and_high_score();
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
	
		iSetColor(168,38,147);
		iFilledRectangle(238,0,3,712);	/// left vertical line
		iFilledRectangle(1130,0,3,712);	/// right vertical line		
		iLine(239,85,1133,85);			/// horizontal line
	}
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

void home()
{
	if(page == 0)
	{
		iShowBMP(233,0,"image/p0_home_page.bmp");
	}
}

void score_page()
{
	if(page == 2)
	{
		iShowBMP(233,0,"image/p2_score_page.bmp");
	}
}

void show_score()
{
	int i, j=311, temp=1;
	
	if(page == 3)	// show easy high scores
	{
		High_score_read();
		iShowBMP(233,0,"image/p3_show_high_score_page.bmp");

		iSetColor(168,38,147);
		iRectangle(487,250, 388, 278);		
		iRectangle(486,249, 390, 280);		
		iRectangle(485,248, 392, 282);		
		iRectangle(484,247, 394, 284);		
		iRectangle(483,246, 396, 286);		
		
		iSetColor(255,255,255);
		iRectangle(482,245, 398, 288);
		iRectangle(481,244, 400, 290);

		iSetColor(168,38,147);
		iRectangle(480,243, 402, 292);
		iRectangle(479,242, 404, 294);
		iRectangle(478,241, 406, 296);
		iRectangle(477,240, 408, 298);
		iRectangle(476,239, 410, 300)	;	

		iSetColor(255,255,255);
		iLine(487,480,874,480);
		iLine(487,434,874,434);
		iLine(487,390,874,390);
		iLine(487,343,874,343);
		iLine(487,298,874,298);

		iText(530,495,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(680,495,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(785,495,"Time",GLUT_BITMAP_TIMES_ROMAN_24);

		j=450;
		for(i=0;i<=4;i++)	// show sequence number
		{
			sprintf(text_high_score,"%d.", temp++);			
			iText(500,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}
		
		j=450;
		for(i=0;i<=4;i++)	// show easy high score holder's name
		{
			sprintf(text_high_score,"%s", scores[i].name);			
			iText(530,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}

		j=450;
		for(i=0;i<=4;i++)	// show easy high scores
		{
			sprintf(text_high_score,"%d", scores[i].highscore);			
			iText(686,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}	

		j=450;
		for(i=0;i<=4;i++)	// show minute and second
		{
			if(scores[i].minute == 0){			
				sprintf(text_high_score,"%ds", scores[i].second);			
				iText(795,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else{			
				sprintf(text_high_score,"%dm %ds", scores[i].minute, scores[i].second);			
				iText(785,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			}
			j -= 45;
		}	
	}

	else if(page == 4)	// show hard high scores
	{
		High_score_read();
		iShowBMP(233,0,"image/p3_show_high_score_page.bmp");

		iSetColor(168,38,147);
		iRectangle(487,250, 388, 278);		
		iRectangle(486,249, 390, 280);		
		iRectangle(485,248, 392, 282);		
		iRectangle(484,247, 394, 284);		
		iRectangle(483,246, 396, 286);		
		
		iSetColor(255,255,255);
		iRectangle(482,245, 398, 288);
		iRectangle(481,244, 400, 290);

		iSetColor(168,38,147);
		iRectangle(480,243, 402, 292);
		iRectangle(479,242, 404, 294);
		iRectangle(478,241, 406, 296);
		iRectangle(477,240, 408, 298);
		iRectangle(476,239, 410, 300)	;	

		iSetColor(255,255,255);
		iLine(487,480,874,480);
		iLine(487,434,874,434);
		iLine(487,390,874,390);
		iLine(487,343,874,343);
		iLine(487,298,874,298);

		iText(530,495,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(680,495,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(785,495,"Time",GLUT_BITMAP_TIMES_ROMAN_24);

		j=450;
		for(i=0;i<=4;i++)	// show sequence number
		{
			sprintf(text_high_score,"%d.", temp++);			
			iText(500,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}
		
		j=450;
		for(i=0;i<=4;i++)	// show easy high score holder's name
		{
			sprintf(text_high_score,"%s", scores[i].name);			
			iText(530,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}

		j=450;
		for(i=0;i<=4;i++)	// show easy high scores
		{
			sprintf(text_high_score,"%d", scores[i].highscore);			
			iText(686,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			j -= 45;
		}	

		j=450;
		for(i=0;i<=4;i++)	// show minute and second
		{
			if(scores[i].minute == 0){			
				sprintf(text_high_score,"%ds", scores[i].second);			
				iText(795,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			}
			else{			
				sprintf(text_high_score,"%dm %ds", scores[i].minute, scores[i].second);			
				iText(785,j,text_high_score,GLUT_BITMAP_TIMES_ROMAN_24);
			}
			j -= 45;
		}				
	}
}

void instruction()
{
	if(page == 5){
		iShowBMP(233,0,"image/p5_instruction_page.bmp");		
	}
}

void setting()
{
	if(page == 6)
	{
		iShowBMP(233,0,"image/p6_setting_page.bmp");
		
		FILE *fp;
		fp = fopen("file/Level.txt", "r");
		fscanf(fp," %d", &play);
		fclose(fp);
		
		iSetColor(255,255,255);
		if(play == 1)
			iText(835,455,"ON",GLUT_BITMAP_HELVETICA_18);
		else if(play ==2)
			iText(836,353,"ON",GLUT_BITMAP_HELVETICA_18);
	}
}

void level_read()
{
	int temp,i=0;
	FILE *fp;

	fp = fopen("file/Level.txt", "r");
	fscanf(fp," %d  %d", &play,&temp);   // read the value of a from the level.txt file
	fclose(fp);

	if(life == -30)		// initial declared value of life=-30
		life = temp;
}

void game_over()
{
	if(page == 7)
	{
		iShowBMP(233,0,"image/p7_game_over.bmp");

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

void game_over_and_high_score()
{
	if(page == 8){
		iShowBMP(233,0,"image/p8_game_over_and_high_score.bmp");

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

void about_us()
{
	if(page == 9){		
		iShowBMP(233,0,"image/p9_about_us.bmp");
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
	}

	if(life <= 0 && highScoreFound == 0)
	{	
		if( waitAMoment < 180 )
		{
			waitAMoment ++ ;			
			printf("wait just a moment");

			iSetColor(255,255,255);
			iText(577,368,"Best Wishes for the Future",GLUT_BITMAP_HELVETICA_18);
		}
		else
			page = 7;
	}

	if(life <= 0 && highScoreFound == 1)
	{
		if( waitAMoment < 180 )
		{
			waitAMoment ++ ;
			printf("wait just a moment");

			iSetColor(255,255,255);
			iText(577,368,"Best Wishes for the Future",GLUT_BITMAP_HELVETICA_18);
		}
		else
			page = 8;
	}
	
}



void iMouse(int button, int state, int k1, int k2)
{	
	if(page==0 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if(k1 >= 548 && k1 <= 815 && k2 >= 479 && k2 <= 539)	/// go to play page
		{
			bubble[0].dy = -1;	bubble[1].dy = -2;  bubble[2].dy = -3;  bubble[3].dy = -2;  bubble[4].dy = -3;
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
			life = 3;
			
			FILE *nakib;
			nakib = fopen("file/Level.txt","w");
			fprintf(nakib,"%d %d",play,life);
			fclose(nakib);
		}
		
		else if(k1 >= 564 && k1 <= 804 && k2 >= 330 && k2 <= 388)	//// for hard level
		{
			play = 2;
			life = 3;

			FILE *nakib;
			nakib = fopen("file/Level.txt","w");
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
	if(page==8 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)  /// when click the enter button ( to insert the name of the highScorer )
	{
		if(k1 >= 548 && k1 <= 812 && k2 >= 135 && k2 <= 195)	
		{
			if(len != 0)
			{
				strcpy(scores[5].name, str);
				scores[5].highscore = scr;

				scores[5].minute = time_minute;
				scores[5].second = time_second;

				for(n = 0; n < len; n++)
					str[n] = 0;
				len = 0;				
				
				High_score_Write();
				variable_reinitialization_2();
			}	
		}
	}
}

void update_time()
{
	my_time++;
}

void variable_reinitialization_1()	// for try again. when game is running or over
{	
	page = 1;				
	iResumeTimer(3);
			
	common_variable_reinitialization();
}

void variable_reinitialization_2()  // back to the main menu. when game is running or over
{	
	page = 0;
	iPauseTimer(1);

	common_variable_reinitialization();
}

void common_variable_reinitialization()
{
	FILE *fp;
	fp = fopen("file/Level.txt", "r");
	fscanf(fp," %d  %d", &play,&life);
	fclose(fp);

	shooterX = 640;

	pause = 0;				// pause = 0 means the game is not in pause mode
	my_time = 0;			// for reset the time counter

	waitAMoment = 0;		// waiting time reset ( it is necessary for when game is over )

	highScoreFound = 0;		// 0 means high score not found
	scr = 0;				// game score/point
	end_life = 0;			// when life become 0 then end_life become 1 and game will be end

	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);

	bubble[0].bubbleX = 260+rand() % 800;
	bubble[1].bubbleX = 260+rand() % 800;
	bubble[2].bubbleX = 260+rand() % 800;
	bubble[3].bubbleX = 260+rand() % 800;
	bubble[4].bubbleX = 260+rand() % 800;
	bubble[0].bubbleY = 660;
	bubble[1].bubbleY = 660;
	bubble[2].bubbleY = 1300;	
	bubble[3].bubbleY = 1700; // after 20 sec	
	bubble[4].bubbleY = 3000; // after 30 sec

	bubble[0].dy = -1;	bubble[1].dy = -2;  bubble[2].dy = -3;  bubble[3].dy = -2;  bubble[4].dy = -3;

	bulletget[0] = 1; bulletget[1] = 1; bulletget[2] = 1;

	mode[0]= 0;	mode[1]= 0; mode[2]= 0;

	bulletX[0]=685.5; bulletX[1]=685.5; bulletX[2]=685.5;
	bulletY[0]=80; bulletY[1]=80; bulletY[2]=80;	

	w[0]=0;	w[1]=0; w[2]=0;
	a[0]=0;	a[1]=0; a[2]=0;
	d[0]=0;	d[1]=0; d[2]=0;

	x[0]=1; x[1]=1; x[2]=1;
	y[0]=1; y[1]=1; y[2]=1;
	z[0]=1; z[1]=1; z[2]=1;

	count[0]=1;	count[1]=1; count[2]=1; count[3]=1; count[4]=1;
}

void High_score_read()
{
	if((life == 0 && play == 1) || page == 3)	// play = 1 means easy level
	{
		FILE *fp;
		int i;
		char a1[20],a2[10], s1[4], m1[4];
		
		fp = fopen("file/easy_score.txt", "r");    
		if(fp == NULL)
		{
			printf("Error in opening file\n");
			printf("The value of fp = %d\n",fp);
		}		
		
		else
		{               
			for(i=0;i<5;i++)
			{
				fscanf(fp,"%s %s %s %s",a1,a2,m1,s1 );

				strcpy(scores[i].name, a1);		
				scores[i].highscore = atoi(a2);
				scores[i].minute = atoi(m1);
				scores[i].second = atoi(s1);

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
		char a1[20],a2[10], s1[4], m1[4];
		
		fp = fopen("file/hard_score.txt", "r");    
		if(fp == NULL)
		{
			printf("Error in opening file\n");
			printf("The value of fp = %d\n",fp);
		}
		
		else
		{               
			for(i=0;i<5;i++)
			{
				fscanf(fp,"%s %s %s %s",a1,a2,m1,s1 );

				strcpy(scores[i].name, a1);		
				scores[i].highscore = atoi(a2);
				scores[i].minute = atoi(m1);
				scores[i].second = atoi(s1);

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

void high_score_sort()
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
	high_score_sort();
	
	if(play == 1)
	{
		FILE *fp;
		fp = fopen("file/easy_score.txt", "w");
		for(i=0;i<5;i++)
			fprintf(fp,"%s \t\t\t %d \t %d \t %d  \n", scores[i].name, scores[i].highscore,
														scores[i].minute, scores[i].second );
		fclose(fp);
	}

	else if(play == 2)
	{
		FILE *fp;
		fp = fopen("file/hard_score.txt", "w");
		for(i=0;i<5;i++)
				fprintf(fp,"%s \t\t\t %d \t %d \t %d  \n", scores[i].name, scores[i].highscore,
														scores[i].minute, scores[i].second );
		fclose(fp);
	}
}

void show_score_and_life_in_text()
{	
	iSetColor(168,38,147);
	iFilledRectangle(242,652,887,60);

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


	if(highScoreFound == 1 && page == 8)
	{
		if(mx == 8)	/// if backspace is pressed from keyboard
		{			
			if(len != 0 )
			{
				len -- ;
				str[len] = ' ' ;				
			}
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

				scores[5].minute = time_minute;
				scores[5].second = time_second;

				for(n = 0; n < len; n++)
					str[n] = 0;
				len = 0;								

				High_score_Write();
				variable_reinitialization_2();
			}			
		}

		else if(len == 8 )	/// if name length exceed 8 
		{
			/// Do nothing
		}
	
		else	/// insert the character to str[] 
		{
			str[len] = mx;
			len ++ ;
		}
	}
}

void iSpecialKeyboard(unsigned char a)
{
	if(a == GLUT_KEY_LEFT && shooterX >240 && end_life==0)
	{
		shooterX -= 20;
		if(bulletget[0] == 1)	bulletX[0] -=20;
		if(bulletget[1] == 1)	bulletX[1] -=20;
		if(bulletget[2] == 1)	bulletX[2] -=20;
	}
	
	if(a == GLUT_KEY_RIGHT && shooterX <1040 && end_life==0)
	{
		shooterX += 20;
		if(bulletget[0] == 1)	bulletX[0] +=20;
		if(bulletget[1] == 1)	bulletX[1] +=20;
		if(bulletget[2] == 1)	bulletX[2] +=20;
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
			if(bubble[p].bubbleX <= 242 || bubble[p].bubbleX >= 1064)
				bubble[p].dx = -bubble[p].dx;
			if(bubble[p].bubbleY < 84 )	
			{
				bubble[p].bubbleX =(260+rand() % 800);
				bubble[p].bubbleY = 660;		// (670+rand() % 500) 
				life -=1;
				count[p] = 1;
			}
		}
		High_score_read();
	}
}

bool detect_collision(int j)
{
	return (bulletX[i] > ( bubble[j].bubbleX + 4)) && (bulletX[i] < (bubble[j].bubbleX +64-1)) &&  
			(bulletY[i] > (bubble[j].bubbleY + 2)) && (bulletY[i] < bubble[j].bubbleY +64-2);
}

void bullet_change_and_collision_level_wise()
{
	if(page == 1 && play ==1)	// play = 1 for easy level
	{
		bullet_change_and_collision();
		bullet_change_and_collision(); // same method call again to increase the bullet speed 2 times
	}

	else if(page == 1 && play ==2)	// play = 2 for hard level
	{
		bullet_change_and_collision();
		bullet_change_and_collision(); // same method call again to increase the bullet speed 2 times
	}
}

void bullet_change_and_collision()
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
				if(detect_collision(j) && play == 1)	// play = 1 for easy level
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
					bubble[j].bubbleX = (260+rand() % 800);
					bubble[j].bubbleY = 660;
				}
				else if(detect_collision(j) && play == 2)	 // play = 2 for hard level
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
						
					if(count[j] == 5) // for blust the bubble in 1 shot 3, for 2 shot 5, for 3 shot 7
					{
						count[j] = 1;
						scr += 5;
						bubble[j].bubbleX = (260+rand() % 800);
						bubble[j].bubbleY = 660;
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

void increase_bubble_speed(){
	/*bubble[0].dx = -3; bubble[0].dy = -3;  bubble[1].dx = 3; bubble[1].dy = -4;  bubble[2].dx = 4; bubble[2].dy = -3;
	  bubble[3].dx = -4; bubble[3].dy = -4;  bubble[4].dx = -2; bubble[4].dy = -5;*/
		
	for(p=0;p<=4;p++)
	{
		// bubble[p].dy = bubble[p].dy - 0.01;
		bubble[p].dy = bubble[p].dy - 1;
	}	
}

void main()
{	
	// maintain the iSetTimer() function sequence strictly

	iSetTimer(10,bullet_change_and_collision_level_wise); // timer number 0
	iSetTimer(120000,increase_bubble_speed);		// timer number 1, previously it was for bullte_change_and_collision something like that
	iSetTimer(35,bubble_change);	// timer number 2
	iSetTimer(1000, update_time);	// timer number 3

	iInitialize(1366,712,"Air Strike");	
}


void iMouseMove(int k3, int k4 ){
	for(p=0;p<=4;p++)
	{
		//printf("bubble[%d].dx = %f \t",p, bubble[p].dx);
		printf("bubble[%d].dy = %f \n",p, bubble[p].dy);
	}
	printf("\n\n");
}
void iPassiveMouseMove(int k5, int k6){
	 //printf("%d %d \n",k5,k6);
}
