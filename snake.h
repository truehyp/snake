#include <gtk/gtk.h>
#ifndef SNAKE_H_
#define SNAKE_H_
#define UP 		1
#define DOWN 		2
#define LEFT		3
#define RIGHT		4
#define WIDTH		800
#define HEIGHT 		600
#define UP_KEY 		0xff52
#define DOWN_KEY 	0xff54
#define LEFT_KEY 	0xff51
#define RIGHT_KEY 	0xff53
#define SPACE_KEY 	32
#define ENTER_KEY 	0xff0d
#define DRAW_SIZE_WIDTH 	480
#define DRAW_SIZE_HEIGTH 	480
#define LINE			24
/*gint UP = 1;
gint DOWN = 2;
gint LEFT = 3;
gint RIGHT = 4;*/


struct Point {
	int x;
	int y;
};

struct Snake {
	struct Point point;
	struct Snake *next;
};

struct Bean {
	struct Point point;
};
/*struct Snake{
	struct Node head;
	struct Node node;
};*/
/*初始化蛇
 * psnake 为指向蛇的指针*/
void Initialize (struct Snake *psnake);

/*为蛇添加一节，从末尾添加*/
void AddSnakeNode (struct Snake *psnake);

/*确定蛇头是否吃到食物
 * 如果撞到食物则返回true
 * 否则返回false
 */
gboolean CheckEat (struct Snake *psnake, struct Bean *pbean);
/*判断蛇头是否撞到墙和或自己
 * 如果撞到则返回true
 * 否则返回false
 */
gint CheckEnd (struct Snake *psnake, int *pforward);
/*随机产生食物的函数*/
void Food (struct Bean *pbean);

/*画蛇食物和墙*/
//void draw (struct Snake *psnake, struct Bean *pbean);


#endif
