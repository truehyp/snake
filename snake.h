#ifndef SNAKE_H_
#define SNAKE_H_
#define WIDTH		800
#define HEIGHT 		600
#define UP_KEY 		0xff52
#define DOWN_KEY 	0xff54
#define LEFT_KEY 	0xff51
#define RIGHT_KEY 	0xff53
#define SPACE_KEY 	32
#define ENTER_KEY 	0xff0d


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
 * 否则返回false*/
gboolean CheckEat (struct Snake *psnake, struct Bean *pbean);

/*判断蛇头是否撞到墙和或自己
 * 如果撞到则返回true
 * 否则返回false*/
gboolean CheckEnd (struct Snake *psnake, gint *pforward);

/*随机产生食物的函数*/
void Food (struct Bean *pbean);

/*画蛇食物和墙*/
void draw (struct Snake *psnake, struct Bean *pbean);


#endif
