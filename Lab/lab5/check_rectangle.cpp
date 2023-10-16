#include "lab5_functions.h" // Include the declearation of the function

// You need to make sure the detected corner_points not form a line or point
bool check_rectangle(const int arr[][MAX_DIMENSION], int row, int col, int corner_points[]) {
    /***************Start your code here***************/
    //check if the corner points form a line or point
    if (corner_points[0] == corner_points[2] || corner_points[1] == corner_points[3])
    {
        return false;
    }

    //check whether the area specified by the corner points is containing all "1"s
    for (int i = corner_points[0]; i <= corner_points[2]; i++)
    {
        for (int j = corner_points[1]; j <= corner_points[3]; j++)
        {
            if (arr[i][j] == 0)
            {
                return false;
            }
        }
    }

    //check whether the values outside that area are all "0"s
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++){
            if (arr[i][j] == 1) {
                if (i >= corner_points[0] && i <= corner_points[2] && j >= corner_points[1] && j <= corner_points[3])
                {
                    continue;
                }else{
                    return false;
                }
            }
        }
    }
    
    return true;
    /***************End your code here***************/
}