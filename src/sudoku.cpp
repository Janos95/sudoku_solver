//
// Created by janos on 04.08.19.
//

#include "sudoku.h"

std::ostream& operator <<(std::ostream& o, const Sudoku& sudoku)
{
    for(int y = 0; y < 9; ++y)
    {
        for(int x = 0; x < 9; ++x)
        {
            o << (int) sudoku(y,x).value;
            if((x+1)%3)
                o << " | ";
            else if(x != 8)
                o << " || ";

        }

        if((y+1)%3)
            o << "\n--|---|---||---|---|---||---|---|--\n";
        else if(y != 8)
            o << "\n==|===|========|===|========|===|==\n";
    }

    return o;

}