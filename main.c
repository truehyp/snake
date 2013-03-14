/*蛇的结构中可以不需要draw函数*/
#include "snake.h"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#define DRAW_SIZE_WIDTH 	480
#define DRAW_SIZE_HEIGTH 	480
#define LINE			24
#define IS_SNAKE 		1	//设置网格中的是蛇
#define IS_FOOD  		2	//设置网格中的是食物
/*enum Forward{
	UP = 1;
	DOWN ;
	LEFT ;
	RIGHT;
} forward;*/

struct Snake *head = NULL;
static struct Snake body[30];
static int body_i = 0;
struct Bean  bean;
static gint grid[LINE][LINE];
const gint EVERY = DRAW_SIZE_WIDTH/LINE;
int forward  = DOWN;
int start_flag = 1; //开始程序的标识
GtkWidget *window = NULL; //作为全局变量，方便draw函数对于其的调用
GtkWidget *drawareo = NULL;

static void destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

/*绘制网格及其上的蛇和事物*/
//void draw (GtkWidget *widget, GdkEventExpose *event, gpointer data)
gint draw (gpointer data)
{
	if (move(NULL) == 1)
	{
		return 0;
	}	
	g_print ("IN draw head.next = %p\n", head->next);
	GdkGC *gc_blue;
	GdkGC *gc_red;
	GdkGC *gc_white;
	gint i;
	gint j;

	GdkColor color;

	//gc_blue = gdk_gc_new(GDK_DRAWABLE(widget->window));
	//gc_blue = gdk_gc_new(GDK_DRAWABLE(window->window));
	gc_blue = gdk_gc_new(drawareo->window);
	color.red = 0;
	color.green = 0;
	color.blue = 65535;
	gdk_gc_set_rgb_fg_color (gc_blue, &color);

	//gc_red = gdk_gc_new (GDK_DRAWABLE(widget->window));
	//gc_red = gdk_gc_new (GDK_DRAWABLE (window->window));
	gc_red = gdk_gc_new (drawareo->window);
	color.red = 65535;
	color.green = 0;
	color.blue = 0;
	gdk_gc_set_rgb_fg_color (gc_red, &color);

	//gc_white = gdk_gc_new (GDK_DRAWABLE(widget->window));
	//gc_white = gdk_gc_new (GDK_DRAWABLE (window->window));
	gc_white = gdk_gc_new (drawareo->window);
	color.red = 65535;
	color.green = 65535;
	color.blue = 65535;
	gdk_gc_set_rgb_fg_color (gc_white, &color);

	gdk_draw_rectangle (drawareo->window, gc_white, TRUE, 0, 0, 25*EVERY, 25*EVERY);
	
	//两次 遍历，保证先出现食物
	for (i = 0; i < LINE; i++)
	{
		for (j = 0; j < LINE; j++)
		{
			if (grid[i][j] == IS_FOOD)
				gdk_draw_arc (drawareo->window, gc_red, TRUE, i*EVERY, j*EVERY, EVERY, EVERY, 0, 64*360);
		}
	}

	for (i = 0; i < LINE; i++)
	{
		for (j = 0; j < LINE; j++)
		{
			if (grid[i][j] == IS_SNAKE)
				gdk_draw_rectangle (drawareo->window, gc_blue, TRUE, i*EVERY, j*EVERY, EVERY, EVERY);
		}
	}
	/*释放*/
	if (gc_white)
		g_object_unref (G_OBJECT (gc_white));
	if (gc_blue)
		g_object_unref (G_OBJECT (gc_blue));
	if (gc_red)
		g_object_unref (G_OBJECT (gc_red));
	return 1;
}

/*按键响应函数*/
void key_press (GtkWidget *widget,
	       	GdkEventKey *event,
	       	gpointer user_data)
{
	switch (event->keyval)
	{
		case UP_KEY:
			if (forward != DOWN)
			{
				g_print("you entry UP\n"); 
				forward = UP;
			}
			break;
		case DOWN_KEY:
			if (forward != UP)
			{
				g_print ("you entry DOWN\n");
				forward = DOWN;
			}
			break;
		case LEFT_KEY:
			if (forward != RIGHT)
			{
				g_print ("you entry LEFT\n");
				forward = LEFT;
			}
			break;
		case RIGHT_KEY:
			if (forward != LEFT)
			{
				g_print ("you entry RIGHT\n");
				forward = RIGHT;
			}
			break;
		case SPACE_KEY:
			///////
			//开始和暂停
			//
			if (start_flag == 1)
				*((gint*)user_data) = gtk_timeout_add (200, draw, NULL);
			if (start_flag == -1)
				gtk_timeout_remove (*((gint*)user_data));
			start_flag = - start_flag;
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

/*初始化函数*/
void init (void)
{
	//grid[1][1] = grid[1][2] = grid[1][3] = 1;
	//grid[6][7] = 2;
	//head = (struct Snake *)malloc (sizeof (struct Snake));
	Initialize (head);
	//AddSnakeNode (head);
	//AddSnakeNode (head);
	/*g_print ("body0 = %p,body1 = %p\n",&body[0],&body[1]);
	g_print ("next = %p ",head.next);
	body[0].point.x = head.point.x;
	body[0].point.y = head.point.y - 1;
	body[1].point.x = body[0].point.x;
	body[1].point.y = body[0].point.y - 1;*/

	grid[head->point.x][head->point.y] = IS_SNAKE;
	//grid[body[0].point.x][body[0].point.y] = grid[body[1].point.x][body[1].point.y] = IS_SNAKE;
	grid[23][23] = IS_FOOD; //测试边界
	Food (&bean);
	g_print ("%d %d\n",bean.point.x, bean.point.y);
	grid[bean.point.x][bean.point.y] = IS_FOOD;


}

/*移动蛇*/
gint move (gpointer data)
{
	struct Snake  *pri_head = head;
	struct Snake  *now_body;
	gint now_x, now_y;
	gint pri_x, pri_y;
	if (CheckEnd (pri_head, &forward) == 2) //检验是否结束
		{
			g_print ("CheckEnd Wall\n"); 
			return 1;
		}
	if (body_i > 3 && CheckEnd (pri_head, &forward) == 1)
	{
		g_print ("CheckEnd\n");
		return 1;
	}
	switch (forward) //依据方向  移动
	{
		case UP:
				/*if (CheckEnd (pri_head, &UP) == TRUE)
				{
					g_print ("CheckEnd\n");
					return 1;
					break;
				}*/
				pri_x = pri_head->point.x;
				pri_y = pri_head->point.y;
				pri_head->point.y = pri_head->point.y - 1;
				g_print ("UP pri_y =%d\n", pri_y);
				while (pri_head->next != NULL) //除头外，每个body移动到它前一个body
				{
					//if (pri_head->next == NULL)
					//	break;
					now_body = pri_head->next;
					now_x = now_body->point.x;
					now_y = now_body->point.y;
					now_body->point.x = pri_x;
					now_body->point.y = pri_y;

					
					pri_head = now_body;
					pri_x = now_x;
					pri_y = now_y;
					g_print ("pri_y =%d, %p\n", pri_y,pri_head);
				}
				break;
		case DOWN:
				/*if (CheckEnd (pri_head, &DOWN) == TRUE)
				{
					g_print ("CheckEnd\n");
					return 1;
					break;
				}*/
				pri_x = pri_head->point.x;
				pri_y = pri_head->point.y;
				pri_head->point.y = pri_head->point.y + 1;
				g_print ("DOWN pri_x = %d pri_y =%d\n",pri_head->point.x, pri_head->point.y);
				g_print ("DOWN point = %p\n", &(pri_head->point));
				g_print ("IN DOWN next = %p\n", pri_head->next);
				while (pri_head->next != NULL)
				{
					//if (pri_head->next == NULL)
					//	break;
					now_body = pri_head->next;
					now_x = now_body->point.x;
					now_y = now_body->point.y;
					now_body->point.x = pri_x;
					now_body->point.y = pri_y;

					
					pri_head = now_body;
					pri_x = now_x;
					pri_y = now_y;
					//g_print ("pri_y =%d\n", pri_y);
					g_print ("In while pri_y =%d, %p\n", pri_y,pri_head);
				}
				break;
		case LEFT:
				/*if (CheckEnd (pri_head, &LEFT) == TRUE)
				{
					g_print ("CheckEnd\n");
					return 1;
					break;
				}*/
				pri_x = pri_head->point.x;
				pri_y = pri_head->point.y;
				pri_head->point.x--;

				while (pri_head->next != NULL)
				{
					//if (pri_head->next == NULL)
					//	break;
					now_body = pri_head->next;
					now_x = now_body->point.x;
					now_y = now_body->point.y;
					now_body->point.x = pri_x;
					now_body->point.y = pri_y;

					
					pri_head = now_body;
					pri_x = now_x;
					pri_y = now_y;
				}
				break;
		case RIGHT:
				/*if (CheckEnd (pri_head, &RIGHT))
				{
					g_print ("CheckEnd\n");
					return 1;
					break;
				}*/
				pri_x = pri_head->point.x;
				pri_y = pri_head->point.y;
				pri_head->point.x++;

				while (pri_head->next != NULL)
				{
					//if (pri_head->next == NULL)
					//	break;
					now_body = pri_head->next;
					now_x = now_body->point.x;
					now_y = now_body->point.y;
					now_body->point.x = pri_x;
					now_body->point.y = pri_y;

					
					pri_head = now_body;
					pri_x = now_x;
					pri_y = now_y;
				}
				break;
		default:
				break;
	}
	/*因为我在吃到食物后 生成的在尾部且和当时的最后一个位置一样
	 *如果最后一个点不是重叠的，那么将他的原来位置清掉。*/
	if (pri_head->point.x != pri_x || pri_head->point.y != pri_y) 
	{
		//grid[pri_head->point.x][pri_head->point.y] = 0;
		//pri_head->point.x = pri_x;
		//pri_head->point.y = pri_y;
		grid[pri_x][pri_y] = 0;
	}

	if (pri_head->point.x == pri_x && pri_head->point.y == pri_y)
	{
		g_print ("\n add body\n");
	}
	if (CheckEat (pri_head, &bean) == TRUE)
	{
		AddSnakeNode (pri_head);
		body_i++;
		grid[bean.point.x][bean.point.y] = 0;//清掉吃掉的点
		Food(&bean);
		grid[bean.point.x][bean.point.y] = IS_FOOD;
		g_print ("body_i = %d\n", body_i);
	}
	pri_head = head;
	g_print ("pri_head = %p", pri_head);
	while (pri_head->next != NULL) //重新生成蛇的图像
	{
		grid[pri_head->point.x][pri_head->point.y] = IS_SNAKE;
		pri_head = pri_head->next;
		g_print ("IN move while pri_head = %p", pri_head);
	}
	grid[pri_head->point.x][pri_head->point.y] = IS_SNAKE;

	if (head->next == NULL)
	{
		g_print ("head->next is NULL\n");
	}
	
	return 0;
}

//开始和暂停，SPACE也有同样的作用
void button_start (GtkWidget *widget, gpointer data)
{
	if (start_flag == 1)
		*((gint*)data) = gtk_timeout_add (200, draw, NULL);
	if (start_flag == -1)
		gtk_timeout_remove (*((gint*)data));
	start_flag = - start_flag;
}
int main (int argc, char *argv[])
{
	gint ptimer;
	GtkWidget *fixed;
	GtkWidget *button;
	head = (struct Snake *)malloc (sizeof (struct Snake));

	gtk_init (&argc, &argv);
	init ();
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	drawareo = gtk_drawing_area_new();
	//ptimer  = gtk_timeout_add (200, draw, NULL);
	button = gtk_button_new_with_label ("Start&stop");
	fixed = gtk_fixed_new();
	
	
	gtk_window_set_title (GTK_WINDOW(window), "snake");
	gtk_window_set_default_size (GTK_WINDOW(window), WIDTH, HEIGHT);
	gtk_widget_set_size_request(drawareo, DRAW_SIZE_WIDTH, DRAW_SIZE_HEIGTH);

	gtk_fixed_put (GTK_FIXED(fixed), drawareo, 0, 0);
	gtk_fixed_put (GTK_FIXED(fixed), button, 0, 500);
	gtk_container_add (GTK_CONTAINER(window), fixed);


	g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
	//g_signal_connect (GTK_OBJECT (window), "expose_event", GTK_SIGNAL_FUNC (draw), NULL);
	g_signal_connect (window, "key-press-event", G_CALLBACK(key_press), (gpointer)&ptimer);
	g_signal_connect (window, "expose", G_CALLBACK(draw), NULL);
	g_signal_connect (GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(button_start), (gpointer)&ptimer);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
