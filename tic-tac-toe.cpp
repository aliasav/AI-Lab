#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

int board[3][3];
int moves[3][3];

void init_boards()
{
	// Blank : 2	X : 3 	O : 5
	int i,j;
	
	// Initialising board
	for ( i = 0 ; i <= 2 ; i++ )
	{
		for ( j = 0 ; j <= 2 ; j++ )
			board[i][j] = 2;
	}
	
	// Initialising Moves board
	int x = 1;
	for ( i = 0 ; i <= 2 ; i ++)
	{
		for ( j = 0 ; j <= 2 ; j++ )
			moves[i][j] = x++;
	}
}

void display_board()
{
	int i,j;
	cout << "\nMoves:\n" ;
	for ( i = 0 ; i <= 2 ; i ++ )
	{
		for ( j = 0 ; j <= 2 ; j++)
		{
			cout << " " << moves[i][j] << " ";
		}
		cout << endl;
	}
	
	/*
	cout << "\nTic-tac-toe board (encrypted form):\n" ;
	for ( i = 0 ; i <= 2 ; i ++ )
	{
		for ( j = 0 ; j <= 2 ; j++)
			cout <<" "<< board[i][j] << " ";
		cout << endl;
	}
	*/
	
	cout << "\nTic-tac-toe board:\n" ;
	for ( i = 0 ; i <= 2 ; i ++ )
	{
		for ( j = 0 ; j <= 2 ; j++)
		{
			switch(board[i][j])
			{
				default:
					break;
				case 2:
					cout << " _ ";
					break;
				case 3:
					cout << " X ";
					break;
				case 5:
					cout << " O ";
					break;
			}
		}
		cout << endl;
	}

}

int main()
{
	init_boards();
	display_board();
	
	return 0;
	
}
