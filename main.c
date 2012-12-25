#include "snake.h"
#include <gtk/gtk.h>

enum Forward{
	UP = 1;
	DOWN ;
	LEFT ;
	RIGHT;
} forward;

struct Snake head;
struct Snake body[30];
struct Bean  bean;
gint forward  = DOWN;

/*按键响应函数*/
void key_press (GtkWidget *widget,
	       	GdkEventKey *event,
	       	gpointer user_data)
{
	switch (event->keyval)
	{
		case UP_KEY:
			if (forward != DOWN)
				forward = UP;
			break;
		case DOWN_KEY:
			if (forward != UP)
				forward = DOWN;
			break;
		case LEFT_KEY:
			if (forward != RIGHT)
				forward = LEFT;
			break;
		case RIGHT_KEY:
			if (forward != LEFT)
				forward = RIGHT;
			break;
		case SPACE_KEY:
			///////
			//
			//
			break;
		case ENTER_KEY:
			//////
			//
			//
			break;
		default:
			break;
	}
}
ggggg
