/*
 *  magicdraw.cpp
 *    2017.10.31  Takata
 *    Special thanks to Nakamura
 */

/* include files */
#include "DxLib.h"
#include <math.h>

/* define */
#define WindowX 600
#define WindowY 200
#define Thickness 1

/* global variables */
const double PI = 3.14159265;
int MouseX, MouseY;
int MouseX_old, MouseY_old;
int charSize = 200;
int spaceSize = 100;
int length_hen = 80;
int OX = 60, OY = 20;
unsigned int Cr;
unsigned int RED;

/* function */
void Convert1( double *length, double *angle );
void Convert2( double length, double angle, int &x, int &y );
void getPoint( int *x, int *y, int times, int devid, double length, double angle );
void DrawDebug();
void draw_1_ta( double length, double angle, bool flag );
void draw_2_ka( double length, double angle, bool flag );
void draw_3_ta( double length, double angle, bool flag );

/* main */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  double length, angle;
  RED = GetColor( 255, 0, 0 );

  SetGraphMode( WindowX , WindowY , 32 );
  ChangeWindowMode( TRUE );

  if( DxLib_Init() == -1 ){ return -1; }

  SetDrawScreen( DX_SCREEN_BACK );
  GetMousePoint( &MouseX, &MouseY );
  Convert1( &length, &angle );

  while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
  {
    // Color
    Cr = GetColor( rand() % 256, rand() % 256, rand() % 256 );

    // Mouse
    MouseX_old = MouseX;
    MouseY_old = MouseY;
    GetMousePoint( &MouseX, &MouseY );

    // Convert1
    Convert1( &length, &angle );

    // Draw
    //DrawDebug();
    DrawLine( 70, 20, 70 - length_hen / sqrt( 2.0 ), 100, RED );
    if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 )
    {
      DrawLine( MouseX_old, MouseY_old, MouseX, MouseY, Cr, Thickness );
      draw_1_ta( length, angle, true );
      draw_2_ka( length, angle, true );
      draw_3_ta( length, angle, true );
    }
    else
    {
      draw_1_ta( length, angle, false );
      draw_2_ka( length, angle, false );
      draw_3_ta( length, angle, false );
    }

    // Refresh
    if( CheckHitKey(KEY_INPUT_SPACE) == 1 ){ ClearDrawScreen(); }

    // Display
    ScreenFlip();
  }

  DxLib_End();

  return 0;
}

/* comversion( Rect -> Pol ) */
void Convert1( double *length, double *angle )
{
  double x = (double)MouseX - (double)OX;
  double y = (double)MouseY - (double)OY;
  *length = sqrt( x * x + y * y );
  *angle  = atan2( y, x );
}

/* conversion( Pol -> Rect ) */
void Convert2( double length, double angle, int *x, int *y )
{
  *x =  length * cos( angle );
  *y = -length * sin( angle );
}

/* get rect-position */
void getPoint( int *x, int *y, int times, int devid, double length, double angle )
{
  angle += PI * times / devid;
  Convert2( length, angle, x, y );
}

/* for adjustment */
void DrawDebug()
{
  DrawLine( charSize,     0, charSize,     WindowY, RED );
  DrawLine( charSize * 2, 0, charSize * 2, WindowY, RED );
}

/* draw Ta(1) */
void draw_1_ta( double length, double angle, bool flag )
{
  static const int stroke = 4;
  int x[stroke], y[stroke];
  static int x_old[stroke] = {0}, y_old[stroke] = {0};
  static bool drawflag = false;
  int i;
  if( !flag )
  {
    drawflag = false;
    return;
  }

  getPoint( &x[0], &y[0], -3, 4, length, angle );
  x[0] += 80; y[0] += 20;
  getPoint( &x[1], &y[1], 3, 5, length, angle );
  x[1] += 180; y[1] += 50;
  getPoint( &x[2], &y[2], 3, 5, length, angle );
  x[2] += 130; y[2] += 120;
  getPoint( &x[3], &y[3], -3, 4, length, angle );
  x[3] += 40; y[3] += 70;

  if( drawflag )
  {
    for( i = 0; i < stroke; i++ )
    {
      DrawLine( x_old[i], y_old[i], x[i], y[i], Cr, Thickness );
    }
  }
  for( i = 0; i < stroke; i++ )
  {
    x_old[i] = x[i];
    y_old[i] = y[i];
  }
  drawflag = true;
}

/* draw Ka(2) */
void draw_2_ka( double length, double angle, bool flag )
{
  static const int stroke = 4;
  int x[stroke], y[stroke];
  static int x_old[stroke] = {0}, y_old[stroke] = {0};
  static bool drawflag = false;
  int i;
  if( !flag )
  {
    drawflag = false;
    return;
  }

  getPoint( &x[0], &y[0], -11, 16, length, angle );
  x[0] += 250; y[0] += 70;
  getPoint( &x[1], &y[1], 7, 10, length, angle );
  x[1] += 350; y[1] += 80;
  getPoint( &x[2], &y[2], 7, 10, length, angle );
  x[2] += 310; y[2] += 20;
  getPoint( &x[3], &y[3], 7, 10, length, angle );
  x[3] += 290; y[3] += 80;
 

  if( drawflag )
  {
    for( i = 0; i < stroke; i++ )
    {
      DrawLine( x_old[i], y_old[i], x[i], y[i], Cr, Thickness );
    }
  }
  for( i = 0; i < stroke; i++ )
  {
    x_old[i] = x[i];
    y_old[i] = y[i];
  }
  drawflag = true;
}

/* draw Ta(3) */
void draw_3_ta( double length, double angle, bool flag )
{
  static const int stroke = 5;
  int x[stroke], y[stroke];
  static int x_old[stroke] = {0}, y_old[stroke] = {0};
  static bool drawflag = false;
  int i;
  if( !flag )
  {
    drawflag = false;
    return;
  }

  getPoint( &x[0], &y[0], 3, 5, length, angle );
  x[0] += 480; y[0] += 30;
  getPoint( &x[1], &y[1], -3, 4, length, angle );
  x[1] += 480; y[1] += 20;
  getPoint( &x[2], &y[2], 3, 5, length, angle );
  x[2] += 580; y[2] += 50;
  getPoint( &x[3], &y[3], 3, 5, length, angle );
  x[3] += 530; y[3] += 120;
  getPoint( &x[4], &y[4], -3, 4, length, angle );
  x[4] += 440; y[4] += 70;

  if( drawflag )
  {
    for( i = 0; i < stroke; i++ )
    {
      DrawLine( x_old[i], y_old[i], x[i], y[i], Cr, Thickness );
    }
  }
  for( i = 0; i < stroke; i++ )
  {
    x_old[i] = x[i];
    y_old[i] = y[i];
  }
  drawflag = true;
}
