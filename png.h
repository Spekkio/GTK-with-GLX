#include <png.h>
#include <GL/glx.h>

typedef struct
{
  unsigned long int width;
  unsigned long int height;
  png_structp png;
  png_infop info;
  png_bytep * row_p;
  png_bytepp row_pointers;
  GLubyte *glxRawTexture;
}texture_t;

extern texture_t botten;
extern texture_t box1;
extern texture_t box2;

void printVersion(void);
void freeTexture(texture_t t);
texture_t loadTexture(const char * image_file_name);
