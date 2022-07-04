/* Name: Vadde Manjula Murari
   Roll no.:19CE30024
   Sudoku Solver(self project) using Backtracking Algorithm */

#include <iostream>
using namespace std;

bool isPresentInCol(int**a,int col, int num){ //check if num is present in col 
   for (int row = 0; row < 9; row++)
      if (a[row][col] == num)
         return true;
   return false;
}
bool isPresentInRow(int** a,int row, int num){ //check if num is present in row
   for (int col = 0; col < 9; col++)
      if (a[row][col] == num)
         return true;
   return false;
}
bool isPresentInBox(int**a,int boxStartRow, int boxStartCol, int num){
//check if num is present in 3x3 box
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (a[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}
void sudokuGrid(int**a){ //print the sudoku grid after solving
cout<<"The answer for the given input is:" << endl;
   for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
         if(j == 3 || j == 6)
            cout << " | ";
         cout << a[i][j] <<" ";
      }
      if(i == 2 || i == 5){
         cout << endl;
         for(int k = 0; k<9; k++)
            cout << "---";
      }
      cout << endl;
   }
}
bool findEmptyPlace(int** a){ //get empty location and update row and column
   for (int row = 0; row < 9; row++)
      for (int col = 0; col < 9; col++)
         if (a[row][col]== 0) //marked with 0 is empty
            return true;
   return false;
}
bool isValidgrid(int** a,int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(a,row, num) && !isPresentInCol(a,col, num) && !isPresentInBox(a,row - row%3 ,
col - col%3, num);
}
void next(int* a,int x,int y)     //return the next iteration indexes
{
	if(x==8)
	{
		if(y==8)
		y=y;						/*same values of row and column will return and checks if grid is full 
													not in next recursive iteration*/
		else{
		y++;
		x=0;
	}
	}
	else
	x++;
	a[0]=x;
	a[1]=y;
}
bool solveSudoku(int** a,int row,int col){
   if (!findEmptyPlace(a))
      return true; //when all places are filled
      bool flag=false;
      if(a[row][col]==0){       //when the grid's row,col box has 0 as input 
      flag=true;
	  }
	  int* nextarr = new int[2]; //strores the next interation indexes
		next(nextarr,row,col);
	  if(flag){
	  for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (isValidgrid(a,row, col, num)){ //check validation, if yes -> put the number in the grid
         a[row][col] = num;
         if (solveSudoku(a,nextarr[0],nextarr[1])) //recursively go for other rooms in the grid
            return true;
         a[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   	}
	}
	else
	{
		if(solveSudoku(a,nextarr[0],nextarr[1]))
		return true;
	}
   return false;
}
int main(){
	int n=9;
	int** a = new int*[9];
	for(int i=0;i<9;i++)
	a[i] = new int[9];
	cout<<"Please enter 0 if the box is to be filled."<<endl;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	cin>>a[i][j];
   if (solveSudoku(a,0,0) == true)
      sudokuGrid(a);
   else
      cout << "No solution exists.";
}
