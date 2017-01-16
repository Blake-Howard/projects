/***********************************************
 *
 * Filename: main.c
 * Description: Uses the uart, gyro, and led on stm32 to create a visual 
 *  application for the gyro. Displaying the intensity of the gyro in 
 *  dgps on the led compass and on screen with screen(or serialT). Allows user to change
 *  axis being monitored with button or typing. 
 * Author: Blake Howard (Bahoward), Di Zhong (dizhong)
 * Created: October 5th, 2015
 * Last-Updated: 10/15/2015
 * Update by: Blake Howard
 * Update #: 11
 */

//included packages
#include <f3d_uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>
#include <stm32f30x.h>

//proto-type fucntions 
int newgetchar();
void init_all();
void delay();
void set_buf();
int btn_cycle();
int char_choose();
void print_gyro_info(float, int);
void light_up(float, int);

//main
int main(void){
 
  //initializing and defining buffer stream
  init_all();
  set_buf();

  //variable intialization 
  int axis, btn_press;
  float buffer[3];
  //default axis
  axis = 0;

  while(1){

    f3d_led_all_off();
    //receive data from gyro, fill buffer
    f3d_gyro_getdata(buffer);
    //decide if button is pressed
    btn_press = user_btn_read();
    //cycle button if button pressed
    axis = btn_cycle(btn_press, axis);
    //change axis with choosing a character
    axis = char_choose(axis);
    //print information to user
    print_gyro_info(buffer[axis], axis);
    //turn on led lights
    light_up(buffer[axis], axis);
    //delay to make more readable
    delay();
  }
}

//a function that recieves dgps (degrees per second) from the gyro
//and the axis for which to light leds 
void light_up(float info, int axis){
  int led = 0;
  int num = 50;
  
  //if negative, increase threshold and turn on lights sequentially
  if (info < -5){
    f3d_led_on(0);
    for (led = 1; led < 5; led++){
      if (info < num*-1)
	f3d_led_on(led);
      num += 50;
    }
  }

  //reset threshold 
  num = 50;
  
  //if positive increase threshold, light up leds 
  if (info > 5){
    f3d_led_on(0);
    for (led = 7; led > 3; led--){
      if (info > num)
	f3d_led_on(led);
      num += 50;
    }
  }
}

//a fucntion that chooses which labels to use for printing
void print_gyro_info(float info, int  axis){

  switch(axis){

  case 0:
    printf("Axis X: ");
    break;

  case 1:
    printf("Axis Y: ");
    break;

  case 2:
    printf("Axis Z: ");
    break;
  }
  printf("%f \n", info);
}

//A function that sees if a character is being sent in
//if so, change axis and return axis, if not
//return previous axis
int char_choose(axis){
  char c = 0;
  c = newgetchar();
  if (c != 0){
    switch(c){
    case 'x':
      axis = 0;
      return axis;
      break;

    case 'y':
      axis = 1;
      return axis;
      break;

    case 'z':
      axis = 2;
      return axis;
      break;
    default:
      printf("Enter x, y, or z\n\n");      
    }//switch
  }//if
  return axis;
}

//A fucntion to change the axis when the button is pressed
//returns current axis if button isn't pressed
int btn_cycle(int num, int axis){

  if (num){
    axis++;
    if (axis > 2){
      return 0;
    }
  }  
  return axis;
}

//define buffer streams
void set_buf(){
  setvbuf(stdin, NULL, _IONBF,0);
  setvbuf(stdout, NULL, _IONBF,0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

//set delay for application
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

//a get character function that will be passed over if a character
//isn't given 
int newgetchar(void) {
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET)
    return USART_ReceiveData(USART1);
  return 0;
}

//initialize all of the things we're using
//gyro, uart, led, user button
void init_all(){

  f3d_gyro_init();
  f3d_user_btn_init();
  f3d_led_init();
  f3d_uart_init();

}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}



