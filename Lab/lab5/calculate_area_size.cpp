#include "lab5_functions.h" // Include the declearation of the function

int area_size(const int arr[][MAX_DIMENSION], int row, int col, const int corner_points[]) {
    /***************Start your code here***************/
    int width = corner_points[3] - corner_points[1] + 1;
    int height = corner_points[2] - corner_points[0] + 1;
    return width * height;
    /***************End your code here***************/
}