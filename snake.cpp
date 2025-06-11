#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
//#include <windows.h>

int window;
int mainStack=0;
int levelStack=0,islevel=0;
int mainmenu=1;
int helpmenu=0;
void* font = GLUT_BITMAP_HELVETICA_18;


int SnakeLength, SleepDelay, level, dir, speed, XSize, YSize;
float snake[2000][2], snakeFood[2],bonusFood[2],CellSize = 1.0f;
int horizontalWalls[80][80];
int verticalWalls[80][80];
int easyWalls[80][80];
int mediumWalls[80][80];
int easy=0,medium=1,hard=2;
int hardness=1;
char score[3];

int isPlaying=0;
int ynStack=0,yesOrNo=0;
int isPause=0,pauseStack=0;;
int gameOver=0;
int gameOverStack=0;

void createWalls()
{
    int i,j;

    for(i=0;i<80;i++)
    {
        for(j=0;j<80;j++)
        {
            horizontalWalls[i][j]=0;
            verticalWalls[i][j]=0;
        
        }
    }



for(i=20;i<60;i++)
{
    verticalWalls[2][i] = 1;
    easyWalls[2][i]=1;
    mediumWalls[2][i]=1;
}
for(i=20;i<60;i++)
{
    verticalWalls[76][i] = 1;
    easyWalls[76][i]=1;
    mediumWalls[76][i]=1;
}

for(i=14;i<66;i++)
{
    horizontalWalls[i][26] = 1;
    mediumWalls[i][26]=1;
}

for(i=14;i<66;i++)
{
    horizontalWalls[i][56] = 1;
    mediumWalls[i][56]=1;
}


horizontalWalls[i][10] = 1;
verticalWalls[10][i] = 1;

for(i=20;i<60;i++)
{
    verticalWalls[2][i] = 1;
}

for(i=20;i<60;i++)
{
    verticalWalls[76][i] = 1;
}

for(i=14;i<66;i++)
{
    horizontalWalls[i][26] = 1;
}


for(i=56;i<76;i++)
{
    verticalWalls[8][i] = 1;
}

for(i=8;i<28;i++)
{
    horizontalWalls[i][76] = 1;
}

for(i=24;i>4;i--)
{
    verticalWalls[8][i] = 1;
}

for(i=8;i<28;i++)
{
    horizontalWalls[i][4] = 1;
}

for(i=24;i>4;i--)
{
    verticalWalls[70][i] = 1;
}

for(i=50;i<70;i++)
{
    horizontalWalls[i][4] = 1;
}

for(i=56;i<76;i++)
{
    verticalWalls[70][i] = 1;
}

for(i=50;i<71;i++)
{
    horizontalWalls[i][76] = 1;
}

for(i=30;i<35;i++)
{
    horizontalWalls[i][50] = 1;
}

for(i=30;i<35;i++)
{
    horizontalWalls[i][35] = 1;
}
for(i=41;i<45;i++)
{
    horizontalWalls[i][50] = 1;
}

for(i=50;i>45;i--)
{
    verticalWalls[30][i] = 1;
}

for(i=50;i>45;i--)
{
    verticalWalls[30][i] = 1;
}
for(i=39;i>35;i--)
{
    verticalWalls[30][i] = 1;
}

for(i=51;i>45;i--)
{
    verticalWalls[45][i] = 1;
}

for(i=40;i>35;i--)
{
    verticalWalls[45][i] = 1;
}

for(i=41;i<45;i++)
{
    horizontalWalls[i][35] = 1;
}

}

int checkGameOver()
{
    int game=0;
    int xCoord,yCoord;

    xCoord=snake[0][0];
    yCoord=snake[0][1];


    if (hardness==0)
    {
        if(easyWalls[xCoord][yCoord]==1 || easyWalls[xCoord][yCoord]==1) game=-1;
    }
    if(hardness==1)
    {
       if(mediumWalls[xCoord][yCoord]==1 || mediumWalls[xCoord][yCoord]==1) game=-1;
    }
    if(hardness==2)
    {
      if(horizontalWalls[xCoord][yCoord]==1 || verticalWalls[xCoord][yCoord]==1) game=-1;
    }

    for(int i=1;i<SnakeLength;i++)
    {

            if(snake[0][0]== snake[i][0] && snake[0][1]== snake[i][1]) game=-1;
    }
    if(xCoord>XSize || xCoord<0 || yCoord>YSize || yCoord<0) game=-1;

    return game;
}

void initGame()
{
    SnakeLength = 7;
    score[0] = '0';
    score[1] = '0';
    score[2] = '0';
    if (hardness==0) SleepDelay = 100000;
    if (hardness==1) SleepDelay = 75000;
    if (hardness==2) SleepDelay = 50000;

    level = 1;
    dir = GLUT_KEY_LEFT;
    speed = 1;
    XSize = 80;
    YSize = 80;
    // Init snake code below:
    for (int i=0; i<SnakeLength; i++)
        {
            snake[i][0] = 40.0f + float(i*CellSize);
            snake[i][1] = 40.0f;
        }
        createWalls();
}

void DisplayScreen()
{
   glClearColor(0.0, 1.000, 0.498, 1.196078);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.545, 0.000, 0.000);
   for (int i=0; i<SnakeLength; i++)
   {
       glRectf (snake[i][0],snake[i][1],float(snake[i][0]+CellSize),float(snake[i][1]+CellSize));
   }
    glColor3f(1.0, 0.271, 0.0);
   glRectf (snake[0][0],snake[0][1],float(snake[0][0]+CellSize),float(snake[0][1]+CellSize));



   // THERE IS WALLS //

   if(hardness == easy)
   {
       glColor3f(0.0, 0.0, 0.0);
        glRectf (2,20,3,60);
         glRectf (76,20,77,60);
   }
   else if (hardness == medium)
   {
        glColor3f(0.0, 0.0, 0.0);
        glRectf (2,20,3,60);
        glRectf (76,20,77,60);
        glRectf (14,26,66,27);
        glRectf (14,56,66,57);
   }


   else if (hardness == hard)
    {
    glColor3f(0.0, 0.0, 0.0);
    glRectf (2,20,3,60);
    glRectf (76,20,77,60);
    glRectf (14,26,66,27);
    glRectf (14,56,66,57);

    glRectf (8,56,9,76);
    glRectf (8,76,28,77);

    glRectf (8,24,9,4);
    glRectf (8,4,28,5);

    glRectf (70,24,71,4);
    glRectf (50,4,70,5);

    glRectf (70,56,71,76);
    glRectf (50,76,71,77);

    glRectf (30,50,35,51);
    glRectf (30,50,31,45);
    glRectf (30,40,31,35);
    glRectf (30,35,35,36);

    glRectf (41,50,45,51);
    glRectf (45,51,46,45);
    glRectf (45,40,46,35);
    glRectf (41,35,45,36);

    }

      glColor3f(0.545, 0.000, 0.000);
   glRasterPos3f(66.0f, 78.0f,0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'S');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'c');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'o');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'r');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'e');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,':');
    for(int i=0;i<3;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,score[i]);
    }

   glColor3f(1.0, 0.0, 0.0);
   glRectf(snakeFood[0],snakeFood[1],snakeFood[0]+CellSize,snakeFood[1]+CellSize);

   
   glFlush();
   glutSwapBuffers();
}


void GenerateFood() {
    int con=0;
   bool generated = false;
   while (!generated) {
     
      snakeFood[0] = rand() % XSize;
      snakeFood[1] = rand() % YSize;

      int xCoord = snakeFood[0];
      int yCoord = snakeFood[1];

      for(int i=0;i<SnakeLength;i++)
      {
          if(xCoord== snake[i][0] && yCoord==snake[i][1]) con=-1;

      }
      for(int j=0;j<80;j++)
      {
          if(horizontalWalls[xCoord][yCoord]==1 || verticalWalls[xCoord][yCoord]==1) con=-1;
      }
    if(con!=-1) generated = true;

}
}

void isEaten()
{
    if(snake[0][0]==snakeFood[0] && snake[0][1]==snakeFood[1])
    {
        SnakeLength+=2;

            if(score[2]!='9') { score[2]+=1; }
            else {
                 if(score[1]!='9')  { score[1]+=1; score[2]='0'; }
                   else {
                          score[0]+=1;
                          score[1]='0';
                        }
                 }
        GenerateFood();
    }
}

void DelayGame() {
    usleep(SleepDelay);
}

// void MyKeyboardFunc(unsigned char Key, int x, int y)
// {
// switch (Key) {
//        case 'a': {
//           if (dir != GLUT_KEY_RIGHT) {
//              dir = GLUT_KEY_LEFT;
//           }
//           break;
//        }
//        case 'd': {
//           if (dir != GLUT_KEY_LEFT) {
//              dir = GLUT_KEY_RIGHT;
//           }
//           break;
//        }
//        case 'w': {
//           if (dir != GLUT_KEY_DOWN) {
//              dir = GLUT_KEY_UP;
//           }
//           break;
//        }
//        case 's': {
//           if (dir != GLUT_KEY_UP) {
//              dir = GLUT_KEY_DOWN;
//           }
//           break;
//        }
//       case 27: {
//            if(isPlaying==1)
//            {
//                isPlaying=0;
//                isPause=1;
//            }
//           else yesOrNo=1;
//           break;
//     };
// }

// }
void MySpecialFunc(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            if (dir != GLUT_KEY_RIGHT) {
                dir = GLUT_KEY_LEFT;
            }
            break;

        case GLUT_KEY_RIGHT:
            if (dir != GLUT_KEY_LEFT) {
                dir = GLUT_KEY_RIGHT;
            }
            break;

        case GLUT_KEY_UP:
            if (dir != GLUT_KEY_DOWN) {
                dir = GLUT_KEY_UP;
            }
            break;

        case GLUT_KEY_DOWN:
            if (dir != GLUT_KEY_UP) {
                dir = GLUT_KEY_DOWN;
            }
            break;
    }
}
void MyKeyboardFunc(unsigned char Key, int x, int y)
{
    if (Key == 27) {  // ESC key
        if (isPlaying == 1) {
            isPlaying = 0;
            isPause = 1;
        } else {
            yesOrNo = 1;
        }
    }
}


void renderBitmapString(float x, float y, void *font, const char *string)
{
       const char *c;
       glRasterPos2f(x, y);
       for (c = string; *c != '\0'; c++) {
              glutBitmapCharacter(font, *c);
       }
}

void MoveSnake()
{
   DelayGame();
   for (int i=SnakeLength-1; i>0; i--)
   {
       snake[i][0] = snake[i-1][0];
       snake[i][1] = snake[i-1][1];
   }
//    glutKeyboardFunc(MyKeyboardFunc);
   glutKeyboardFunc(MyKeyboardFunc);     // For ESC and other normal keys
glutSpecialFunc(MySpecialFunc);       // For arrow keys

   switch (dir) {
       case GLUT_KEY_LEFT: {
          snake[0][0] -= speed;
          break;
       }
       case GLUT_KEY_RIGHT: {
          snake[0][0] += speed;
          break;
       }
       case GLUT_KEY_UP: {
          snake[0][1] += speed;
          break;
       }
       case GLUT_KEY_DOWN: {
          snake[0][1] -= speed;
          break;
       }
    };
    isEaten();

    if(checkGameOver()==-1)
    {
        isPlaying=0;
        gameOver=1;
    }

    glutPostRedisplay();
}
/////////////////////////////////////////////////////////////////////////////////////////////////



void printText()
{
   glClearColor(0.0, 0.000, 0.00, 0.196078);
   glClear(GL_COLOR_BUFFER_BIT);

   if(gameOver!=1 && helpmenu!=1)
   {

   glColor3f(1.000, 0.500, 0.000);
    renderBitmapString(24.0f, 70.0f, font, "--- Snake Game ---");

    glColor3f(0.85, 0.85, 0.100);
    renderBitmapString(28.0f, 10.0f, font, "CG Assignment");

   }
   if(mainmenu==1)
   {
       if(mainStack==0)
{
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 50.0f, font, "New Game");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 45.0f, font, "Help");
    renderBitmapString(30.0f, 40.0f, font, "Quit");
}
if(mainStack==1)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, font, "New Game");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 45.0f, font, "Help");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 40.0f, font, "Quit");
}
if(mainStack==2)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, font, "New Game");
    renderBitmapString(30.0f, 45.0f, font, "Help");
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 40.0f, font, "Quit");
}

}

 else if(helpmenu==1)
   {
           glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, font, "HELP MENU");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(1.0f, 40.0f, font, "You can use W,A,S,D for controlling the snake and menu.");
    renderBitmapString(10.0f, 35.0f, font, "Press ENTER for execute and press ESC to exit.");
    glColor3f(1.545, 1.000, 0.000);
    renderBitmapString(10.0f, 10.0f, font, "Please wait 3 seconds, it will return to main menu.");


    // usleep(999999);

    glFlush();
   glutSwapBuffers();
    helpmenu=0;
    usleep(2000000);
    mainmenu=1;
   }
   else if(islevel==1)
    {

        if(levelStack==0)
{
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 50.0f, font, "Easy");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 45.0f, font, "Medium");
    renderBitmapString(30.0f, 40.0f, font, "Hard");

}
    if(levelStack==1)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, font, "Easy");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 45.0f, font, "Medium");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 40.0f, font, "Hard");



}
    if(levelStack==2)
    {
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, font, "Easy");
    renderBitmapString(30.0f, 45.0f, font, "Medium");
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 40.0f, font, "Hard");


    }
    }
    else if (isPause==1)
    {
        if(pauseStack==0)
        {
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 45.0f, font, "Resume Game");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 40.0f, font, "Quit Game");
        }
        if(pauseStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 45.0f, font, "Resume Game");
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 40.0f, font, "Quit Game");
        }
    }
    if(yesOrNo==1)
    {
        if(ynStack==0)
        {
            glColor3f(1.0, 0.000, 0.000);
            renderBitmapString(50.0f, 45.0f, font, "Yes");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(50.0f, 40.0f, font, "No");
        }
        if(ynStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(50.0f, 45.0f, font, "Yes");
            glColor3f(1.0, 0.000, 0.000);
            renderBitmapString(50.0f, 40.0f, font, "No");
        }
    }
    else if(gameOver==1)
    {
    glColor3f(1.000, 0.000, 0.000);
    renderBitmapString(30.0f, 60.0f, font, "! GAME OVER !");
    glColor3f(0.000, 0.000, 1.000);
    renderBitmapString(25.0f, 50.0f, font, "Your Score :");

    glRasterPos3f(45.0f, 50.0f,0.0f);
        for(int i=0;i<3;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,score[i]);
    }
        if(gameOverStack==0)
        {
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 45.0f, font, "Restart Game");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 40.0f, font, "Quit Game");
        }
        if(gameOverStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 45.0f, font, "Restart Game");
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 40.0f, font, "Quit Game");
        }
    }
   glFlush();
   glutSwapBuffers();

}

void ScreenResizer(GLsizei w, GLsizei h)
{
   if (h == 0) h = 1;
   glViewport(0, 0, w, h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0f, 80.f, 0.0f, 80.f, -1.0, 1.0);
   glFlush();
}

void installSnake()
{
    initGame();
    GenerateFood();
    glutDisplayFunc(DisplayScreen);
    glutReshapeFunc(ScreenResizer);
}
void resumeSnake()
{
    glutDisplayFunc(DisplayScreen);
    glutReshapeFunc(ScreenResizer);
}
void MyNewKeyboardFunc(unsigned char Key, int x, int y)
{
switch (Key) {
       case 'w': {
          if(mainmenu==1 && yesOrNo!=1){if (mainStack>0) {  mainStack--; } }
          else if (islevel==1) { if (levelStack>0) { levelStack--;} }
          else if(isPause==1 && yesOrNo==0) { if(pauseStack>0) {pauseStack--;} }
          else if(isPause==1 && yesOrNo==1) { if(ynStack>0) {ynStack--;} }
          else if(yesOrNo==1)  { if(ynStack>0) {ynStack--;} }
          else if(gameOver==1 && yesOrNo==0) { if(gameOverStack>0) {gameOverStack--;} }
          break;
       }
       case 's': {
          if(mainmenu==1 && yesOrNo!=1) { if (mainStack<2) { mainStack++;   }   }
          else if(islevel==1) { if (levelStack<2) { levelStack++;} }
          else if(isPause==1 && yesOrNo==0) { if(pauseStack<1) {pauseStack++;} }
          else if(isPause==1 && yesOrNo==1) { if(ynStack<1) {ynStack++;} }
          else if(yesOrNo==1) { if(ynStack<1) {ynStack++;}}
          else if(gameOver==1 && yesOrNo==0) { if(gameOverStack<1) {gameOverStack++;} }
          break;
       }
       case 13: {
           if(mainmenu==1 && yesOrNo!=1)
           {
          if (mainStack==0) { mainmenu=0; islevel=1;}
          if (mainStack==1) { mainmenu=0; helpmenu=1; }
          if (mainStack==2) { ynStack=0; yesOrNo=1; }
           }
           else if(islevel==1)
           {
             if (levelStack==0) { hardness=0; islevel=0; isPlaying=1; installSnake();}
             if (levelStack==1) { hardness=1; islevel=0; isPlaying=1; installSnake();}
             if (levelStack==2) { hardness=2; islevel=0; isPlaying=1; installSnake();}
           }
           else if(isPause==1 && yesOrNo==0)
           {
                if(pauseStack==0) { isPause=0; yesOrNo=0; isPlaying=1; resumeSnake();}
                if(pauseStack==1) {yesOrNo=1; }
           }
           else if(isPause==1 && yesOrNo==1)
           {
               if(ynStack==0) { yesOrNo=0; isPause=0; mainmenu=1; }
               else if(ynStack==1) { yesOrNo=0; isPause=1;}
           }
           else if(mainmenu==1 && yesOrNo==1)
           {
               if(ynStack==0) exit(0);
               else if(ynStack==1) { yesOrNo=0; }
           }
           else if(gameOver==1)
           {
               if(gameOverStack==0) { yesOrNo=0; gameOver=0; isPlaying=1; installSnake(); }
               else if(gameOverStack==1) { yesOrNo=0; exit(0);}
           }

          break;
       }
       case 27: {
           if(isPlaying==1)
           {
               isPlaying=0;
               isPause=1;
                glutDisplayFunc(printText);
                glutReshapeFunc(ScreenResizer);
                glutKeyboardFunc(MyNewKeyboardFunc);
           }
          else yesOrNo=1;
          break;
       }
    };
}


void loopMain()
{
    if(isPlaying!=1)
    {
        glutDisplayFunc(printText);
        glutReshapeFunc(ScreenResizer);
        glutKeyboardFunc(MyNewKeyboardFunc);
        // glutKeyboardFunc(MyKeyboardFunc);     // For ESC and other normal keys
        // glutSpecialFunc(MySpecialFunc);       // For arrow keys


    }
    else  if( gameOver!=1) MoveSnake();


    glutPostRedisplay();
}

int main(int argc, char **argv)
{    srand (time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(750,750);
    // glutInitWindowPosition(220,220);
    glutCreateWindow("The binary bunch");
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(printText);
    glutReshapeFunc(ScreenResizer);
    glutIdleFunc(loopMain);
    glutMainLoop();
    return EXIT_SUCCESS;
}

