#include <gtk/gtk.h>
#include <snake.h>
#include <stdbool.h>
#include <time.h>


void Initialize (struct Snake *psnake)
{
	psnake->point.x = 0;
	psnake->point.y = 0;
	psnake->next = NULL:
}

void AddSnakeNode (struct Snake *psnake)
{
	struct Snake newbody;
	struct Snake *scansnake = psnake;
	while (scansnake->next != NULL)
		scansnake = scansnake->next;
	scansnake->next = &newbody;
}

gboolean CheckEat (struct Snake *psnake,struct Bean *pbean)
{
	if (psnake->point.x == pbean->point.x&&psnake->point.y ==pbean.point.y)
		return TRUE;
	return FALSE;
}

gboolean CheckEnd (struct Snake *psnake, gint *pforward)
{
	struct Snake *scansnake = psnake;
	struct Snake *head = psnake;
	while (scansnake->next != NULL)
	{
		scansnake = scansnake->next;
		if (head->point.x == scansnake->point.x &&head->point.y == scansnake->point.y)
			return TRUE;
	}
	if (head->point.y == 0&&(*pforward) == UP)
		return TRUE;
	if (head->point.y == WIDTH&&(*pforward) == DOWN)
		return TRUE;
	if (head->point.x == 0&&(*pforward) == LEFT)
		return TRUE;
	if (head->point.x == HEIGHT&&(*pforward) == RIGHT)
		return TRUE;
	return FALSE;
}

void Food (struct Bean *pbean)
{
	srand((unsigned int )time(0));
	pbean->point.x = rand()%WIDTH + 1;
	srand((unsigned int )time(0));
	pbean->point.y = rand()%HEIGHT + 1;
}

void draw (struct Snake *psnake, struct Bean *pbean)
{
	
}
