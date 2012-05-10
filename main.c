#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "glx.h"

#include "callback.c"

GtkWidget * window;
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
float TimeCounter,FPS;

void initRoutine()
{
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), "OpenGL test with GTK");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

  g_timeout_add(T_UPDATE,(GSourceFunc)time_handler, GTK_WINDOW(window));
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

int main(int argc, char ** argv)
{
  gtk_init(&argc, &argv);

  initRoutine();

  gtk_widget_show(window);

  glxSetup();

  time_handler(window);
  gtk_main();

  return 0;
}
