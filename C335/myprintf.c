#include <stdarg.h>
#include <stdio.h>

int acsiiconv();
void printint();
void printstring();
void printhex();

void myprintf(const char *fmt, ...) {
    const char *p;
    va_list argp;
    int i;
    char *s;

    va_start(argp, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'c':
            i = va_arg(argp, int);
            putchar(i);
            break;

        case 'd':
            i = va_arg(argp, int);
            printint(i);
            break; //This

	case 's':
            s = va_arg(argp, char *);
            printstring(s); //This
            break;
	    
	case 'x':
	  i = va_arg(argp, int);
	  printhex(i); //This
	  break; 
	  
        case '%':
            putchar('%');
            break;
        }
    }
    va_end(argp);
}

int main()
{
  printint(0);
  printf("\n");
  printint(1234567890);
  printf("\n");
  myprintf("%s", "Is this working?");
  printf("\n");
  myprintf("The number %d", -12);
  printf("\n");
  myprintf("the number %x in hexadecimal\n", 11);
}

int num_storage[10];

int fill_storage(num)
{
  int i = 0;
  
  while (num > 9){
    num_storage[i] = num % 10;
    num = num / 10;
    i++;
  }
  
  num_storage[i] = num;

  return i;
}

int acsiiconv(num)
{
  int acsii_num = num + 48;
  return acsii_num;
}

void printint(num)
{
  int i = 0;
  int negative = 0;

  if (num < 0){
    num = abs(num);
    negative = 1;
  }
  
  i = fill_storage(num);
  
  if (negative == 1)
    putchar('-');

  while (i >= 0){
    num_storage[i] = acsiiconv(num_storage[i]);
    putchar(num_storage[i]);
    i--;
  }
}

void printstring(char *s)
{
  while(*s){
    putchar(*s);
    s++;
  }
}

void printhex(num)
{
  int hexmult = 16;
  int i = 0;
  int remain = 0;
  
  while (num > 15){
    remain = num % 16;
    num = num / 16;
    num_storage[i] = remain;
    i++;
  }
  
  num_storage[i] = num;

  while (i >= 0){
    
    if (num_storage[i] > 9){
      
      switch (num_storage[i]){
	
      case 10:
	putchar('a');
	break;
	
      case 11:
	putchar('b');
	break;
	
      case 12:
	putchar('c');
	break;
	
      case 13:
	putchar('d');
	break;
	
      case 14:
	putchar('e');
	break;
	
      case 15:
	putchar('f');
	break;
	
      default:
	myprintf("Error with hexidecimal printing");
      }
    }
    
    else
      putchar(acsiiconv(num_storage[i]));
    
    i--;
  }      
}





