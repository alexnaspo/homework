#include <stdio.h>

struct x
{
  int **a,**b;
  struct x **q, **p;
};

int main(int argc, char const *argv[])
{
  // char *s ="GO CS288!";
  // printf("%lu\n", sizeof(s));
  // printf("%s\n", s);
  // int length = sizeof(s)/sizeof(char);
  // int i;
  // for (i = 0; i <= length + 1; ++i)
  // {
  //   printf("%c\n", s[i]);
  // }

  // struct x
  // {
  //   int *a, *b;
  //   struct x *p, *q;
  // };

  // printf("%lu \n", sizeof(struct x));

  // printf("%lu \n", sizeof(argv + 0));
  printf("%s\n", "================");
  // printf("%lu \n", sizeof(argv + 1));
  printf("%lu\n", sizeof(*argv[1]));
  printf("%s\n", argv[0]);
  // printf("%s\n", "================");
  // printf("%lu \n", sizeof(argv + 2));
  // printf("%s\n", "================");
  // printf("%lu \n", sizeof(argv + 3));
  // printf("%lu \n", sizeof(argv + 4));
  return 0;
}


