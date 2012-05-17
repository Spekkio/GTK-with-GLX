#include <stdlib.h>
#include <png.h>
#include "png.h"

png_structp botten_png, box1_png, box2_png;
png_infop botten_info, box1_info, box2_info;

texture_t botten;
texture_t box1;
texture_t box2;

texture_t loadTexture(const char * image_file_name)
{
  texture_t image;
  unsigned long int y;
  unsigned int row_bytes, sig_read;
  FILE * file;

  sig_read=0;

  file = fopen(image_file_name,"r");
  if(file)
    {
      image.png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

      image.info = png_create_info_struct(image.png);

      if(setjmp(png_jmpbuf(image.png)))
	{
	  png_destroy_read_struct(&image.png, &image.info, png_infopp_NULL);
	  fclose(file);
	  return *(texture_t *)NULL;
	}

      png_init_io(image.png, file);

      png_set_sig_bytes(image.png, sig_read);

      png_read_png(image.png, image.info, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

      image.height = png_get_image_height(image.png, image.info);
      image.width = png_get_image_width(image.png, image.info);

      row_bytes = png_get_rowbytes(image.png, image.info);
      image.row_pointers = png_get_rows(image.png, image.info);
      image.glxRawTexture = malloc(row_bytes * image.height);

      for(y=0; y<image.height;y++)
	{
	  memcpy(image.glxRawTexture + (row_bytes * (image.height-1-y)), image.row_pointers[y], row_bytes);
	}

      png_destroy_read_struct(&image.png, &image.info, png_infopp_NULL);

      fclose(file);
      return image;
    }
  return *((texture_t *)NULL);
}
/*
void loadTextures(void)
{
  unsigned long int y;
  FILE * botten_f;
  FILE * box1_f;
  FILE * box2_f;

  botten_f = fopen("botten.png","r");
  box1_f = fopen("box.png","r");
  box2_f = fopen("box_45.png","r");
  if(botten_f && box1_f && box2_f)
    {
      botten_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      box1_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      box2_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

      png_init_io(botten_png, botten_f);
      png_init_io(box1_png, box1_f);
      png_init_io(box2_png, box2_f);

      botten_info = png_create_info_struct(botten_png);
      png_read_info(botten_png, botten_info);

      box1_info=png_create_info_struct(box1_png);
      png_read_info(box1_png, box1_info);

      box2_info = png_create_info_struct(box2_png);
      png_read_info(box2_png, box2_info);

      botten.height = png_get_image_height(botten_png, botten_info);
      box1.height = png_get_image_height(box1_png, box1_info);
      box2.height = png_get_image_height(box2_png, box2_info);

      botten.row_p = (png_bytep*) malloc(sizeof(png_bytep)*botten.height);
      for (y=0; y<botten.height; y++)
	botten.row_p[y] = (png_byte*) malloc(png_get_rowbytes(botten_png,botten_info));
      png_read_image(botten_png, botten.row_p);
      
      box1.row_p = (png_bytep*) malloc(sizeof(png_bytep)*box1.height);
      for (y=0; y<box1.height; y++)
	box1.row_p[y] = (png_byte*) malloc(png_get_rowbytes(box1_png,box1_info));
      png_read_image(box1_png, box1.row_p);

      box2.row_p = (png_bytep*) malloc(sizeof(png_bytep)*box2.height);
      for (y=0; y<box2.height; y++)
	box2.row_p[y] = (png_byte*) malloc(png_get_rowbytes(box2_png,box2_info));
      png_read_image(box2_png, box2.row_p);

      fclose(botten_f);
      fclose(box1_f);
      fclose(box2_f);
    }
}
*/
void printVersion(void)
{
    printf("\tCompiled with libpng %s; using libpng %s.\n",PNG_LIBPNG_VER_STRING, png_libpng_ver);
    printf("\tCompiled with zlib %s; using zlib %s.\n", ZLIB_VERSION, zlib_version);
}

void freeTexture(texture_t t)
{
  free(t.glxRawTexture);
}
/*
void freeTextures(void)
{
  unsigned long int y;

  for (y=0; y<botten.height; y++)
    free(botten.row_p[y]);
  free(botten.row_p);

  for (y=0; y<box1.height; y++)
    free(box1.row_p[y]);
  free(box1.row_p);

  for (y=0; y<box2.height; y++)
    free(box2.row_p[y]);
  free(box2.row_p);
}
*/
