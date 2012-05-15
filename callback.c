static gboolean time_handler(GtkWidget *widget)
{
  /*
  time_t curtime;
  struct tm *loctime;
  */
  static float counter = 0;
  counter += (T_UPDATE/1000.0);
  if(counter>=1.0)
    {
      counter=0;
      TimeCounter++;
    }

  widget=widget;

  XGetWindowAttributes(disp, GDK_WINDOW_XID(window->window), &wa);
  glViewport(0, 0, wa.width, wa.height);

  rotate();
  expose();

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
