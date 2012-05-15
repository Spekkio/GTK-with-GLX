#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

#include "main.h"
#include "sphere.c"


void rotate()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(rot_y_vel*0.001, 1.0, 0.0, 1.0);
  glRotatef(rot_z_vel*0.001, 0.0, 1.0, 1.0);
  glMultMatrixf(rotation_matrix);
  glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}

void calcSphere()
{
  const float it = 100.0;
  float i,a;
  glBegin(GL_QUADS);

  for(a=0;a<it;a+=1.0)
  for(i=0;i<it;i+=1.0)
    {
      glColor3f(sin(a/(it*3))*2*M_PI,0.5,sin((i/(it/10))*2*M_PI));
      glVertex3f(sin((a/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI), sin((a/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI), cos((a/(it*2))*2*M_PI));
      glVertex3f(sin((a/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), sin((a/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), cos((a/(it*2))*2*M_PI));
      glVertex3f(sin(((a+1)/(it*2))*2*M_PI)*cos(((i+1)/it)*2*M_PI), sin(((a+1)/(it*2))*2*M_PI)*sin(((i+1)/it)*2*M_PI), cos(((a+1)/(it*2))*2*M_PI));
      glVertex3f(sin(((a+1)/(it*2))*2*M_PI)*cos(((i)/it)*2*M_PI), sin(((a+1)/(it*2))*2*M_PI)*sin(((i)/it)*2*M_PI), cos(((a+1)/(it*2))*2*M_PI));
    }

  glEnd();
}

void drawCube(float size)
{
  glBegin(GL_QUADS);

  glColor3f(0.7, 0.0, 0.2);
  glVertex3f(-size, -size, -size);
  glVertex3f( size, -size, -size);
  glVertex3f( size,  size, -size);
  glVertex3f(-size,  size, -size);

  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f(-size,  size,  size);

  glColor3f(0.0, 0.0, 0.7);
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, -size,  size);
  glVertex3f(-size,  size,  size);
  glVertex3f(-size,  size, -size);

  glVertex3f( size, -size, -size);
  glVertex3f( size, -size,  size);
  glVertex3f( size,  size,  size);
  glVertex3f( size,  size, -size);

  glColor3f(0.0, 0.7, 0.0);

  glVertex3f(-size, -size, -size);
  glVertex3f(-size, -size,  size);
  glVertex3f( size, -size,  size);
  glVertex3f( size, -size, -size);

  glVertex3f(-size, size, -size);
  glVertex3f(-size, size,  size);
  glVertex3f( size, size,  size);
  glVertex3f( size, size, -size);

  glEnd();
}

void expose(void)
{
  float	aspect_ratio;
  char	info_string[256];

  aspect_ratio = (float)(wa.width) / (float)(wa.height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.50*aspect_ratio, 2.50*aspect_ratio, -2.50, 2.50, 1., 100.);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10., 0., 0., 0., 0., 0., 0., 0., 1.);
  glMultMatrixf(rotation_matrix);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*drawCube(1.0);*/
  drawSphere();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, (float)wa.width, 0, (float)wa.height, -1., 1.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 glColor3f(1.0, 1.0, 1.0);
 sprintf(info_string, "%4.1f seconds * %4.1f fps at %i x %i", TimeCounter, FPS, wa.width, wa.height);
 glRasterPos2i(10, 10);
 glCallLists(strnlen(info_string,256), GL_UNSIGNED_BYTE, info_string);

 sprintf(info_string, "GLX with GTK test program");
 glRasterPos2i(10, wa.height-32);
 glCallLists(strlen(info_string), GL_UNSIGNED_BYTE, info_string);

 glXSwapBuffers(disp, GDK_WINDOW_XID(window->window));
 /*
 glXSwapBuffers(disp, *gl_drawable);
 */
}

void glxSetup()
{
  char		font_string[128];
  XFontStruct	*font_struct;

  TimeCounter = 0;

  glc = glXCreateContext(disp, vi, NULL, GL_TRUE);
  if(glc == NULL)
    {
      printf("\n\tCannot create gl context\n");
      exit(0);
    }/*
  glXCreateGLXPixmap(disp, vi, pixmap);
     */
  glXMakeCurrent(disp, GDK_WINDOW_XID(window->window), glc);

  /*
  glXMakeCurrent(disp, pixmap, glc);
  */
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.00, 0.00, 0.40, 1.00);

  sprintf(font_string, "-monotype-*-medium-r-normal--*-*-*-*-*-*-iso8859-1");
  font_struct = XLoadQueryFont(disp, font_string);

  if(font_struct != NULL)
    {
      printf("found font: %s\n",font_string);
      glXUseXFont(font_struct->fid, 32, 192, 32);
    }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}
