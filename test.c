#include <stdio.h>
#include <stdint.h>
 uint32_t rgbcolor(int r, int g, int b , int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
int main()
{
  printf("%u\n", rgbcolor(255, 16, 10, 0));
}