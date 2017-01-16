/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log: #3 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_uart.h>
#include <f3d_lcd_sd.h>
#include <f3d_user_btn.h>
#include <stdio.h>
#include <math.h>
#include <f3d_i2c.h>
#include <f3d_mag.h>
#include <f3d_accel.h>  // Pull in include files for F30x standard drivers 
#define PI (3.141592653589793)
#define TIMER 20000


//Function to draw a filled in circle
//Fills in the circle from left to right
void drawCirc(uint8_t xCent, uint8_t yCent, int radius, uint16_t color){
  int x, y, r2, a;
  r2 = radius * radius;
  
  for (x = -radius; x <= radius; x++)
    {
      //Math equation for a circle
      y = (int)(sqrt(r2 - x*x) + .5);
      for (a = yCent-y; a < yCent+y; a++){
	f3d_lcd_drawPixel(xCent + x, a, color);
      }
    }
}


//Draws a hallow circle, or just the outline of a circle
//Draw circumfrence from left to right
void drawCirc2(uint8_t xCent, uint8_t yCent, int radius, uint16_t color){
  int x, y, r2, a;
  r2 = radius * radius;
  
  for (x = -radius; x <= radius; x++)
    {
      //Math equation for a circle
      y = (int)(sqrt(r2 - x*x) + .5);
      f3d_lcd_drawPixel(xCent + x, yCent +y, color);
      f3d_lcd_drawPixel(xCent + x, yCent -y, color);
      f3d_lcd_drawPixel(xCent + x, yCent +y-1, color);
      f3d_lcd_drawPixel(xCent + x, yCent -y+1, color);
    }
}

//Draws a filled in circle on the edge of another circle
void innerCircCirc(uint8_t xCent, uint8_t yCent, int radius, uint16_t color, double heading)
{

  //heading orientation correction
  heading -= PI/2;
  //math formulas to locate a point on the circumference
  int x = (int)(xCent + (radius*cos(heading)));
  int y = (int)(yCent + (radius*sin(heading)));
  drawCirc(x, y , 5, color);
}


/* Currently not functional. The idea is to use the equations for 
   finding a point on the circumference and the origin of the circle
   to find a slope, m. Then use slope-point formula to create a lower
   bound, and the formula for a circle to create a upper bound to be
   filled.*/
void fillSlice(uint8_t xCent, uint8_t yCent, int radius, uint16_t color, double heading)
{
  int x, yb,yt, r2, a;
  r2 = radius * radius;
  double m, heading2;
  //Heading correction and conversion to radians
  heading2 = (heading*(PI/180)) - PI/2;
  //Points on the cirlce edge
  int cumfrence_x = (int)(xCent + (radius*cos(heading2)));
  int cumfrence_y = (int)(yCent + (radius*sin(heading2)));
  if ((heading >= 0) && (heading <= 90)){
    for (x = xCent; x <= cumfrence_x ; x++){
      // Slope for points and origin, yb(Y bottom bound), yt(y top bound)
      m = ((cumfrence_y - yCent)/(cumfrence_x - xCent));
      yb = (int)(m*((x - xCent) + yCent));
      yt = (int)(sqrt(r2 - x*x) + .5);
      for (a = yb; a < yt; a++){
	f3d_lcd_drawPixel(xCent + x, a, color);
      }
    }
  }
}
int main(void) {

  //initialization
  f3d_lcd_init();
  f3d_user_btn_init();
  f3d_uart_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  int size = 10;
  f3d_lcd_fillScreen(BLACK);
  char a[size],b[size],c[size],d[size],e[size],f[size];
  float accel[3], mag[3], zaccel, yaccel;
  double pitch, roll, headx, heady, heading;
  int x = 6;
  int y = 59;
  int z = 112;

  while (1){
    f3d_accel_read(accel);
    f3d_mag_read(mag);
    //Variables and calculation pitch and roll
    zaccel = accel[2];
    yaccel = accel[1];
    pitch = (double)(atan(accel[0]/sqrt((double)((yaccel*yaccel)+(zaccel*zaccel)))));
    roll = (double)(atan(yaccel/sqrt((double)((accel[0]*accel[0])+(zaccel*zaccel)))));

    //calculation heading with roll correction
    //I noticed that we do indeed correct for one of these, but
    //not the other. I believe pitch still changes our heading.
    headx = (double)(mag[0]*cos(pitch) + mag[2]*sin(pitch));
    heady = (double)(mag[0]*sin(roll)*sin(pitch) + mag[1]*cos(roll) - mag[2]*sin(roll)*cos(pitch));
    //heading = (double)(atan2(mag[1],mag[0])*(180/PI));

    //conversion to degrees
    heading =(double)(atan2(heady,headx)*(180/PI));
 
    //heading corrections to make the heading easier to work with
    if (heading < 0){      
      heading = 180 - fabs(heading);
      heading += 180;
    }

    heading += 180;

    if (heading >= 360) {
      heading = heading - 360;
    }

    double heading_rad = heading*(PI/180);

    sprintf(a, "P: %05.2f", pitch);
    sprintf(b, "R: %05.2f", roll);
    sprintf(c, "H: %07.2f", heading);

    sprintf(d, "HR: %07.2f", heading_rad);
    sprintf(e, "Y: %07.2f", mag[1]);
    sprintf(f, "Z: %07.2f", mag[2]);
    
    //drawing compass
    drawCirc2(64, 80, 30, RED);
    innerCircCirc(64, 80, 20, CYAN, heading_rad);
    delay(1);
    innerCircCirc(64, 80, 20, BLACK, heading_rad);
    
    //testing fillslice
    fillSlice(64, 80, 30, RED, 45.0);

    //f3d_lcd_drawString(4, x-6, c, WHITE, BLACK);
    //f3d_lcd_drawString(4, z-6, d, WHITE, BLACK);
    /*f3d_lcd_drawString(4, z-6, c, WHITE, BLACK);

    f3d_lcd_drawString(4, x+6, d, WHITE, BLACK);
    f3d_lcd_drawString(4, y+6, e, WHITE, BLACK);
    f3d_lcd_drawString(4, z+6, f, WHITE, BLACK);*/
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif


/* main.c ends here */
