#include <stdlib.h>
#include <png.h>

png_structp botten_png, box1_png, box2_png;
png_infop botten_info, box1_info, box2_info;
png_bytep * botten_row_p;
png_bytep * box1_row_p;
png_bytep * box2_row_p;
unsigned long int botten_height;
unsigned long int box1_height;
unsigned long int box2_height;

void loadTextures(void)
{
  unsigned long int y;
  FILE * botten;
  FILE * box1;
  FILE * box2;

  botten = fopen("botten.png","r");
  box1 = fopen("box.png","r");
  box2 = fopen("box_45.png","r");
  if(botten && box1 && box2)
    {
      botten_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      box1_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      box2_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

      png_init_io(botten_png, botten);
      png_init_io(box1_png, box1);
      png_init_io(box2_png, box2);

      botten_info = png_create_info_struct(botten_png);
      png_read_info(botten_png, botten_info);

      box1_info=png_create_info_struct(box1_png);
      png_read_info(box1_png, box1_info);

      box2_info = png_create_info_struct(box2_png);
      png_read_info(box2_png, box2_info);

      botten_height = png_get_image_height(botten_png, botten_info);
      box1_height = png_get_image_height(box1_png, box1_info);
      box2_height = png_get_image_height(box2_png, box2_info);

      botten_row_p = (png_bytep*) malloc(sizeof(png_bytep)*botten_height);
      for (y=0; y<botten_height; y++)
	botten_row_p[y] = (png_byte*) malloc(png_get_rowbytes(botten_png,botten_info));
      png_read_image(botten_png, botten_row_p);
      
      box1_row_p = (png_bytep*) malloc(sizeof(png_bytep)*box1_height);
      for (y=0; y<box1_height; y++)
	box1_row_p[y] = (png_byte*) malloc(png_get_rowbytes(box1_png,box1_info));
      png_read_image(box1_png, box1_row_p);

      box2_row_p = (png_bytep*) malloc(sizeof(png_bytep)*box2_height);
      for (y=0; y<box2_height; y++)
	box2_row_p[y] = (png_byte*) malloc(png_get_rowbytes(box2_png,box2_info));
      png_read_image(box2_png, box2_row_p);

      fclose(botten);
      fclose(box1);
      fclose(box2);
    }
}

void printVersion(void)
{
    printf("\tCompiled with libpng %s; using libpng %s.\n",PNG_LIBPNG_VER_STRING, png_libpng_ver);
    printf("\tCompiled with zlib %s; using zlib %s.\n", ZLIB_VERSION, zlib_version);
}

void freeTextures(void)
{
  unsigned long int y;

  for (y=0; y<botten_height; y++)
    free(botten_row_p[y]);
  free(botten_row_p);

  for (y=0; y<box1_height; y++)
    free(box1_row_p[y]);
  free(box1_row_p);

  for (y=0; y<box2_height; y++)
    free(box2_row_p[y]);
  free(box2_row_p);
}
