/* Hello World program */

#include<stdio.h>

main()
{
    short age[4]; 
    age[0]=23;
    age[1]=34;
    age[2]=65;
    age[3]=74;

    int i;
    int len=sizeof(age)/sizeof(short);

    for (i = 0; i < len; i++)
    {
      printf("%d\n", age[i]);
      printf("%s\n", "===========");
    
    }
    return 0;

}