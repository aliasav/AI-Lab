#include<stdio.h>
#include<stdlib.h>

struct node
{
	int x, y;
	struct node *next;

}*root, *left, *right;

void DFS()
{
	struct node *temp;
	temp = left;
	printf("DFS Result\nStart State  ::  (%d , %d)\n", root->x, root->y);
	printf("Possible DFS Result 1\n");
	while(1)
	{
		printf("(%d , %d)\n", temp->x, temp->y);
		if(temp->next == NULL)
			break;
		temp = temp->next;
	}
	temp = right;
	printf("Possible DFS Result 2\n");
	while(1)
	{
		printf("(%d , %d)\n", temp->x, temp->y);
		if(temp->next == NULL)
			break;
		temp = temp->next;
	}
}


void BFS(int reqJug1, int reqJug2)
{
	struct node *temp1 = left, *temp2 = right;
	printf("\nBFS Result\n");
	printf("(%d , %d)\n", root->x, root->y);
	while(1)
	{
		printf("(%d , %d)\n", temp1->x, temp1->y);
		if((temp1->x == reqJug1)&&(temp1->y == reqJug2))
			break;
		temp1 = temp1->next;
		printf("(%d , %d)\n", temp2->x, temp2->y);
		if((temp2->x == reqJug1)&&(temp2->y == reqJug2))
			break;
		temp2 = temp2->next;
	}
}

int isNodePresent(struct node *nextState, int maxJug1, int maxJug2, int reqJug1, int reqJug2)
{
	struct node *temp;
	
	// If Next state is goal state, return 0
	if((nextState->x == reqJug1) && (nextState->y == reqJug2))
		return(0);
		
	// If Both jugs max out, return 1
	if((nextState->x == maxJug1) && (nextState->y == maxJug2))
		return(1);
		
	// If Both jugs empty, return 1
	if((nextState->x == 0) && (nextState->y == 0))
		return(1);
	
	// Search for next state, starting from left
	temp = left;
	while(1)
	{
		if((temp->x == nextState->x) && (temp->y == nextState->y))
			return(1);
		else if(temp->next == NULL)
			break;
		else
			temp = temp->next;
	}

	// Searching right for next state
	temp = right;
	while(1)
	{
		if((temp->x == nextState->x) && (temp->y == nextState->y))
			return(1);
		else if(temp->next == NULL)
			break;
		temp = temp->next;
	}
	return(0);
}

struct node* genNewState(struct node *crntState, int maxJug1, int maxJug2, int reqJug1, int reqJug2)
{
	int d;
	struct node *nextState;
	nextState = (struct node*)malloc(sizeof(struct node));
	
	// Trying (max,current)	
	nextState->x = maxJug1;
	nextState->y = crntState->y;
	if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
		return(nextState);
	
	// Trying (current,max)
	nextState->x = crntState->x;
	nextState->y = maxJug2;
	if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
		return(nextState);
	
	// Trying (0,current)
	nextState->x = 0;
	nextState->y = crntState->y;
	if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
		return(nextState);
	
	// Trying (current,0)
	nextState->y = 0;
	nextState->x = crntState->x;
	if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
		return(nextState);

	if((crntState->y < maxJug2) && (crntState->x != 0))
	{
		d = maxJug2 - crntState->y;
		if(d >= crntState->x)
			{
				nextState->x = 0;
				nextState->y = crntState->y + crntState->x;
			}
		else
		{
			nextState->x = crntState->x - d;
			nextState->y = crntState->y + d;
		}
		if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
				return(nextState);
	}
	if((crntState->x < maxJug1) && (crntState->y != 0))
	{
		d = maxJug1 - crntState->x;
		if(d >= crntState->y)
		{
			nextState->y =-0;
			nextState->x = crntState->x + crntState->y;
		}
		else
		{
			nextState->y = crntState->y - d;
			nextState->x = crntState->x + d;
		}
		if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
			return(nextState);
	}
	return(NULL);
}


void generateTree(int maxJug1, int maxJug2, int reqJug1, int reqJug2)
{	
	printf("Generate Tree function called.\n\n");
	int flag1, flag2;
	
	struct node *tempLeft, *tempRight;
	
	// Initialising root(0,0)
	root  = (struct node*)malloc(sizeof(struct node));
	root->x = 0; root->y = 0; root->next = NULL;
	
	// Initialising left(x,0)
	left = (struct node*)malloc(sizeof(struct node));
	left->x = 0; left->y = maxJug2; left->next = NULL;

	// Initialising right(0,y)
	right = (struct node*)malloc(sizeof(struct node));
	right->x = maxJug1; right->y = 0; right->next = NULL;
	
	tempLeft = left;
	tempRight = right;

	while(1)
	{
		flag1 = 0; flag2 = 0;
		if((tempLeft->x != reqJug1) || (tempLeft->y != reqJug2))
		{
			tempLeft->next = genNewState(tempLeft, maxJug1, maxJug2, reqJug1, reqJug2);
			tempLeft = tempLeft->next;
			tempLeft->next = NULL;
			flag1 = 1;
		}
		if((tempRight->x != reqJug1) || (tempRight->y != reqJug2))
		{
			tempRight->next = genNewState(tempRight, maxJug1, maxJug2, reqJug1, reqJug2);
			tempRight = tempRight->next;
			tempRight->next = NULL;
			flag2 = 1;
		}
		if((flag1 == 0) && (flag2 == 0))
			break;
	}
}


int main()
{
	int maxJug1, maxJug2, reqJug1, reqJug2;
	
	printf("Enter the maximum capacity of jug1 : ");
	scanf("%d", &maxJug1);
	printf("Enter the maximum capacity of jug2 : ");
	scanf("%d", &maxJug2);
	printf("Enter the required water in jug1 : ");
	scanf("%d", &reqJug1);
	printf("Enter the required water in jug2 : ");
	scanf("%d", &reqJug2);
	
	generateTree(maxJug1, maxJug2, reqJug1, reqJug2);
	DFS();
	BFS(reqJug1, reqJug2);
	return 0;
}
