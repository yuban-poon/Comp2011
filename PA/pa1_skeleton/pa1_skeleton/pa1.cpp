// === Region: Project Declaration ===
//
//  COMP2011 Fall 2023
//  PA1: A Simpified Robot Wars Game
//
//  Your name: PAN Rubin
//  Your ITSC email: rpanac@connect.ust.hk
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA: CHUNG, Peter (cspeter@cse.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
// =====================================

// === Region: Headers ===
// iostream and cstring are included.
// Do not include extra header files
// =======================
#include <iostream>
#include <cstring>
using namespace std;

// === Region: Constants ===
// Useful constants are defined for this project assignment
// =======================
const int MAX_ROWS = 20;
const int MAX_COLS = 30;
const int MAX_ACTION_TEXT_LENGTH = 10 + 1;    // array size for the action text, +1 for the NULL character
const int MAX_DIRECTION_TEXT_LENGTH = 10 + 1; // array size for the direction text, +1 for the NULL character
const int MAX_NUM_ROBOTS = 26;                // Note: Robots are named from A..Z
const char CHAR_EMPTY = '.';
const char CHAR_END_INPUT = '!';
const char DIRECTION_EAST = 'e';
const char DIRECTION_WEST = 'w';
const char DIRECTION_SOUTH = 's';
const char DIRECTION_NORTH = 'n';
const char DIRECTION_ERROR = '!';
const char DIRECTION_EAST_TEXT[] = "east";
const char DIRECTION_WEST_TEXT[] = "west";
const char DIRECTION_SOUTH_TEXT[] = "south";
const char DIRECTION_NORTH_TEXT[] = "north";
const char DIRECTION_ERROR_TEXT[] = "error";
const char ACTION_MOVE = 'm';
const char ACTION_HIT = 'h';
const char ACTION_SHOOT = 's';
const char ACTION_ERROR = '!';
const char ACTION_MOVE_TEXT[] = "moves";
const char ACTION_HIT_TEXT[] = "hits";
const char ACTION_SHOOT_TEXT[] = "shoots";
const int STATUS_ACTION_MOVE_NOT_IMPLMENTED = 0;
const int STATUS_ACTION_MOVE_SUCCESS = 1;
const int STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY = 2;
const int STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH = 3;

// Weapon: for the hit action
const int WEAPON_HIT_DAMAGE = 200;

// Weapon: for the shoot action
const int WEAPON_SHOOT_DAMAGE = 100;
const int WEAPON_SHOOT_RANGE = 5;

const int STATUS_ACTION_WEAPON_NOT_IMPLEMENTED = 0;
const int STATUS_ACTION_WEAPON_SUCCESS = 1;
const int STATUS_ACTION_WEAPON_FAIL = 2;

// Helper function: mapping the robotLetter to the correct array index
// e.g., 'A'=>0, 'B'=>1, ...
int robotLetterToArrayIndex(const char robotLetter)
{
    return int(robotLetter - 'A');
}

// Helper function: mapping array index to the robot letter
// e.g., 0=>'A', 1=>'B', ...
char arrayIndexToRobotLetter(const int index)
{
    return char(index + 'A');
}

// Helper function: convert an action text to a letter
// It is easier to compare characters than strings
char actionTextToLetter(const char actionText[MAX_ACTION_TEXT_LENGTH])
{
    // In this game, only 3 possible values
    if (strcmp(actionText, ACTION_MOVE_TEXT) == 0)
    {
        return ACTION_MOVE;
    }
    else if (strcmp(actionText, ACTION_HIT_TEXT) == 0)
    {
        return ACTION_HIT;
    }
    else if (strcmp(actionText, ACTION_SHOOT_TEXT) == 0)
    {
        return ACTION_SHOOT;
    }
    return ACTION_ERROR;
}

// Helper function: convert a direction text to a letter
// It is easier to compare characters than strings
char directionTextToLetter(const char directionText[MAX_DIRECTION_TEXT_LENGTH])
{
    // In this game, only 4 possible directions
    if (strcmp(directionText, DIRECTION_EAST_TEXT) == 0)
    {
        return DIRECTION_EAST;
    }
    else if (strcmp(directionText, DIRECTION_SOUTH_TEXT) == 0)
    {
        return DIRECTION_SOUTH;
    }
    else if (strcmp(directionText, DIRECTION_WEST_TEXT) == 0)
    {
        return DIRECTION_WEST;
    }
    else if (strcmp(directionText, DIRECTION_NORTH_TEXT) == 0)
    {
        return DIRECTION_NORTH;
    }
    return DIRECTION_ERROR;
}

// Helper function: convert a direction letter to text
const char *letterToDirectionText(char direction)
{
    if (direction == DIRECTION_EAST)
        return DIRECTION_EAST_TEXT;
    else if (direction == DIRECTION_SOUTH)
        return DIRECTION_SOUTH_TEXT;
    else if (direction == DIRECTION_WEST)
        return DIRECTION_WEST_TEXT;
    else if (direction == DIRECTION_NORTH)
        return DIRECTION_NORTH_TEXT;
    return DIRECTION_ERROR_TEXT;
}

// Helper function: Initialize the 2D array with an empty character
void initializeMap(char map[MAX_ROWS][MAX_COLS], const int numRows, const int numCols)
{
    int r, c;
    for (r = 0; r < numRows; r++)
        for (c = 0; c < numCols; c++)
            map[r][c] = CHAR_EMPTY;
}

// Helper function: Initialize the 1D array with zeros
void initializeHealthPoints(int healthPoints[MAX_NUM_ROBOTS])
{
    int i;
    for (i = 0; i < MAX_NUM_ROBOTS; i++)
        healthPoints[i] = 0;
}

// Helper function: Read the map information
void readInputMap(char map[MAX_ROWS][MAX_COLS], int &mapRows, int &mapCols)
{
    int r, c;
    char line[MAX_COLS + 1]; // character array to store each line

    // Read the game map
    cin >> mapRows >> mapCols;
    initializeMap(map, mapRows, mapCols);

    cin.ignore(); // ignore the end line character in this line
    for (r = 0; r < mapRows; r++)
    {
        cin.getline(line, MAX_COLS + 1);
        for (c = 0; c < mapCols; c++)
            map[r][c] = line[c];
    }
}

// Helper function: Read the robot information
void readInputHealthPoints(int healthPoints[MAX_NUM_ROBOTS])
{
    int numRobots, hp, i;
    char robotLetter;

    initializeHealthPoints(healthPoints);
    // Read robot letters and health points
    cin >> numRobots;
    for (i = 0; i < numRobots; i++)
    {
        cin >> robotLetter >> hp;
        // cout << robotLetter << hp << endl;
        healthPoints[robotLetterToArrayIndex(robotLetter)] = hp;
    }
}

// Helper function: Display the game map
void displayMap(const char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols)
{
    int r, c;
    for (r = 0; r < mapRows; r++)
    {
        for (c = 0; c < mapCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

// Helper function: Display the health point information
void displayHealthPoints(const int healthPoints[MAX_NUM_ROBOTS])
{
    int i, hp;
    for (i = 0; i < MAX_NUM_ROBOTS; i++)
    {
        hp = healthPoints[i];
        if (hp > 0)
        {
            cout << "Robot " << arrayIndexToRobotLetter(i) << " HP=" << hp << endl;
        }
    }
}

// TODO:
// function updateHealthPointsForHitAction: updates the map, healthPoints, and returns the values to the main function after the hit action
//
// @param healthPoints: a 1D array storing the healthPoints of robots
// @param map: a 2D character array storing the game map
// @param mapRows: the number of rows of the game map
// @param mapCols: the number of columns of the game map
// @param robotLetter: the robot to be moved
// @param directionLetter: the movement direction
// @param targetRobotLetter: the target robot.
// @param targetOriginalHealthPoint: the original health point of the target robot.
// @param targetUpdatedHealthPoint: the updated health point of the target robot.
//
//  Note: The pass-by-reference variables will be returned and used in the main function.
//
// @return: the status value, please check the constant values near the top of the starter code.
// The main function may also help you understand the meanings of the possible return values
int updateHealthPointsForHitAction(int healthPoints[MAX_NUM_ROBOTS],
                                   char map[MAX_ROWS][MAX_COLS],
                                   const int mapRows, const int mapCols,
                                   const char robotLetter,
                                   const char directionLetter,
                                   char &targetRobotLetter,
                                   int &targetOriginalHealthPoint,
                                   int &targetUpdatedHealthPoint)
{
    for(int i = 0; i < mapRows; i++){
        for(int j = 0; j < mapCols; j++){
            if(map[i][j] == robotLetter){
                switch (directionLetter)
                {
                case DIRECTION_EAST:
                    if(map[i][j + 1] != CHAR_EMPTY && j + 1 < mapCols){
                        //update the information of target robot letter
                        targetRobotLetter = map[i][j + 1];
                        targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                        targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_HIT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_HIT_DAMAGE;
                        healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                        if (targetUpdatedHealthPoint == 0)
                        {
                            map[i][j + 1] = CHAR_EMPTY;
                        }
                        return STATUS_ACTION_WEAPON_SUCCESS;
                    }
                    break;
                case DIRECTION_WEST:
                    if(map[i][j - 1] != CHAR_EMPTY && j - 1 >= 0){
                        //update the information of target robot letter
                        targetRobotLetter = map[i][j - 1];
                        targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                        targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_HIT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_HIT_DAMAGE;
                        healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                        if (targetUpdatedHealthPoint == 0)
                        {
                            map[i][j - 1] = CHAR_EMPTY;
                        }
                        return STATUS_ACTION_WEAPON_SUCCESS;
                    }
                    break;
                case DIRECTION_SOUTH:
                    if(map[i + 1][j] != CHAR_EMPTY && i + 1 < mapRows){
                        //update the information of target robot letter
                        targetRobotLetter = map[i + 1][j];
                        targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                        targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_HIT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_HIT_DAMAGE;
                        healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                        if (targetUpdatedHealthPoint == 0)
                        {
                            map[i + 1][j] = CHAR_EMPTY;
                        }
                        return STATUS_ACTION_WEAPON_SUCCESS;
                    }
                    break;
                case DIRECTION_NORTH:
                    if(map[i - 1][j] != CHAR_EMPTY && i - 1 >= 0){
                        //update the information of target robot letter
                        targetRobotLetter = map[i - 1][j];
                        targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                        targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_HIT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_HIT_DAMAGE;
                        healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                        if (targetUpdatedHealthPoint == 0)
                        {
                            map[i - 1][j] = CHAR_EMPTY;
                        }
                        return STATUS_ACTION_WEAPON_SUCCESS;
                    }
                    break;
                default:
                    return STATUS_ACTION_WEAPON_NOT_IMPLEMENTED;
                }
                return STATUS_ACTION_WEAPON_FAIL;
            }
        }
    }
    return STATUS_ACTION_WEAPON_NOT_IMPLEMENTED;
}

// TODO:
// function updateHealthPointsForShootAction: updates the map, healthPoints, and returns the values to the main function after the shoot action
//
// @param healthPoints: a 1D array storing the healthPoints of robots
// @param map: a 2D character array storing the game map
// @param mapRows: the number of rows of the game map
// @param mapCols: the number of columns of the game map
// @param robotLetter: the robot to be moved
// @param directionLetter: the movement direction
// @param targetRobotLetter: the target robot.
// @param targetOriginalHealthPoint: the original health point of the target robot.
// @param targetUpdatedHealthPoint: the updated health point of the target robot.
//
//  Note: The pass-by-reference variables will be returned and used in the main function.
//
// @return: the status value, please check the constant values near the top of the starter code.
// The main function may also help you understand the meanings of the possible return values
int updateHealthPointsForShootAction(int healthPoints[MAX_NUM_ROBOTS],
                                     char map[MAX_ROWS][MAX_COLS],
                                     const int mapRows, const int mapCols,
                                     const char robotLetter,
                                     const char directionLetter,
                                     char &targetRobotLetter,
                                     int &targetOriginalHealthPoint,
                                     int &targetUpdatedHealthPoint)
{
    for(int i = 0; i < mapRows; i++){
        for(int j = 0; j < mapCols; j++){
            if(map[i][j] == robotLetter){
                switch (directionLetter)
                {
                case DIRECTION_EAST:
                    for(int k = 1; k <= WEAPON_SHOOT_RANGE; k++){
                        if(map[i][j + k] != CHAR_EMPTY && j + k < mapCols){
                            //update the information of target robot letter
                            targetRobotLetter = map[i][j + k];
                            targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                            targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE;
                            healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                            if (targetUpdatedHealthPoint == 0)
                            {
                                map[i][j + k] = CHAR_EMPTY;
                            }
                            return STATUS_ACTION_WEAPON_SUCCESS;
                        }
                    }
                    break;
                case DIRECTION_WEST:
                    for(int k = 1; k <= WEAPON_SHOOT_RANGE; k++){
                        if(map[i][j - k] != CHAR_EMPTY && j - k >= 0){
                            //update the information of target robot letter
                            targetRobotLetter = map[i][j - k];
                            targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                            targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE;
                            healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                            if (targetUpdatedHealthPoint == 0)
                            {
                                map[i][j - k] = CHAR_EMPTY;
                            }
                            return STATUS_ACTION_WEAPON_SUCCESS;
                        }
                    }
                    break;
                case DIRECTION_SOUTH:
                    for(int k = 1; k <= WEAPON_SHOOT_RANGE; k++){
                        if(map[i + k][j] != CHAR_EMPTY && i + k < mapRows){
                            //update the information of target robot letter
                            targetRobotLetter = map[i + k][j];
                            targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                            targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE;
                            healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                            if (targetUpdatedHealthPoint == 0)
                            {
                                map[i + k][j] = CHAR_EMPTY;
                            }
                            return STATUS_ACTION_WEAPON_SUCCESS;
                        }
                    }
                    break;
                case DIRECTION_NORTH:
                    for(int k = 1; k <= WEAPON_SHOOT_RANGE; k++){
                        if(map[i - k][j] != CHAR_EMPTY && i - k >= 0){
                            //update the information of target robot letter
                            targetRobotLetter = map[i - k][j];
                            targetOriginalHealthPoint = healthPoints[robotLetterToArrayIndex(targetRobotLetter)];
                            targetUpdatedHealthPoint = (targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE < 0) ? 0 : targetOriginalHealthPoint - WEAPON_SHOOT_DAMAGE;
                            healthPoints[robotLetterToArrayIndex(targetRobotLetter)] = targetUpdatedHealthPoint;
                            if (targetUpdatedHealthPoint == 0)
                            {
                               map[i - k][j] = CHAR_EMPTY;
                            }
                            return STATUS_ACTION_WEAPON_SUCCESS;
                        }
                    }
                    break;
                default:
                    return STATUS_ACTION_WEAPON_NOT_IMPLEMENTED;
                }
                return STATUS_ACTION_WEAPON_FAIL;
            }
        }
    }
    return STATUS_ACTION_WEAPON_NOT_IMPLEMENTED;
}

// TODO:
// function updateMapForMoveAction: updates the map and returns the status value after the robot movement
// @param map: a 2D character array storing the game map
// @param mapRows: the number of rows of the game map
// @param mapCols: the number of columns of the game map
// @param robotLetter: the robot to be moved
// @param directionLetter: the movement direction
// @param moveSteps: the number of steps to be moved along the direction
//
// @return: the status value, please check the constant values near the top of the starter code.
// The main function may also help you understand the meanings of the possible return values
//
int updateMapForMoveAction(char map[MAX_ROWS][MAX_COLS], const int mapRows, const int mapCols,
                           const char robotLetter, const char directionLetter, const int moveSteps)
{
    for(int i = 0; i < mapRows; i++){
        for(int j = 0; j < mapCols; j++){
            if(map[i][j] == robotLetter){
                switch (directionLetter){
                    case DIRECTION_EAST:
                        for(int k = 1; k <= moveSteps; k++){
                            if(j + k < mapCols){
                                if(map[i][j + k] != CHAR_EMPTY){
                                    return STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH;
                                }
                            }
                            else {
                                return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
                            }
                        }
                        map[i][j] = CHAR_EMPTY;
                        map[i][j + moveSteps] = robotLetter;
                        break;
                    case DIRECTION_WEST:
                        for(int k = 1; k <= moveSteps; k++){
                            if(j - k >= 0){
                                if(map[i][j - k] != CHAR_EMPTY){
                                    return STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH;
                                }
                            }
                            else{
                                return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
                            }
                        }
                        map[i][j] = CHAR_EMPTY;
                        map[i][j - moveSteps] = robotLetter;
                        break;
                    case DIRECTION_SOUTH:
                        for(int k = 1; k <= moveSteps; k++){
                            if(i + k < mapRows){
                                if(map[i + k][j] != CHAR_EMPTY){
                                    return STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH;
                                }
                            }
                            else{
                                return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
                            }
                        }
                        map[i][j] = CHAR_EMPTY;
                        map[i + moveSteps][j] = robotLetter;
                        break;
                    case DIRECTION_NORTH:
                        for(int k = 1; k <= moveSteps; k++){
                            if(i - k >= 0){
                                if(map[i - k][j] != CHAR_EMPTY){
                                    return STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH;
                                }
                            }
                            else{
                                return STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY;
                            }
                        }
                        map[i][j] = CHAR_EMPTY;
                        map[i - moveSteps][j] = robotLetter;
                        break;
                    default:
                        return STATUS_ACTION_MOVE_NOT_IMPLMENTED;
                }
                return STATUS_ACTION_MOVE_SUCCESS;
            }
        }
    }
    return STATUS_ACTION_MOVE_NOT_IMPLMENTED;
}

/**
 * function: the main function
 *
 * Note: The main function is given. 
 * DO NOT modify anything inside the main function
 */
int main()
{
    char map[MAX_ROWS][MAX_COLS];
    int healthPoints[MAX_NUM_ROBOTS];
    int mapRows, mapCols, moveSteps;
    int statusMove, statusHit, statusShoot;
    char robotLetter, actionLetter, directionLetter;
    char actionText[MAX_ACTION_TEXT_LENGTH];
    char directionText[MAX_DIRECTION_TEXT_LENGTH];
    char targetRobotLetter;
    int targetOriginalHealthPoint;
    int targetUpdatedHealthPoint;

    // Start by reading the input
    // Usage:
    //
    // ./pa1 < testcase/inputX.txt
    //
    // Alternatively, you can type in the content lines by lines

    readInputHealthPoints(healthPoints);
    readInputMap(map, mapRows, mapCols);

    cout << "The initial game information:" << endl;
    displayHealthPoints(healthPoints);
    displayMap(map, mapRows, mapCols);

    while (true)
    {
        cin >> robotLetter;
        if (robotLetter == CHAR_END_INPUT)
            break; // End of the game

        // if the robot letter is not the end of the game
        // read the action text and the direction letter
        cin >> actionText >> directionText;
        actionLetter = actionTextToLetter(actionText);
        directionLetter = directionTextToLetter(directionText);
        if (actionLetter == ACTION_MOVE)
        {
            // need to read the steps if the action is ACTION_MOVE
            cin >> moveSteps;

            statusMove = updateMapForMoveAction(map, mapRows, mapCols, robotLetter, directionLetter, moveSteps);

            if (statusMove == STATUS_ACTION_MOVE_NOT_IMPLMENTED)
            {
                cout << "The move action is not implemented yet" << endl;
            }
            else if (statusMove == STATUS_ACTION_MOVE_SUCCESS)
            {
                cout << "Success: "
                     << "Robot " << robotLetter << " moves along the direction " << letterToDirectionText(directionLetter) << " by " << moveSteps << " step(s)" << endl;
                displayMap(map, mapRows, mapCols);
            }
            else if (statusMove == STATUS_ACTION_MOVE_OUTSIDE_BOUNDARY)
            {
                cout << "Fail: "
                     << "If robot " << robotLetter << " moves along the direction " << letterToDirectionText(directionLetter) << " by " << moveSteps << " step(s)"
                     << ", it will move outside a boundary, so the position remains unchanged" << endl;
                displayMap(map, mapRows, mapCols);
            }
            else if (statusMove == STATUS_ACTION_MOVE_HIT_ANOTHER_ROBOT_ALONG_PATH)
            {
                cout << "Fail: "
                     << "If robot " << robotLetter << " moves along the direction " << letterToDirectionText(directionLetter) << " by " << moveSteps << " step(s)"
                     << ", it will hit another robot along the path, so the position remains unchanged" << endl;
                displayMap(map, mapRows, mapCols);
            }
        } 
        else if (actionLetter == ACTION_HIT)
        {
            statusHit = updateHealthPointsForHitAction(healthPoints, map, mapRows, mapCols, robotLetter, directionLetter, targetRobotLetter, targetOriginalHealthPoint, targetUpdatedHealthPoint);
            if (statusHit == STATUS_ACTION_WEAPON_NOT_IMPLEMENTED)
            {
                cout << "The hit action is not implemented yet" << endl;
            }
            else if (statusHit == STATUS_ACTION_WEAPON_SUCCESS)
            {

                cout << "Success: "
                     << "Robot " << robotLetter << " hits " << targetRobotLetter << endl;
                cout << "Robot " << targetRobotLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                if (targetUpdatedHealthPoint == 0)
                {
                    cout << "Robot " << targetRobotLetter << " is being destroyed by " << robotLetter << endl;
                    displayMap(map, mapRows, mapCols);
                }
                cout << "== Health points of alive robots ==" << endl;
                displayHealthPoints(healthPoints);
            }
            else if (statusHit == STATUS_ACTION_WEAPON_FAIL)
            {
                cout << "Fail: "
                     << "Robot " << robotLetter << " cannot hit any target" << endl;
                cout << "== Health points of alive robots ==" << endl;
                displayHealthPoints(healthPoints);
            }
        }
        else if (actionLetter == ACTION_SHOOT)
        {
            statusShoot = updateHealthPointsForShootAction(healthPoints, map, mapRows, mapCols, robotLetter, directionLetter, targetRobotLetter, targetOriginalHealthPoint, targetUpdatedHealthPoint);
            if (statusShoot == STATUS_ACTION_WEAPON_NOT_IMPLEMENTED)
            {
                cout << "The shoot action is not implemented yet" << endl;
            }
            else if (statusShoot == STATUS_ACTION_WEAPON_SUCCESS)
            {
                cout << "Success: "
                     << "Robot " << robotLetter << " shoots " << targetRobotLetter << endl;
                cout << "Robot " << targetRobotLetter << " health point is reduced from " << targetOriginalHealthPoint << " to " << targetUpdatedHealthPoint << endl;
                if (targetUpdatedHealthPoint == 0)
                {
                    cout << "Robot " << targetRobotLetter << " is being destroyed by " << robotLetter << endl;
                    displayMap(map, mapRows, mapCols);
                }
                cout << "== Health points of alive robots ==" << endl;
                displayHealthPoints(healthPoints);
            }
            else if (statusShoot == STATUS_ACTION_WEAPON_FAIL)
            {
                cout << "Fail: "
                     << "Robot " << robotLetter << " cannot shoot any target" << endl;
                cout << "== Health points of alive robots ==" << endl;
                displayHealthPoints(healthPoints);
            }
        }
    }
    cout << "=== Game Ended ===" << endl;
    return 0;
}