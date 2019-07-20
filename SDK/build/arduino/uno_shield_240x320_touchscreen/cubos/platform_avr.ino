//////////////////////////////////////////////////
// For debugging

// Переменные, создаваемые процессом сборки,
// когда компилируется скетч
extern int __bss_end;
extern void *__brkval;
 
// Функция, возвращающая количество свободного ОЗУ (RAM)
int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}

void showFreeMemory(){
  int val = memoryFree();
  int y = 0;
  // DEBUGGING
  // Problems in SDK
  int a=val;
  char b[10];
  String str;
  str=String(a);
  str.toCharArray(b,10);
  drawString( b, 0, y);

}

//
/////////////////////////////////////////////////