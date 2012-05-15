extern GdkPixmap * pixmap;
extern GdkVisual * visual;

extern GtkWidget * window;
extern GdkDisplay* pGtkDisplay;
extern Display * disp;
extern Window root;
extern XVisualInfo * vi;
extern Colormap cmap;
extern GLint att[];
extern GLXContext glc;
extern GLfloat rotation_matrix[16];
extern XWindowAttributes wa;
extern float rot_z_vel, rot_y_vel,DT;
extern float TimeCounter,FPS;
#define T_UPDATE 1
