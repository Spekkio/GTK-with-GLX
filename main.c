#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "glx.h"

#include "callback.c"

GdkPixmap * pixmap;
GdkVisual * visual;

GtkWidget * window;
GtkWidget * draw_area;
GdkDisplay* pGtkDisplay;
Display * disp;
Window root;
XVisualInfo * vi;
Colormap cmap;
GLint att[]   = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
GLXContext glc;
GLfloat rotation_matrix[16];
XWindowAttributes wa;
float rot_z_vel = 50.0, rot_y_vel = 30.0,DT;

unsigned long int frames;
float TimeCounter,FPS;

png_structp botten_png, box1_png, box2_png;
png_infop botten_info, box1_info, box2_info;

long int flags;

void initRoutine()
{
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  draw_area = gtk_drawing_area_new();

  gtk_widget_set_size_request(draw_area, 500, 500);

  gtk_container_add(GTK_CONTAINER(window), draw_area);

  visual = gdk_visual_get_system();
  pixmap = gdk_pixmap_new(NULL, 500, 500, 24);

  gtk_window_set_title(GTK_WINDOW(window), "OpenGL test with GTK");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

  TimeCounter=0.0;
  frames=0;

  g_timeout_add(0,(GSourceFunc)time_handler, GTK_WINDOW(window));
  g_timeout_add_seconds(1,(GSourceFunc)time_seconds, GTK_WINDOW(window));

  g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
  g_signal_connect(window, "expose-event", G_CALLBACK(expose_event), NULL);

  pGtkDisplay = gtk_widget_get_display(window);
  disp = gdk_x11_display_get_xdisplay(pGtkDisplay);
  root = gdk_x11_get_default_root_xwindow();
 
  vi = glXChooseVisual(disp,0,att);
  if(vi == NULL)
    {
      printf("\n\tno matching visuals\n\n");
    }

  cmap = XCreateColormap(disp, root, vi->visual, AllocNone);

  if(cmap == 0)
    {
      printf("\n\tCannot create color map\n");
      exit(0);
    }
}

void loadImageFiles(void)
{
  FILE * botten;
  FILE * box1;
  FILE * box2;
  png_bytep * row_p;
  unsigned long int height;
  unsigned long int y;
  
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

      height = png_get_image_height(botten_png, botten_info);
      /*
      printf("Width: %lu\n",png_get_image_width(botten_png, botten_info));
      printf("Height: %lu\n",png_get_image_height(botten_png, botten_info));
      printf("Color: %i\n",png_get_color_type(botten_png, botten_info));
      printf("Bits: %i\n",png_get_bit_depth(botten_png, botten_info));
      */
      row_p = (png_bytep*) malloc(sizeof(png_bytep)*height);
      for (y=0; y<height; y++)
	row_p[y] = (png_byte*) malloc(png_get_rowbytes(botten_png,botten_info));

      png_read_image(botten_png, row_p);

      for (y=0; y<height; y++)
	free(row_p[y]);
      free(row_p);

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

int main(int argc, char ** argv)
{
  flags = 0x00;

  gtk_init(&argc, &argv);

  loadImageFiles();

  initRoutine();

  gtk_widget_show(window);

  glxSetup();

  time_handler(window);
  gtk_main();

  return 0;
}
