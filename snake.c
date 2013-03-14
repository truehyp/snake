#include <gtk/gtk.h>
#include "snake.h"
#include <stdbool.h>
#include <time.h>

/*初始化蛇*/
void Initialize (struct Snake *psnake)
{
	psnake->point.x = 1;
	psnake->point.y = 3;
	psnake->next = NULL;
}

/*为蛇添加一节*/
void AddSnakeNode (struct Snake *psnake)
{
	struct Snake *pbody;
	pbody = (struct Snake *)malloc (sizeof (struct Snake));
	pbody->next = NULL;
	struct Snake *scansnake = psnake;
	while (scansnake->next != NULL)
		scansnake = scansnake->next;
	pbody->point.x = scansnake->point.x;//此处将尾部重叠，所以move中要进行相应处理
	pbody->point.y = scansnake->point.y;
	scansnake->next = pbody;
	g_print ("pbody = %p\n",pbody);
	g_print ("psnake = %p psnake->next = %p\n", psnake, psnake->next);
}

/*确定蛇是否吃到食物*/
gboolean CheckEat (struct Snake *psnake, struct Bean *pbean)
{
	if (psnake->point.x == pbean->point.x)
	{
	       	if (psnake->point.y == pbean->point.y)
			return TRUE;
	}
	return FALSE;
}

/*判断蛇是否撞到墙或自己*/
gint CheckEnd (struct Snake *psnake, int *pforward)
{
	struct Snake *scansnake = psnake;
	struct Snake *head = psnake;
	while (scansnake->next != NULL)
	{
		scansnake = scansnake->next;
		if (head->point.x == scansnake->point.x &&head->point.y == scansnake->point.y)
			return 1;
	}
	if (head->point.y == 0 && (*pforward) == UP)
		return 2;
	if (head->point.y == LINE - 1 && (*pforward) == DOWN)
		return 2;
	if (head->point.x == 0 && (*pforward) == LEFT)
		return 2;
	if (head->point.x == LINE - 1 && (*pforward) == RIGHT)
		return 2;
	return 0;
}

/*随机产生食物的函数*/
void Food (struct Bean *pbean)
{
	srand((unsigned int )time(0));
	pbean->point.x = rand()%LINE ;
	srand((unsigned int )time(0));
	pbean->point.y = rand()%LINE ;
}

/*画蛇食物和墙*/
/*void draw (struct Snake *psnake, struct Bean *pbean)
{
	
}*/
