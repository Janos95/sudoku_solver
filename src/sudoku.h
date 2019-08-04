//
// Created by janos on 04.08.19.
//


#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <optional>
#include <stack>
#include <cassert>

#pragma once



using Int = std::uint8_t;


struct Entry
{
    int y, x;
};


struct GridPoint
{
    constexpr GridPoint(int value): value(value)
    {
        if(value)
        {
            std::fill(candidates.begin(), candidates.end(), Int(0));
            candidates[value - 1] = Int(1);
        }
    }

    GridPoint(const GridPoint&) noexcept = default;


    Int value;
    std::array<Int, 9> candidates = {1, 1, 1, 1, 1, 1, 1, 1, 1};


};

struct Sudoku
{

    constexpr auto& operator()(int y, int x)
    {
        return board[x + 9 * y];
    }

    constexpr auto operator()(int y, int x) const
    {
        return board[x + 9 * y];
    }

    std::array<GridPoint, 9*9> board;

    std::vector<Entry> emptyGridPoints;
};


//returns true if first argument is greater than the second.
//using this with heap utilities from stl will produce a min heap.

struct numberOfEmptyGridPoints
{
    const Sudoku& suduko;

    bool operator() (const Entry& e1, const Entry& e2)
    {
        const auto& c1 = suduko(e1.y,e1.x).candidates;
        const auto& c2 = suduko(e2.y,e2.x).candidates;
        return std::count(c1.begin(), c1.end(), 1) > std::count(c2.begin(), c2.end(), 1);
    }
};


std::ostream& operator <<(std::ostream&, const Sudoku&);