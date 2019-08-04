#include "sudoku.h"


#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <optional>
#include <stack>
#include <cassert>
#include <chrono>



//only works if there is some value in (y,x)
auto eliminate(Sudoku& sudoku, const int y, const int x)
{
    const Int v = sudoku(y,x).value;
    assert(v);

    for(int y1 = 0; y1 < 9; ++y1)
        sudoku(y1, x).candidates[v-1] = 0;

    for(int x1 = 0; x1 < 9; ++x1)
        sudoku(y, x1).candidates[v-1] = 0;

    int xbegin = x - x % 3, ybegin = y - y % 3;

    for(int y1 = ybegin; y1 < ybegin + 3; ++y1)
    for(int x1 = xbegin; x1 < xbegin + 3; ++x1)
        sudoku(y1, x1).candidates[v-1] = 0;

}



Sudoku solve(const Sudoku& sudoku)
{
    auto solution = sudoku;

    for(int y = 0; y < 9; ++y)
    {
        for(int x = 0; x < 9; ++x)
        {
            if(!solution(y,x).value)
                solution.emptyGridPoints.push_back({y,x});
            else
                eliminate(solution, y, x);
        }
    }

    std::sort(solution.emptyGridPoints.begin(), solution.emptyGridPoints.end(), numberOfEmptyGridPoints{solution});

    std::vector<Sudoku> backtracking = {solution};
    auto emptyGridPoints = &backtracking.back().emptyGridPoints;

    int count = 0;

    while(!emptyGridPoints->empty())
    {
        ++count;
        auto& currentBoard = backtracking.back();

        //get empty grid point with fewest possibilties
        auto& egp = currentBoard.emptyGridPoints;
        const auto [y, x] = egp.back();

        const auto& c = currentBoard(y, x).candidates;
        const auto it = std::find(c.begin(), c.end(), 1);

        const auto numPoss = std::count(c.begin(), c.end(), 1);



        if(numPoss == 0)
        {
            //no solution, so backtrack
            backtracking.pop_back();

            auto& oldBoard = backtracking.back();
            auto& oldEgp = oldBoard.emptyGridPoints;
            auto& [oldY, oldX] = oldEgp.back();

            auto& cOld = oldBoard(oldY, oldX).candidates;
            auto itOld = std::find(cOld.begin(), cOld.end(), 1);

            *itOld = 0;

            emptyGridPoints = &oldBoard.emptyGridPoints;
        }
        else if(numPoss == 1)
        {
            //write value and eliminate
            currentBoard(y, x) = std::distance(c.begin(), it) + 1;
            eliminate(currentBoard, y, x);

            std::sort(egp.begin(), egp.end(), numberOfEmptyGridPoints{currentBoard});
            egp.pop_back();
        }
        else
        {
            backtracking.push_back(currentBoard);
            auto& newBoard = backtracking.back();
            auto& newEgp = newBoard.emptyGridPoints;

            newBoard(y, x) = std::distance(c.begin(), it) + 1;
            eliminate(newBoard, y, x);

            std::sort(newEgp.begin(), newEgp.end(), numberOfEmptyGridPoints{newBoard});
            newEgp.pop_back();

            emptyGridPoints = &newBoard.emptyGridPoints;
        }

    }

    return backtracking.back();

}

