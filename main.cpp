#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <optional>
#include <queue>
#include <variant>

struct Sudoku
{
    std::uint8_t& operator()(int y, int x)
    {
        return board[x + 9 * y];
    }

    std::uint8_t operator()(int y, int x) const
    {
        return board[x + 9 * y];
    }

    std::array<std::uint8_t, 9*9> board;
};


std::ostream& operator <<(std::ostream& o, const Sudoku& sudoku)
{
    for(int y = 0; y < 9; ++y)
    {
        for(int x = 0; x < 9; ++x)
        {
            o << (int) sudoku(y,x);
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

struct EmptyField
{
    int x, y;
    std::array<std::uint8_t, 9> poss = {1, 1, 1, 1, 1, 1, 1, 1, 1};
};

struct Entry
{
    int x, y;
    std::uint8_t value;
};

using Node = std::variant<Entry, EmptyField>;

auto eliminate(const Sudoku& sudoku, EmptyField& emptyField)
{
    auto& [x, y, poss] = emptyField;

    for(int y1 = 0; y1 < 9; ++y1)
        poss[sudoku(y1, x)] = 0;

    for(int x1 = 0; x1 < 9; ++x1)
        poss[sudoku(y, x1)] = 0;;

    int xbegin = x / 3, ybegin = y / 3;

    for(int y1 = ybegin; y1 < ybegin + 3; ++y1)
    for(int x1 = xbegin; x1 < ybegin + 3; ++x1)
        poss[sudoku(y1, x)] = 0;

    return std::count(poss.begin(), poss.end(), 1);

}

void writeValue(const Entry& entry, Sudoku& sudoku)
{
    sudoku(entry.y, entry.x) = entry.value;

    for(int y1 = 0; y1 < 9; ++y1)
        poss[sudoku(y1, x)] = 0;

    for(int x1 = 0; x1 < 9; ++x1)
        poss[sudoku(y, x1)] = 0;;

    int xbegin = x / 3, ybegin = y / 3;

    for(int y1 = ybegin; y1 < ybegin + 3; ++y1)
        for(int x1 = xbegin; x1 < ybegin + 3; ++x1)
            poss[sudoku(y1, x)] = 0;


}

inline std::uint8_t getFirstPoss(const std::array<std::uint8_t, 9>& poss)
{
    return std::distance(poss.begin(), std::find(poss.begin(), poss.end(), 1));
}



std::optional<Sudoku> solve(const Sudoku& sudoku)
{
    auto solution = sudoku;

    std::vector<EmptyField> emptyFields;

    for(int y = 0; y < 9; ++y)
    for(int x = 0; x < 9; ++x)
        if(!sudoku(y,x))
        {
            EmptyField emptyField{y,x};
            int numPoss = eliminate(sudoku, emptyField);

            if(numPoss == 0)
                return std::nullopt;

            else if(numPoss == 1)
            {
                auto& poss = emptyField.poss;
                solution(y,x) = getFirstPoss(poss);
                continue;
            }

            emptyFields.push_back(emptyField);
        }

    std::queue<Node> nodes;

    nodes.emplace(emptyFields.front());

    while(!nodes.empty())
    {
        auto [y, x, value] = nodes.front();
        solution(y, x) = value;


    }




}

int main()
{
    Sudoku sudoku
            {{
              0, 0, 0,    6, 8, 4,    7, 0, 0,
              0, 0, 0,    0, 1, 0,    0, 9, 5,
              2, 0, 7,    0, 9, 0,    0, 0, 0,

              6, 9, 5,    0, 0, 1,    8, 0, 0,
              0, 0, 0,    3, 4, 0,    0, 0, 0,
              8, 0, 0,    0, 0, 0,    1, 0, 0,

              0, 0, 0,    4, 6, 9,    0, 0, 0,
              0, 3, 0,    0, 7, 0,    0, 0, 0,
              0, 5, 0,    0, 0, 0,    0, 8, 7
            }};

    std::cout << sudoku;

}