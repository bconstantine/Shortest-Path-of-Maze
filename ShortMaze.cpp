#include <iostream>
using namespace std;

struct Coordinate
{
    int y;
    int x;
};

struct Node
{
    Coordinate curPoint;
    int curLength;
    int direction;
    Node* next;
    Node* prev;
};

//0 up,
//1 right,
//2 down,
//3 left
//-1 means no, e.g start
bool directionAvail(Node* &currentNode, Node* &head, char** maze, int row, int col)
{
    bool dontForward = false;
    short oneFound = -1;
    short twoFound = -1;
    short threeFound = -1;
    short fourFound = -1;

    if (currentNode == NULL || head == NULL)
    {
        return false;
    }
    if (currentNode->curPoint.y > 0)
    {
        if (maze[currentNode->curPoint.y - 1][currentNode->curPoint.x] == '*' || maze[currentNode->curPoint.y - 1][currentNode->curPoint.x] == '@')
        {
            if (currentNode->direction != 2)
            {
                oneFound = 0;
            }
            
        }
    }

    if (currentNode->curPoint.x < col - 1)
    {
        if (maze[currentNode->curPoint.y][currentNode->curPoint.x + 1] == '*' || maze[currentNode->curPoint.y][currentNode->curPoint.x + 1] == '@')
        {
            if (currentNode->direction != 3)
            {
                if (oneFound != -1)
                {
                    twoFound = 1;
                }
                else
                {
                    oneFound = 1;
                }
            }

        }
    }

    if (currentNode->curPoint.y < row - 1)
    {
        if (maze[currentNode->curPoint.y+1][currentNode->curPoint.x] == '*' || maze[currentNode->curPoint.y + 1][currentNode->curPoint.x] == '@')
        {
            if (currentNode->direction != 0)
            {
                if (oneFound != -1)
                {
                    if (twoFound != -1)
                    {
                        threeFound = 2;
                    }
                    else
                    {
                        twoFound = 2;
                    }
                }
                else
                {
                    oneFound = 2;
                }
            }

        }
    }

    if (currentNode->curPoint.x > 0)
    {
        if (maze[currentNode->curPoint.y][currentNode->curPoint.x - 1] == '*' || maze[currentNode->curPoint.y][currentNode->curPoint.x - 1] == '@')
        {
            if (currentNode->direction != 1)
            {
                if (oneFound != -1)
                {
                    if (twoFound != -1)
                    {
                        if (threeFound != -1)
                        {
                            fourFound = 3;
                        }
                        else
                        {
                            threeFound = 3;
                        }
                    }
                    else
                    {
                        twoFound = 3;
                    }
                }
                else
                {
                    oneFound = 3;
                }
            }

        }
    }

    if (oneFound == -1)
    {
        if (currentNode == head)
        {
            head = currentNode->next;
        }
        if (currentNode->prev != NULL)
        {
            currentNode->prev->next = currentNode->next;
        }
        if (currentNode->next != NULL)
        {
            currentNode->next->prev = currentNode->prev;
        }
        Node* erase = currentNode;
        if (currentNode->next == NULL)
        {
            currentNode = NULL;
        }
        else
        {
            currentNode = currentNode->next;
        }
        //currentNode = currentNode->next;
        dontForward = true;
        //delete erase; //freeing the currentNode;
    }
    else if (twoFound == -1)
    {
        //cout << "Enter here2\n";
        currentNode->direction = oneFound;
        if (oneFound == 0)
        {
            currentNode->curPoint.y--;
        }
        else if (oneFound == 1)
        {
            currentNode->curPoint.x++;
        }
        else if (oneFound == 2)
        {
            currentNode->curPoint.y++;
        }
        else
        {
            currentNode->curPoint.x--;
        }
        currentNode->curLength++;
        maze[currentNode->curPoint.y][currentNode->curPoint.x] = 'a';
    }
    else if(threeFound == -1)
    {
       //found two
        Node* newNode1 = new Node; // insert new node
        newNode1->curLength = currentNode->curLength + 1;
        currentNode->curLength++;
        newNode1->curPoint = currentNode->curPoint;
        currentNode->direction = twoFound;
        newNode1->direction = oneFound;
        if (oneFound == 0)
        {
            newNode1->curPoint.y--;;
        }
        else if (oneFound == 1)
        {
            newNode1->curPoint.x++;
        }
        else if (oneFound == 2)
        {
            newNode1->curPoint.y++;
        }
        else
        {
            newNode1->curPoint.x--;
        }

        if (twoFound == 0)
        {
            currentNode->curPoint.y--;;
        }
        else if (twoFound == 1)
        {
            currentNode->curPoint.x++;
        }
        else if (twoFound == 2)
        {
            currentNode->curPoint.y++;
        }
        else
        {
            currentNode->curPoint.x--;
        }
        
        //inserting the newNode1 behind the currentNode
        newNode1->prev = currentNode->prev;
        if (newNode1->prev == NULL)
        {
            head = newNode1;
        }
        else
        {
            if (currentNode->prev != NULL)
            {

                currentNode->prev->next = newNode1;

            }
        }
        newNode1->next = currentNode;
        currentNode->prev = newNode1;
        maze[currentNode->curPoint.y][currentNode->curPoint.x] = 'a';
        maze[newNode1->curPoint.y][newNode1->curPoint.x] = 'a';
    }
    else if(fourFound == -1)
    {
        Node* newNode1 = new Node; // insert new node
        Node* newNode2 = new Node;
        newNode1->curLength = currentNode->curLength + 1;
        newNode2->curLength = currentNode->curLength + 1;
        currentNode->curLength++;
        newNode1->curPoint = currentNode->curPoint;
        newNode2->curPoint = currentNode->curPoint;
        currentNode->direction = threeFound;
        newNode1->direction = oneFound;
        newNode2->direction = twoFound;
        if (oneFound == 0)
        {
            newNode1->curPoint.y--;;
        }
        else if (oneFound == 1)
        {
            newNode1->curPoint.x++;
        }
        else if (oneFound == 2)
        {
            newNode1->curPoint.y++;
        }
        else
        {
            newNode1->curPoint.x--;
        }

        if (twoFound == 0)
        {
            newNode2->curPoint.y--;;
        }
        else if (twoFound == 1)
        {
            newNode2->curPoint.x++;
        }
        else if (twoFound == 2)
        {
            newNode2->curPoint.y++;
        }
        else
        {
            newNode2->curPoint.x--;
        }

        if (threeFound == 0)
        {
            currentNode->curPoint.y--;;
        }
        else if (threeFound == 1)
        {
            currentNode->curPoint.x++;
        }
        else if (threeFound == 2)
        {
            currentNode->curPoint.y++;
        }
        else
        {
            currentNode->curPoint.x--;
        }

        //inserting the newNode1 behind the currentNode
        newNode1->prev = currentNode->prev;
        if (newNode1->prev == NULL)
        {
            head = newNode1;
        }
        else
        {
            currentNode->prev->next = newNode1;
        }
        newNode1->next = newNode2;
        newNode2->prev = newNode1;
        newNode2->next = currentNode;
        currentNode->prev = newNode2;
        maze[currentNode->curPoint.y][currentNode->curPoint.x] = 'a';
        maze[newNode1->curPoint.y][newNode1->curPoint.x] = 'a';
        maze[newNode2->curPoint.y][newNode2->curPoint.x] = 'a';
    }
    else
    {
        //found four
        Node* newNode1 = new Node; 
        Node* newNode2 = new Node;
        Node* newNode3 = new Node;
        newNode1->curLength = currentNode->curLength + 1;
        newNode2->curLength = currentNode->curLength + 1;
        newNode3->curLength = currentNode->curLength + 1;
        currentNode->curLength++;
        newNode1->curPoint = currentNode->curPoint;
        newNode2->curPoint = currentNode->curPoint;
        newNode3->curPoint = currentNode->curPoint;
        currentNode->direction = fourFound;
        newNode1->direction = oneFound;
        newNode2->direction = twoFound;
        newNode3->direction = threeFound;
        if (oneFound == 0)
        {
            newNode1->curPoint.y--;;
        }
        else if (oneFound == 1)
        {
            newNode1->curPoint.x++;
        }
        else if (oneFound == 2)
        {
            newNode1->curPoint.y++;
        }
        else
        {
            newNode1->curPoint.x--;
        }

        if (twoFound == 0)
        {
            newNode2->curPoint.y--;;
        }
        else if (twoFound == 1)
        {
            newNode2->curPoint.x++;
        }
        else if (twoFound == 2)
        {
            newNode2->curPoint.y++;
        }
        else
        {
            newNode2->curPoint.x--;
        }

        if (threeFound == 0)
        {
            newNode3->curPoint.y--;;
        }
        else if (threeFound == 1)
        {
            newNode3->curPoint.x++;
        }
        else if (threeFound == 2)
        {
            newNode3->curPoint.y++;
        }
        else
        {
            newNode3->curPoint.x--;
        }

        if (fourFound == 0)
        {
            currentNode->curPoint.y--;;
        }
        else if (fourFound == 1)
        {
            currentNode->curPoint.x++;
        }
        else if (fourFound == 2)
        {
            currentNode->curPoint.y++;
        }
        else
        {
            currentNode->curPoint.x--;
        }

        //inserting the newNode1 behind the currentNode
        newNode1->prev = currentNode->prev;
        if (newNode1->prev == NULL)
        {
            head = newNode1;
        }
        else
        {
            currentNode->prev->next = newNode1;
        }
        newNode1->next = newNode2;
        newNode2->prev = newNode1;
        newNode2->next = newNode3;
        newNode3->prev = newNode2;
        newNode3->next = currentNode;
        currentNode->prev = newNode3;
        maze[currentNode->curPoint.y][currentNode->curPoint.x] = 'a';
        maze[newNode1->curPoint.y][newNode1->curPoint.x] = 'a';
        maze[newNode2->curPoint.y][newNode2->curPoint.x] = 'a';
        maze[newNode3->curPoint.y][newNode3->curPoint.x] = 'a';
    }
    return dontForward;
}

bool empty(Node** head,  Coordinate finish, int &shortest)
{
    bool found = false;
    //bool empty = true;
    Node* erase;
    Node* current = *head;
    //mistake in here when the empty is equal to shortest
    while (current != NULL)
    {
        if (current->curPoint.x == finish.x && current->curPoint.y == finish.y)
        {
            //cout << "YES!\n";
            shortest = current->curLength;
            found = true;
            break;
        }
        else
        {
            current = current->next;
        }
    }
    return found;
    //return empty;
}

int main()
{
    int row;
    int col;
    while (cin >> row >> col)
    {
        //# wall
        //. starting point
        //* aisle
        //@ exit
        char** maze = new char* [row];
        for (int i = 0; i < row; i++)
        {
            maze[i] = new char[col];
        }

        Coordinate start = { -1,-1 };
        Coordinate finish = { -1,-1 };
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cin >> maze[i][j];
                if (maze[i][j] == '.')
                {
                    if (start.x != -1 && start.y != -1)
                    {
                        return -1;
                    }
                    else
                    {
                        start.y = i;
                        start.x = j;
                    }
                }
                else if (maze[i][j] == '@')
                {
                    if (finish.x != -1 && finish.y != -1)
                    {
                        return -1;
                    }
                    else
                    {
                        finish.y = i;
                        finish.x = j;
                    }
                }
            }
        }

        if (start.x == -1 && start.y == -1 || finish.x == -1 && finish.y == -1)
        {
            cout << 0 << endl;
            return 0;
        }

        Node* head = new Node;
        int shortest = 2147483647; //close to int max
        Node* current = head;
        current->curLength = 0;
        current->curPoint = start;
        current->direction = -1;
        current->next = NULL;
        current->prev = NULL;
        bool dontForward;
        bool found = false;
        while (head != NULL)
        {
            dontForward = directionAvail(current, head, maze, row, col);
            Node* currentParsing = head;
            if (head == NULL)
            {
                currentParsing = NULL;
            }
            if (!dontForward)
            {
                if (current->next == NULL)
                {
                    if (empty(&head, finish, shortest))
                    {
                        found = true;
                        break;
                    }
                    current = head;
                }
                else
                {
                    current = current->next;
                }
            }
            else
            {
                if (current == NULL)
                {
                    if (empty(&head, finish, shortest))
                    {
                        found = true;
                        break;
                    }
                    //empty(&head, finish, shortest);
                    current = head;
                }
            }
        }
        if (found == false)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << shortest << endl;
        }
    }
}
