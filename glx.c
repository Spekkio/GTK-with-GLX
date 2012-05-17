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
#include "glx.h"
#include "png.h"
/*#include "sphere.c"*/

GLuint sphere;
GLuint texture[1];

void rotate()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(rot_y_vel*0.001, 1.0, 1.0, 1.0);
  glRotatef(rot_z_vel*0.001, 1.0, 1.0, 1.0);
  glMultMatrixf(rotation_matrix);
  glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}

void drawSphere()
{
  glCallList(sphere);
}

void calcSphere()
{
  const float it = 100.0;
  float i,a;

  sphere=glGenLists(1);
  glNewList(sphere,GL_COMPILE);

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

  glEndList();

}

void drawCube(float size)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glBegin(GL_QUADS);

  /*glColor3f(0.7, 0.0, 0.2);*/
  glTexCoord2f(1.0/3.0, 2.0/3.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(2.0/3.0, 2.0/3.0); glVertex3f( size, -size, -size);
  glTexCoord2f(2.0/3.0, 3.0/3.0); glVertex3f( size,  size, -size);
  glTexCoord2f(1.0/3.0, 3.0/3.0); glVertex3f(-size,  size, -size);

  glTexCoord2f(1.0/3.0, 1.0/3.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(2.0/3.0, 1.0/3.0); glVertex3f( size, -size,  size);
  glTexCoord2f(2.0/3.0, 2.0/3.0); glVertex3f( size,  size,  size);
  glTexCoord2f(1.0/3.0, 2.0/3.0); glVertex3f(-size,  size,  size);

  glTexCoord2f(2.0/3.0, 1.0/3.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(3.0/3.0, 1.0/3.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(3.0/3.0, 2.0/3.0); glVertex3f(-size,  size,  size);
  glTexCoord2f(2.0/3.0, 2.0/3.0); glVertex3f(-size,  size, -size);

  
  glTexCoord2f(0.0/3.0, 1.0/3.0); glVertex3f( size, -size, -size);
  glTexCoord2f(1.0/3.0, 1.0/3.0); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0/3.0, 2.0/3.0); glVertex3f( size,  size,  size);
  glTexCoord2f(0.0/3.0, 2.0/3.0); glVertex3f( size,  size, -size);
 
  glTexCoord2f(1.0/3.0, 0.0/3.0); glVertex3f(-size, -size, -size);
  glTexCoord2f(2.0/3.0, 0.0/3.0); glVertex3f(-size, -size,  size);
  glTexCoord2f(2.0/3.0, 1.0/3.0); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0/3.0, 1.0/3.0); glVertex3f( size, -size, -size);
  
  glTexCoord2f(0.0/3.0, 0.0/3.0);glVertex3f(-size, size, -size);
  glTexCoord2f(1.0/3.0, 0.0/3.0);glVertex3f(-size, size,  size);
  glTexCoord2f(1.0/3.0, 1.0/3.0);glVertex3f( size, size,  size);
  glTexCoord2f(0.0/3.0, 1.0/3.0);glVertex3f( size, size, -size);
  
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void expose(void)
{
  float aspect_ratio;
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

  drawSphere();
  /*drawCube(1.0);*/

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
  /*
  unsigned long int x,y;
  uint8_t pixels[100*100*3];
  */

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
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
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
  /*
  for(y=0;y<100;y++)
    {
      for(x=0;x<=100;x++)
	{
	  pixels[x*3+100*y*3+0] = sin(((y+x)/100.0)*2*M_PI)*127.0+127.0;
	  pixels[x*3+100*y*3+1] = sin((x/100.0)*2*M_PI)*127.0+127.0;
	  pixels[x*3+100*y*3+2] = sin((y/100.0)*2*M_PI)*127.0+127.0;
	}
    }
  */

  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, box1.width, box1.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, box1.glxRawTexture);
  /*glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);*/
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  calcSphere();
}
