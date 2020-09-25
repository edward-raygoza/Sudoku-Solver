#include <stdio.h>
#include <stdlib.h>


// Declare printSudoku function
void printSudoku(int***);
int integerValueSubgrids=9;
// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions. You can define any functions that can help your solve the problem

    //calls the solve sudoku function 

/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 integerValueSubgrids.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 integerValueSubgrids into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading integerValuebers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}


void printSudoku(int*** arr){
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
	
	// Your implementation here

    //printing entire board
    int i,j,k;    
for(i=0; i < integerValueSubgrids; i+=3){
    //print all 3*3 integerValueSubgrids of the whole grid, each block of entire board
    for(j=0; j < 3; ++j){
        int upDate_Value_row;
        //print each row of each block
        for(k = 0; k<3; ++k){
            upDate_Value_row = *(*(*(arr+i) + j) + k);//first row
            printf("%d ", upDate_Value_row);
        }
        printf("|");
        for(k = 0; k<3; ++k){
            upDate_Value_row = *(*(*(arr+i+1) + j) + k);//second row
            printf("%d ", upDate_Value_row);
        }
        printf("|");
        for(k = 0; k<3; ++k){
            upDate_Value_row = *(*(*(arr+i+2) + j)+ k);//3rd row
            printf("%d ", upDate_Value_row);
        }
        printf("|");
        printf("\n");
        }
       if(i == 6){
         break;
            
       }
       printf("---------------------\n");
        
    }
    printf("\n");
}
//check
int emptySlot(int*** integerValueSubgrids, int* gridIdentity, int *row, int *column){
    int subGridnum, row_index, column_index;
    for (subGridnum = 0; subGridnum < 9; ++subGridnum){
        for(row_index = 0; row_index < 3; ++row_index){
            for(column_index = 0; column_index < 3; ++column_index){
                int upDate_Value = *(*(*(integerValueSubgrids + subGridnum)+row_index)+ column_index);
                if (upDate_Value == 0){
                    //found unassigned spot
                    //update gridIdentity, row and column values
                    *gridIdentity = subGridnum;
                    *row = row_index;
                    *column = column_index;
                    return 1;
                }
            }
        }
    }
    return 0;
}
// check
int rowSafe(int*** integerValueSubgrids, int gridIdentity, int row, int integerValue){
    //get starting gridIdentity(integer of subGrid(block))
    int starting_subGridnum;
    //gridIdentity is between 0 and 2
    if(gridIdentity >= 0 && gridIdentity <= 2){
        starting_subGridnum = 0;//starts at fist block
    }
    else if (gridIdentity >= 3 && gridIdentity <= 5){// 3 and 4
        starting_subGridnum = 3;//starts at fourth block middle row
    }
    else if (gridIdentity >= 6 && gridIdentity <= 8){//6 and 8
        starting_subGridnum =6;// starts at the seventh block
    }
    for(int blockGrid_index = starting_subGridnum; blockGrid_index < starting_subGridnum + 3; ++blockGrid_index){
        int** gridIdentity = *(integerValueSubgrids + blockGrid_index);
        //loop through columns of given row
        for (int column = 0; column < 3; ++column){
        //int upDate_Value = gridIdentity[row][c]//2d later convert since no array notation
        int upDate_Value = *(*(gridIdentity + row) + column);
        if (upDate_Value == integerValue){
            return 0;
        }
        }
    }
    return 1;
}
    //check
int columnSafe(int*** integerValueSubgrids, int gridIdentity, int column, int integerValue){
    //get starting block, different method from getting row starting block
    int starting_subGridnum;
    if(gridIdentity == 0 || gridIdentity == 3 || gridIdentity == 6){
        starting_subGridnum = 0;
    }
    else if (gridIdentity == 1 || gridIdentity == 4 || gridIdentity == 7){
        starting_subGridnum= 1;
    }
    else if (gridIdentity == 2 || gridIdentity == 5 || gridIdentity == 8){
        starting_subGridnum = 2;
    }
    for (int blockGrid_index = starting_subGridnum; blockGrid_index <= starting_subGridnum + 6; blockGrid_index += 3){
        int** gridIdentity = *(integerValueSubgrids + blockGrid_index);
        //loop through the rows of columns
        for(int row = 0; row < 3; ++row){
            //int upDate_Value = gridIdentity[row][c]
            int upDate_Value = *(*(gridIdentity + row) + column);
            if(upDate_Value == integerValue){
                return 0;
            }
        }
    }
    return 1;
    
}


    //check
    int grideSafe(int*** integerValueSubgrids, int gridIdentity, int integerValue){
        //loop through one block and compare all values to integerValue
        //int block = integerValueSubgrids[gridIdentity];
        int** block = *(integerValueSubgrids + gridIdentity);
        for(int row = 0; row < 3; ++ row){
            for(int column = 0; column < 3; ++column){
                int upDate_Value = *(*(block + row)+column);
                if(upDate_Value == integerValue){
                    return 0;
                }
            }
    }
    return 1;
    
}
    //checks if its safe to input a value in the grid
    int check_if_safe(int*** integerValueSubgrids, int gridIdentity, int row, int column, int integerValue){
        if(rowSafe(integerValueSubgrids, gridIdentity, row, integerValue) && columnSafe(integerValueSubgrids, gridIdentity, column, integerValue) && grideSafe(integerValueSubgrids, gridIdentity, integerValue)){
            return 1;
        }
        return 0;
    }

int solveSudoku(int*** integerValueSubgrids){
	// This is the function to solve the Sudoku (integerValueSubgrids). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
	
	//Your implementation here

    /*
    if(its_safe(integerValueber of block, row, columintegerValuen))
        then give an assignment value for now
    return if successful 
    if(solveSudoku(integerValueber of block))
        return 1
    else
        failure then try again
    return false
    */
   
   int row, column, gridIdentity;
   //if the cell is not empty 
   if(!emptySlot(integerValueSubgrids, &gridIdentity, &row, &column)){
       return 1;
   }
    
   for(int integerValue =1; integerValue <= 9; ++integerValue){
       if(check_if_safe(integerValueSubgrids, gridIdentity, row, column, integerValue)){

           //2d integerValueSubgrids[gridIdentity][row][col] // integerValueSubgrids is the integer of the block in the Grid
           *(*(*(integerValueSubgrids + gridIdentity)+row) + column) = integerValue;
           if(solveSudoku(integerValueSubgrids)){
               return 1;
           }
           *(*(*(integerValueSubgrids + gridIdentity)+row)+column) = 0;
       }
   }
   return 0;//if this is false then backtracking starts
}
