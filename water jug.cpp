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

// Returns 0 if next state is goal state or if next state does not violate any production rules and if it is not already present in existing tree.
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
	
	// Searching existing tree for next state
	
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


// Tries all production rules, verifies with end state amd returns state if it is a goal state, else returns NULL.

/* PRODUCTION RULES 
(x, y) -> (a, y) if x < a i.e., Fill the first jug if it is not already full
(x, y) -> (x, b) if y < b i.e., Fill the second jug if it is not already full
(x, y) -> (0, y) if x > 0 i.e., Empty the first jug
(x, y) -> (x, 0) if y > 0 i.e, Empty the second jug
(x, y) -> (min(x + y, a), max(0, x + y – a)) if y > 0 i.e., Pour from second jug into first jug until the first jug is full or the second jug is empty
(x, y) -> (max(0, x + y – b), min(x + y, b)) if x > 0 i.e., Pour from first jug into second jug until the second jug is full or the first jug is empty
*/

struct node* genNewState(struct node *crntState, int maxJug1, int maxJug2, int reqJug1, int reqJug2)
{
	int d;
	struct node *nextState;
	nextState = (struct node*)malloc(sizeof(struct node));
	
	// Applying different production rules
	
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

	// General case: (x,y) where y < max2
	if((crntState->y < maxJug2) && (crntState->x != 0))
	{
		d = maxJug2 - crntState->y;
		
		if(d >= crntState->x)
			{
				// Pour all contents of Jug1 into Jug2
				nextState->x = 0;
				nextState->y = crntState->y + crntState->x;
			}
		else
		{
			// Pour as much as Jug2 can take from Jug1
			nextState->x = crntState->x - d;
			nextState->y = crntState->y + d;
		}
		if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
				return(nextState);
	}
	
	// General case: (x,y) where x < max1
	if((crntState->x < maxJug1) && (crntState->y != 0))
	{
		d = maxJug1 - crntState->x;
		if(d >= crntState->y)
		{
			// Pour all contents of Jug2 into Jug1
			nextState->y = 0;
			nextState->x = crntState->x + crntState->y;
		}
		else
		{
			// Pour as much as Jug1 can take from Jug2
			nextState->y = crntState->y - d;
			nextState->x = crntState->x + d;
		}
		if(isNodePresent(nextState, maxJug1, maxJug2, reqJug1, reqJug2) != 1)
			return(nextState);
	}
	return(NULL);
}

// Generates tree of all valid states.
void generateTree(int maxJug1, int maxJug2, int reqJug1, int reqJug2)
{	
	printf("Generate Tree of valid states.\n");
	int flag1, flag2;
	int total = 0;
	struct node *tempLeft, *tempRight;
	
	// Initialising root(0,0)
	root  = (struct node*)malloc(sizeof(struct node));
	root->x = 0; root->y = 0; root->next = NULL;
	total++;
	
	// Initialising left(x,0)
	left = (struct node*)malloc(sizeof(struct node));
	left->x = 0; left->y = maxJug2; left->next = NULL;
	total++;
	
	// Initialising right(0,y)
	right = (struct node*)malloc(sizeof(struct node));
	right->x = maxJug1; right->y = 0; right->next = NULL;
	total++;
	
	tempLeft = left;
	tempRight = right;

	while(1)
	{
		flag1 = 0; flag2 = 0;
		if((tempLeft->x != reqJug1) || (tempLeft->y != reqJug2))
		{
			tempLeft->next = genNewState(tempLeft, maxJug1, maxJug2, reqJug1, reqJug2);
			total++;
			tempLeft = tempLeft->next;
			tempLeft->next = NULL;
			flag1 = 1;
		}
		if((tempRight->x != reqJug1) || (tempRight->y != reqJug2))
		{
			tempRight->next = genNewState(tempRight, maxJug1, maxJug2, reqJug1, reqJug2);
			total++;
			tempRight = tempRight->next;
			tempRight->next = NULL;
			flag2 = 1;
		}
		if((flag1 == 0) && (flag2 == 0))
			break;
	}
	printf("Total States: %d\n", total);
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
