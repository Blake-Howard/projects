int main (void){

setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int axis, use_button, a, b, led;
  float buffer[size] = {24.6, 243.46, 234234.345};
  char to_print[10];
  char *flprint ="%f\n\n";

  axis = 0;
  use_button = 0;

  while(1){
    //f3d_gyro_getdata(buffer);
    int c = getchar();
  
    printf( "%f ", buffer[0]);
    printf( "%f ", buffer[1]);
    printf( "%f \n\n", buffer[2]);
    delay();
    

    
    if (user_btn_read()){
      if (use_button == 0)
	use_button = 1;
      else if (axis == 2)
	axis = 0;
      else 
	axis++;
    }

   switch (c) {
      
    case 'x':
      use_button = 0;
      axis = 0;
      break;
      
    case 'y':
      use_button = 0;
      axis = 1;
      break;
      
    case 'z':
      use_button = 0;
      axis = 2;
      break;
      
    default:
      printf("Enter x, y, or z\n");
      printf("Or press the button\n\n");
    }
    
    a = -100;
    b = -200;
    
    for(led = 1; led < 4; led++){
		if(buffer[axis] < a && buffer[axis] > b)
	//f3d_led_on(led);
		printf("Working 1-3");
     a -= 100;
     b -= 100;
    }
    
    a = 100;
    b = 200;
    
    for(led = 7; led > 4; led++){
      if(buffer[axis] > a && buffer[axis] < b)
	//f3d_led_on(led);
		printf("Working 4-7");
      a += 100;
      b += 100;
    }
    if (abs(buffer[axis]) > 5 || abs(buffer[axis]) < 100)
      //f3d_led_on(0);
		printf("working 0");
    
    if (abs(buffer[axis]) > 400)
      //f3d_led_on(4);
		printf("working 5");
      //delay();
  }
}