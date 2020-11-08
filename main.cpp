#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAME_SPEED 400
#define BLACK	     0
#define RED	     1
#define GREEN	     2
#define BLUE	     3
#define YELLOW	     4
#define ORANGE	     5
#define PURPLE      6
#define MAGENTA     7
#define UP          -1
#define LEFT        0
#define DOWN        1
#define RIGHT       2

void Restart();

bool pause = false;
GLbyte Map[10][20];
struct Thing
{
	GLbyte data[4][4];
	GLbyte x, y;
     GLbyte type, pos;
};

struct Thing Piece;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);	
}

void SelectColor( GLbyte color )
{
     switch( color )
     {
          case RED:
               glColor3f( 1.0, 0.0, 0.0 );
          break;

          case GREEN:
               glColor3f( 0.0, 1.0, 0.0 );
          break;

          case BLUE:
               glColor3f( 0.0, 0.0, 1.0 );
          break;

          case YELLOW:
               glColor3f( 1.0, 1.0, 0.0 );
          break;

          case ORANGE:
               glColor3f( 0.98, 0.625, 0.12 );
          break;

          case PURPLE:
               glColor3f( 0.60, 0.40, 0.70 );
          break;

          case MAGENTA:
               glColor3f( 1.0, 0, 1.0 );
          break;

          default:
               glColor3f( 0.0, 0.0, 0.0 );
          break;
     }
}

void RenderScene(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	glBegin (GL_LINES);
		glColor3f(0.5, 0.5, 0.5);
		for ( GLfloat pos = -0.9; pos < 1.0; pos += 0.1 )
		{
			glVertex3f(-1.0, pos, 0);
			glVertex3f(0.0, pos, 0);
		}
		for ( GLfloat pos = -0.9; pos < 0.1; pos += 0.1 )
		{
			glVertex3f(pos, -1.0, 0);
			glVertex3f(pos, 1.0, 0);
		}
	glEnd();

	glBegin (GL_QUADS);
          for ( int y = 0; y < 4; y++ )
          {
	          for ( int x = 0; x < 4; x++ )
	          {
				if ( Piece.data[x][y] == BLACK )
                    {
                         continue;
                    }
                    SelectColor( Piece.data[x][y] );
				glVertex3f( (((float)(Piece.x+x)/10)-1), (((float)(Piece.y+y)/10)-1), 0);
				glVertex3f( (((float)(Piece.x+x)/10)-1), ((((float)(Piece.y+y)+1)/10)-1), 0);
				glVertex3f( ((((float)(Piece.x+x)+1)/10)-1), ((((float)(Piece.y+y)+1)/10)-1), 0);
				glVertex3f( ((((float)(Piece.x+x)+1)/10)-1), (((float)(Piece.y+y)/10)-1), 0);
	          }
          }
		for ( int x = 0; x < 10; x++ )
		{
			for ( int y = 0; y < 20; y++ )
			{
				SelectColor( Map[x][y] );
				glVertex3f( (((float)x/10)-1), (((float)y/10)-1), 0);
				glVertex3f( (((float)x/10)-1), ((((float)y+1)/10)-1), 0);
				glVertex3f( ((((float)x+1)/10)-1), ((((float)y+1)/10)-1), 0);
				glVertex3f( ((((float)x+1)/10)-1), (((float)y/10)-1), 0);
			}
		}
		glColor3f(.75, .75, .75);
		glVertex3f(0.0, -1.0, 0);
		glVertex3f(0.0, 1.0, 0);
		glVertex3f(1.0, 1.0, 0);
		glVertex3f(1.0, -1.0, 0);
	glEnd();

	glutSwapBuffers();
}

void Rotate( int direction )
{
     if ( Piece.type == 0 )
     {
          return;
     }
     else
     {
          for ( int y = 0; y < 4; y++ )
          {
	          for ( int x = 0; x < 4; x++ )
	          {
		          Piece.data[x][y] = BLACK;
	          }
          }
          if ( Piece.type == 1 )
          {
               if ( Piece.pos == 1 )
               {
                    Piece.pos++;
                    Piece.data[2][0] = GREEN;
                    Piece.data[1][1] = GREEN;Piece.data[2][1] = GREEN;
                    Piece.data[1][2] = GREEN;
               }
               else
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    Piece.pos--;
                    Piece.data[0][0] = GREEN;Piece.data[1][0] = GREEN;
			     Piece.data[1][1] = GREEN;Piece.data[2][1] = GREEN;
               }
          }
          else if ( Piece.type == 2 )
          {
               if ( Piece.pos == 1 )
               {
                    Piece.pos++;
                    Piece.data[1][0] = BLUE;
                    Piece.data[1][1] = BLUE;Piece.data[2][1] = BLUE;
                    Piece.data[2][2] = BLUE;
               }
               else
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    Piece.pos--;
                    Piece.data[1][0] = BLUE;Piece.data[2][0] = BLUE;
		          Piece.data[0][1] = BLUE;Piece.data[1][1] = BLUE;
               }
          }
          else if ( Piece.type == 3 )
          {
               Piece.pos += direction;
               if ( Piece.pos < 1 )
               {
                    Piece.pos = 4;
               }
               else if ( Piece.pos > 4 )
               {
                    Piece.pos = 1;
               }
               
               printf("Pos: %d     x: %d\n", Piece.pos, Piece.x );

               if ( Piece.pos == 1 )
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
                    Piece.data[0][0] = YELLOW;
			     Piece.data[0][1] = YELLOW;Piece.data[1][1] = YELLOW;Piece.data[2][1] = YELLOW;
               }
               else if ( Piece.pos == 2 )
               {
                    Piece.data[1][0] = YELLOW;Piece.data[2][0] = YELLOW;
		          Piece.data[1][1] = YELLOW;
                    Piece.data[1][2] = YELLOW;
               }
               else if ( Piece.pos == 3 )
               {
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    Piece.data[0][1] = YELLOW;Piece.data[1][1] = YELLOW;Piece.data[2][1] = YELLOW;
                    Piece.data[2][2] = YELLOW;
               }
               else if ( Piece.pos == 4 )
               {
                    Piece.data[0][2] = YELLOW;
                    Piece.data[1][0] = YELLOW;Piece.data[1][1] = YELLOW;Piece.data[1][2] = YELLOW;
               }
          }
          else if ( Piece.type == 4 )
          {
               Piece.pos += direction;
               if ( Piece.pos < 1 )
               {
                    Piece.pos = 4;
               }
               else if ( Piece.pos > 4 )
               {
                    Piece.pos = 1;
               }
               if ( Piece.pos == 1 )
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
			     Piece.data[2][0] = ORANGE;
			     Piece.data[0][1] = ORANGE;Piece.data[1][1] = ORANGE;Piece.data[2][1] = ORANGE;
               }
               else if ( Piece.pos == 2 )
               {
                    Piece.data[1][0] = ORANGE;
		          Piece.data[1][1] = ORANGE;
                    Piece.data[1][2] = ORANGE;Piece.data[2][2] = ORANGE;
               }
               else if ( Piece.pos == 3 )
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
                    Piece.data[0][1] = ORANGE;Piece.data[1][1] = ORANGE;Piece.data[2][1] = ORANGE;
                    Piece.data[0][2] = ORANGE;
               }
               else if ( Piece.pos == 4 )
               {
                    Piece.data[0][0] = ORANGE;
                    Piece.data[1][0] = ORANGE;Piece.data[1][1] = ORANGE;Piece.data[1][2] = ORANGE;
               }
          }
          else if ( Piece.type == 5 )
          {
               Piece.pos += direction;
               if ( Piece.pos < 1 )
               {
                    Piece.pos = 4;
               }
               else if ( Piece.pos > 4 )
               {
                    Piece.pos = 1;
               }

               if ( Piece.pos == 1 )
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
			     Piece.data[1][0] = PURPLE;
			     Piece.data[0][1] = PURPLE;Piece.data[1][1] = PURPLE;Piece.data[2][1] = PURPLE;
               }
               else if ( Piece.pos == 2 )
               {
                    Piece.data[1][0] = PURPLE;
		          Piece.data[1][1] = PURPLE;Piece.data[2][1] = PURPLE;
                    Piece.data[1][2] = PURPLE;
               }
               else if ( Piece.pos == 3 )
               {
                    if ( Piece.x == -1 )
                    {
                         Piece.x++;
                    }
                    if ( Piece.x == 8 )
                    {
                         Piece.x--;
                    }
                    Piece.data[0][1] = PURPLE;Piece.data[1][1] = PURPLE;Piece.data[2][1] = PURPLE;
                    Piece.data[1][2] = PURPLE;
               }
               else if ( Piece.pos == 4 )
               {
                    Piece.data[0][1] = PURPLE;
                    Piece.data[1][0] = PURPLE;Piece.data[1][1] = PURPLE;Piece.data[1][2] = PURPLE;
               }
          }
          else if ( Piece.type == 6 )
          {
               if ( Piece.pos == 1 )
               {
                    if ( Piece.x > 6 )
                    {
                         Piece.x = 6;
                    }
                    if ( Piece.x == -1 )
                    {
                         Piece.x = 0;
                    }
                    Piece.pos++;
                    Piece.data[0][2] = MAGENTA;Piece.data[1][2] = MAGENTA;Piece.data[2][2] = MAGENTA;Piece.data[3][2] = MAGENTA;
               }
               else
               {
                    Piece.pos--;
                    Piece.data[1][0] = MAGENTA;Piece.data[1][1] = MAGENTA;Piece.data[1][2] = MAGENTA;Piece.data[1][3] = MAGENTA;
               }
          }
          RenderScene();
     }
}

void Removeline( int line )
{
     for ( int y = line; y < 19; y++ )
     {
          for ( int x = 0; x < 10; x++ )
          {
               Map[x][y] = Map[x][y+1];
               if ( y == 18 )
               {
                    Map[x][y+1] = BLACK;
               }
          }
     }
}

void createPiece()
{
     for ( int y = Piece.y; y < Piece.y+4; y++ )
     {
          if ( Map[0][y] != BLACK && Map[1][y] != BLACK && Map[2][y] != BLACK && Map[3][y] != BLACK && Map[4][y] != BLACK &&
               Map[5][y] != BLACK && Map[6][y] != BLACK && Map[7][y] != BLACK && Map[8][y] != BLACK && Map[9][y] != BLACK )
          {
               Removeline( y );
               y--;
          }
     }
     for ( int y = 0; y < 4; y++ )
     {
	     for ( int x = 0; x < 4; x++ )
	     {
		     Piece.data[x][y] = BLACK;
	     }
     }
     Piece.x = 4;
	Piece.y = 16;
     Piece.pos = 1;

     if ( Map[4][16] != BLACK )
     {
          Restart();
          return;
     }
	Piece.type = rand() % 7;
     //Piece.type = 4;
	switch ( Piece.type )
	{
		case 0: // Square
			Piece.data[0][0] = RED;Piece.data[1][0] = RED;
			Piece.data[0][1] = RED;Piece.data[1][1] = RED;
		break;
		case 1: // S
			Piece.data[0][0] = GREEN;Piece.data[1][0] = GREEN;
			Piece.data[1][1] = GREEN;Piece.data[2][1] = GREEN;
		break;
          case 2: // Z
			Piece.data[1][0] = BLUE;Piece.data[2][0] = BLUE;
		     Piece.data[0][1] = BLUE;Piece.data[1][1] = BLUE;
		break;
		case 3: // L
			Piece.data[0][0] = YELLOW;
			Piece.data[0][1] = YELLOW;Piece.data[1][1] = YELLOW;Piece.data[2][1] = YELLOW;
		break;
		case 4: // J
			Piece.data[2][0] = ORANGE;
			Piece.data[0][1] = ORANGE;Piece.data[1][1] = ORANGE;Piece.data[2][1] = ORANGE;
		break;
		case 5: // T
			Piece.data[1][0] = PURPLE;
			Piece.data[0][1] = PURPLE;Piece.data[1][1] = PURPLE;Piece.data[2][1] = PURPLE;
		break;
		case 6: // I
               Piece.x = 5;
			Piece.data[1][0] = MAGENTA;Piece.data[1][1] = MAGENTA;Piece.data[1][2] = MAGENTA;Piece.data[1][3] = MAGENTA;
		break;
          case 7: // Test dot
               Piece.data[0][0] = PURPLE;
          break;
	}
}

void Restart()
{
	for ( int y = 0; y < 20; y++ )
	{
		for ( int x = 0; x < 10; x++ )
		{
			Map[x][y] = 0;
		}
	}

	createPiece();
}

bool CanMove ( int direction )
{
     bool result = false;

     if ( direction == LEFT )
     {
          if ( Piece.type != 6 )
          {
               if ( Piece.pos == 2 && Piece.x == -1 || Piece.pos != 2 && Piece.x == 0 )
               {
                    return false;
               }
               return true;
          }
          else // Piece 6 ( I )
          {
               if ( Piece.pos == 1 && Piece.x == -1 || Piece.pos == 2 && Piece.x == 0 )
               {
                    return false;
               }
          }
          if ( Map[Piece.x-1][Piece.y] == BLACK && Map[Piece.x-1][Piece.y+1] == BLACK && Map[Piece.x-1][Piece.y+2] == BLACK && Map[Piece.x-1][Piece.y+3] == BLACK )
          {
               return true;
          }
          return false;
     }
     else if ( direction == DOWN )
     {
          if ( Piece.y < 1 )
          {
               if ( ( Piece.type == 3 || Piece.type == 4 || Piece.type == 5) && Piece.pos == 3 && Piece.y == 0 )
               {
                    return true;
               }
               if ( Piece.type == 6 && Piece.pos == 2 && Piece.y > -2 )
               {
                    return true;
               }
               return false;
          }
          else if ( Piece.type == 6 && Piece.pos == 2 )
          {
               if ( Map[Piece.x][Piece.y+1] != BLACK || Map[Piece.x+1][Piece.y+1] != BLACK || Map[Piece.x+2][Piece.y+1] != BLACK || Map[Piece.x+3][Piece.y+1] != BLACK )
               {
                    return false;
               }
          }
          else if ( Piece.type == 3 && Piece.pos == 4 )
          {
               if ( Map[Piece.x][Piece.y-1] == BLACK && Map[Piece.x][Piece.y] == BLACK && Map[Piece.x][Piece.y+1] == BLACK )
               {
                    return true;
               }
               else if ( Map[Piece.x][Piece.y+1] != BLACK && Piece.data[0][2] != BLACK )
               {
                    return false;
               }
          }
          else if ( Piece.type == 3 && Piece.pos == 3 )
          {
               if ( Map[Piece.x][Piece.y] != BLACK || Map[Piece.x+1][Piece.y] != BLACK || Map[Piece.x+2][Piece.y] != BLACK )
               {
                    return false;
               }
               else
               {
                    return true;
               }
          }
          else if ( Piece.type == 4 && Piece.pos == 2 )
          {
               if ( Map[Piece.x+1][Piece.y-1] != BLACK || Map[Piece.x+2][Piece.y+1] != BLACK )
               {
                    return false;
               }
               else
               {
                    return true;
               }
          }
          if ( Map[Piece.x][Piece.y-1] == BLACK && Map[Piece.x+1][Piece.y-1] == BLACK && Map[Piece.x+2][Piece.y-1] == BLACK && Map[Piece.x+3][Piece.y-1] == BLACK )
          {
               return true;
          }
          for ( int x = 0; x < 4; x++ )
          {
               if ( Piece.data[x][0] != BLACK && Map[Piece.x+x][Piece.y-1] != BLACK )
               {
                    return false;
               }
               if ( Piece.data[x][1] != BLACK && Piece.data[x][0] == BLACK && Map[Piece.x+x][Piece.y] != BLACK )
               {
                    return false;
               }
          }
          return true;
     }
     else if ( direction == RIGHT )
     {
          if ( Piece.type >= 3 && Piece.type <= 5 )
          {
               if ( Piece.pos == 4 && Piece.x == 8 )
               {
                    return false;
               }
               else if ( Piece.pos != 4  && Piece.x == 7 )
               {
                    return false;
               }
               return true;
          }
          else if ( Piece.type == 6 || Piece.type == 0 )
          {
               if ( Piece.pos == 1 && Piece.x == 8 )
               {
                    return false;
               }
               if ( Piece.pos == 2 && Piece.x == 6 )
               {
                    return false;
               }
               return true;
          }
          else
          {
               if ( Piece.x == 7 )
               {
                    return false;
               }
               if ( Map[Piece.x+1][Piece.y] == BLACK && Map[Piece.x+1][Piece.y+1] == BLACK && Map[Piece.x+1][Piece.y+2] == BLACK && Map[Piece.x+1][Piece.y+3] == BLACK )
               {
                    return true;
               }
          }
          return false;
     }

     return false;
}

void keyPressed(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q':
		case 27 : // Esc
			exit(1);
		break;
          case 'p':
          case 'P':
               pause = !pause;
          break;
          case 'r':
          case 'R':
               Restart();
          break;
          case 32: // Space
               if ( CanMove(DOWN) )
               {
                    Piece.y--;
                    RenderScene();
               }
          break;
		default:
               //printf( "Unknow Key: %d", key );
		break;
	}
}

void SpecialKeys(int key, int x, int y)
{  
	switch(key)
	{
		case GLUT_KEY_LEFT:
			if ( CanMove(LEFT) )
			{	
				Piece.x--;
                    RenderScene();
			}
		break;
		case GLUT_KEY_RIGHT:
			if ( CanMove(RIGHT) )
			{	
				Piece.x++;
                    RenderScene();
			}
		break;
          case GLUT_KEY_UP:
               Rotate(UP);
          break;
          case GLUT_KEY_DOWN:
               Rotate(DOWN);
          break;
          
          case GLUT_KEY_END:
               pause = !pause;
          break;
		default:
               //printf( "Unknow Special Key: %d", key );
		break;
	}
}

void MovePiece ( int value )
{
     if ( !CanMove(DOWN) )
     {
	     for ( int y = 0; y < 4; y++ )
	     {
		     for ( int x = 0; x < 4; x++ )
		     {
			     if ( Piece.data[x][y] != BLACK )
                    {
                         Map[Piece.x+x][Piece.y+y] = Piece.data[x][y];
                    }
		     }
	     }
          createPiece();
     }
     else
     {
          Piece.y--;
     }

     RenderScene();
	glutTimerFunc(GAME_SPEED,MovePiece, 1);
     if ( pause )
     {
          system ( "CLS" );
          for ( int y = 20; y > 0; y-- )
          {
               for ( int x = 0; x < 10; x++ )
               {
                    printf ( "%d ", Map[x][y] );
               }
               puts ("");
          }
          printf (" %d, %d ", Piece.x , Piece.y);
          system ( "PAUSE" );
     }
}

int main(int argc, char** argv)
{
     #ifndef _DEBUG
          FreeConsole();
     #endif
	srand ( time(NULL) );
	for ( int y = 0; y < 20; y++ )
	{
		for ( int x = 0; x < 10; x++ )
		{
			Map[x][y] = 0;
		}
	}

	createPiece();

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (250, 200); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Tetris");
	init ();
	glutTimerFunc(GAME_SPEED,MovePiece, 1);
	glutDisplayFunc(RenderScene); 
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(SpecialKeys);

	glutMainLoop();
	return 0;
}