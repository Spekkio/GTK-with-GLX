static gboolean time_seconds(GtkWidget *widget)
{
  TimeCounter++;
  FPS = frames;
  frames=0;
  widget=widget;
  return TRUE;
}

static gboolean time_handler(GtkWidget *widget)
{
  frames++;

  if(gtk_widget_is_drawable(widget))
    {
      XGetWindowAttributes(disp, GDK_WINDOW_XID(window->window), &wa);
      glViewport(0, 0, wa.width, wa.height);
      rotate();
      expose();
    }

  /*  gtk_widget_queue_draw(widget);*/
  return TRUE;
}

static gboolean expose_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  widget = widget;
  event = event;
  data = data;

  return FALSE;
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  widget = widget;
  event = event;
  data = data;
  glXMakeCurrent(disp, None, NULL);
  glXDestroyContext(disp, glc);
  gtk_main_quit();
  return FALSE;
}
