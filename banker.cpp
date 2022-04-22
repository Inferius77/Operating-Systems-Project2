// lab 2 for operatiing systems
// implement the bankers algorithm
// 4/21/22
// michael Angie

#include <iostream>
#include <fstream>

int main()
{
    bool flag;
    const int processes = 5;
    const int resources = 3;
    int solution[5];
    int need[5][3];
    int allocation[5][3];
    int max[5][3];
    int available[3];
    int index = 0;
    std::ifstream in;
    
////////////////////////////////////////////////////
// fill the arrays from the input file

    in.open("input.txt");

    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            in >> allocation[i][j];
        }
    }

    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            in >> max[i][j];
        }
    }

    for (int i = 0; i < resources; ++i)
        {
            in >> available[i];
        }
// done
///////////////////////////////////////////////////

    int temp[5] = { 0, 0, 0, 0, 0 };

    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < processes; ++j)
        {
            if (temp[j] == 0)
            {
                flag = false;

                for (int x = 0; x < resources; ++x)
                {
                    if (need[j][x] > available[x])
                    {
                        flag = true;
                        break;
                    }
                }

                if (!flag)
                {
                    solution[index++] = j;

                    for (int x = 0; x < 3; ++x)
                    {
                        available[x] += allocation[j][x];
                    }

                    temp[j] = 1;
                }
            }
        }
    }

    // check for starvation
    for (int i = 0; i < processes; ++i)
    {
        if (temp[i] == 0)
        {
            std::cout << "The sequence is not safe." << std::endl;
            return 0;
        }
    }

    
    std::cout << "The following sequence is safe: " << std::endl;

    for (int i = 0; i < processes - 1; ++i)
    {
        std::cout << "P" << solution[i] << " -> ";
    }

    std::cout << "P" << solution[processes - 1] << std::endl;

    return 0;
}


