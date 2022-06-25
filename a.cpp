#include <bits/stdc++.h>
using namespace std;

void PrintPath(vector<vector<int>> v)
{

    for (auto i : v)
    {
        cout << "  ";
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << "\n";
    }
}

struct PuzzleNode
{
    int n, m;
    int x, y;
    vector<vector<int>> grid;
    PuzzleNode *parent;
    int costG, costH;

    PuzzleNode(vector<vector<int>> arr)
    {

        this->n = arr.size();
        this->m = arr[0].size();
        this->costG = 0;
        this->costH = 0;
        this->parent = NULL;

        for (int i = 0; i < n; i++)
        {
            vector<int> temp;
            for (int j = 0; j < m; j++)
            {
                temp.push_back(arr[i][j]);
                if (arr[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
                else
                {
                    int curr = arr[i][j] - 1;
                    int I = curr / m;
                    int J = curr % m;
                    this->costH += (abs(i - I) + abs(j - J));
                }
            }
            grid.push_back(temp);
        }
    }

    bool isValid()
    {
        vector<int> flattenGrid;
        int sz = n * m;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                flattenGrid.push_back(grid[i][j]);
            }
        }

        sort(flattenGrid.begin(), flattenGrid.end());

        int cnt = 0;
        for (int i = 0; i < sz; i++)
        {
            if (flattenGrid[i] != cnt)
                return false;
            cnt++;
        }

        return true;
    }

    bool isDestinationNode()
    {
        int cnt = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == n - 1 && j == m - 1)
                    continue;
                else if (grid[i][j] != cnt)
                    return false;
                cnt++;
            }
        }
        return true;
    }

    bool isSolvable()
    {
        vector<int> flattenGrid;
        int sz = n * m;
        cout<<sz<<"\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j]!=0)
                {
                    flattenGrid.push_back(grid[i][j]);
                }
            }
        }
        int noOfInversions = 0;

        for (int i = 0; i < sz - 1; i++)
        {
            for (int j = i + 1; j < sz; j++)
            {
                if (flattenGrid[i] > flattenGrid[j])
                {
                    cout<<flattenGrid[i]<<" "<<flattenGrid[j]<<"\n";
                    noOfInversions++;
                }
            }
        }
        cout<<"Inversions= "<<noOfInversions<<"\n";
        return ((noOfInversions % 2) == 0);
    }
};

struct CompareTotalCost
{
    bool operator()(PuzzleNode *p1, PuzzleNode *p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return ((p1->costG + p1->costH) > (p2->costG + p2->costH));
    }
};

class PuzzleSolver
{
private:
    int r[4] = {0, 1, 0, -1};
    int c[4] = {-1, 0, 1, 0};
    PuzzleNode *puzzle;
    int iterations;

public:
    PuzzleSolver(PuzzleNode *curr)
    {
        this->puzzle = curr;
    }

    vector<vector<vector<int>>> solveByBFS()
    {
        iterations = 0;
        vector<vector<vector<int>>> path;
        PuzzleNode *answerNode = NULL;

        queue<PuzzleNode *> q;
        set<vector<vector<int>>> isVisited;
        this->puzzle->parent = NULL;
        q.push(this->puzzle);
        isVisited.insert(puzzle->grid);

        while (!q.empty())
        {
            iterations++;

            PuzzleNode *curr = q.front();
            q.pop();

            if (curr->isDestinationNode())
            {
                answerNode = curr;
                break;
            }

            for (int i = 0; i < 4; i++)
            {

                int X = curr->x + r[i];
                int Y = curr->y + c[i];

                if (X >= 0 && X < curr->n && Y >= 0 && Y < curr->m)
                {
                    vector<vector<int>> tempGrid = curr->grid;
                    swap(tempGrid[curr->x][curr->y], tempGrid[X][Y]);

                    if (isVisited.find(tempGrid) == isVisited.end())
                    {

                        PuzzleNode *tempNode = new PuzzleNode(tempGrid);

                        tempNode->parent = curr;

                        q.push(tempNode);

                        isVisited.insert(tempGrid);
                    }
                }
            }
        }

        while (answerNode != NULL)
        {
            path.push_back(answerNode->grid);
            answerNode = answerNode->parent;
        }

        return path;
    }

    bool DFS(PuzzleNode *puzzle, vector<vector<vector<int>>> &path, set<vector<vector<int>>> &isVisited)
    {
        iterations++;
        if (puzzle->isDestinationNode())
        {
            path.push_back(puzzle->grid);
            return true;
        }

        for (int i = 0; i < 4; i++)
        {

            int X = puzzle->x + r[i];
            int Y = puzzle->y + c[i];

            if (X >= 0 && X < puzzle->n && Y >= 0 && Y < puzzle->m)
            {
                vector<vector<int>> tempGrid = puzzle->grid;
                swap(tempGrid[puzzle->x][puzzle->y], tempGrid[X][Y]);

                if (isVisited.find(tempGrid) == isVisited.end())
                {
                    PuzzleNode *tempNode = new PuzzleNode(tempGrid);
                    tempNode->parent = puzzle;
                    isVisited.insert(tempGrid);
                    if (DFS(tempNode, path, isVisited))
                    {
                        path.push_back(puzzle->grid);
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool IDDFS(PuzzleNode *puzzle, vector<vector<vector<int>>> &path, set<vector<vector<int>>> &isVisited, int depth, int maxDepth)
    {
        iterations++;
        if (puzzle->isDestinationNode())
        {
            path.push_back(puzzle->grid);
            return true;
        }
        if (maxDepth < depth)
            return false;

        for (int i = 0; i < 4; i++)
        {

            int X = puzzle->x + r[i];
            int Y = puzzle->y + c[i];

            if (X >= 0 && X < puzzle->n && Y >= 0 && Y < puzzle->m)
            {
                vector<vector<int>> tempGrid = puzzle->grid;
                swap(tempGrid[puzzle->x][puzzle->y], tempGrid[X][Y]);

                if (isVisited.find(tempGrid) == isVisited.end())
                {
                    PuzzleNode *tempNode = new PuzzleNode(tempGrid);
                    tempNode->parent = puzzle;
                    isVisited.insert(tempGrid);
                    if (IDDFS(tempNode, path, isVisited, depth + 1, maxDepth))
                    {
                        path.push_back(puzzle->grid);
                        return true;
                    }
                }
            }
        }

        return false;
    }

    vector<vector<vector<int>>> solveByDFS()
    {
        iterations = 0;
        vector<vector<vector<int>>> path;
        set<vector<vector<int>>> isVisited;

        DFS(this->puzzle, path, isVisited);

        return path;
    }

    vector<vector<vector<int>>> solveByIDDFS()
    {
        iterations = 0;
        vector<vector<vector<int>>> path;
        set<vector<vector<int>>> isVisited;
        int maxDepth = 1;
        while (1)
        {
            if (IDDFS(this->puzzle, path, isVisited, 0, maxDepth) == true)
            {
                break;
            }
            isVisited.clear();
            path.clear();
            maxDepth++;
        }

        return path;
    }

    vector<vector<vector<int>>> solveByAStar()
    {
        iterations = 0;
        vector<vector<vector<int>>> path;
        PuzzleNode *answerNode = NULL;

        priority_queue<PuzzleNode *, vector<PuzzleNode *>, CompareTotalCost> q;
        // set<vector<vector<int>>> isVisited;
        this->puzzle->parent = NULL;
        this->puzzle->costG = 0;
        q.push(this->puzzle);
        // isVisited.insert(puzzle->grid);

        while (!q.empty())
        {
            iterations++;

            PuzzleNode *curr = q.top();
            q.pop();

            if (curr->isDestinationNode())
            {
                answerNode = curr;
                break;
            }

            for (int i = 0; i < 4; i++)
            {

                int X = curr->x + r[i];
                int Y = curr->y + c[i];

                if (X >= 0 && X < curr->n && Y >= 0 && Y < curr->m)
                {
                    vector<vector<int>> tempGrid = curr->grid;
                    swap(tempGrid[curr->x][curr->y], tempGrid[X][Y]);

                    // if (isVisited.find(tempGrid) == isVisited.end())
                    {

                        PuzzleNode *tempNode = new PuzzleNode(tempGrid);

                        tempNode->parent = curr;
                        tempNode->costG = curr->costG + 1;

                        q.push(tempNode);
                        // isVisited.insert(tempGrid);

                    }
                }
            }
        }

        while (answerNode != NULL)
        {
            // cout<<answerNode->costG<<" "<<answerNode->costH<<"\n";
            path.push_back(answerNode->grid);
            answerNode = answerNode->parent;
        }

        return path;
    }

    int getIterations()
    {
        return iterations;
    }
};

int main()
{
    cout << "Enter Dimensions of Puzzle Matrix (as number of rows & columns)\n";
    int n, m;
    cin >> n >> m;

    cout << "\n";
    cout << "Enter elements of puzzle matrix (Number ranging between 1 to " << (n * m - 1) << " & 0 for empty cell or silder cell)\n";
    vector<vector<int>> arr(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }
    cout << "\n";
    PuzzleNode *Game = new PuzzleNode(arr);
    if (!Game->isValid())
    {
        cout << "Puzzle is invalid, Please enter correct puzzle !!!\n";
        return 0;
    }
    // if (!Game->isSolvable())
    // {
        
    //     cout << "Can not find answer, since puzzle is not solvable!!!\n";
    //     return 0;
    // }

    PuzzleSolver *solver = new PuzzleSolver(Game);

    vector<vector<vector<int>>> path = solver->solveByAStar();

    cout << "\n";
    cout << "Printing Path:\n\n";
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        cout << i + 1 << ")\n";
        PrintPath(path[i]);
        cout << "\n";
    }

    cout << "Number of iterations for given algorithm to complete= " << solver->getIterations() << ".\n";
    cout << "\n";
    return 0;
}
// 3 3
// 0 7 6
// 1 4 3
// 2 5 8