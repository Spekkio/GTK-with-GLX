#include <stdio.h>
#include <math.h>


int main()
{
  const float it = 10;
  float i,a;

  printf("#declare generated_sphere = mesh {\n");

  for(a=0;a<it;a+=1.0)
  for(i=0;i<it;i+=1.0)
    { /*Corner 1*/
      printf("\ttriangle {");
      printf("<%f , %f , %f> , ", sin((a/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI), sin((a/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI), cos((a/(it*2))*2*M_PI));

      /*Corner 2*/
      printf("<%f , %f , %f> , ", sin((a/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), sin((a/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), cos((a/(it*2))*2*M_PI));

      /*Corner 3*/
      printf("<%f , %f , %f>",sin(((a+1)/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), sin(((a+1)/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), cos(((a+1)/(it*2))*2*M_PI));

      printf("}\n");

      /*Corner 4*/
      printf("\ttriangle {");
      printf("<%f , %f , %f> , ",sin(((a+1)/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI), sin(((a+1)/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI), cos(((a+1)/(it*2))*2*M_PI));

      /*Corner 3*/
      printf("<%f , %f , %f>",sin(((a+1)/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), sin(((a+1)/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), cos(((a+1)/(it*2))*2*M_PI));

      /*Corner 1*/
      printf("<%f , %f , %f>", sin((a/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI), sin((a/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI), cos((a/(it*2))*2*M_PI));

      printf("}\n");

    }
  printf("\ttexture {\n\t\tpigment { color rgb<1.0 , 1.0 , 1.0>}\n\t\tfinish { ambient 0.2 diffuse 0.9 }\n\t}\n");
  printf("}");

  return 0;
}
