// in a chessboard place 8 queens such that they dont attack each other and cover the entire board. find all such combinations (there are 92)

#include <bits/stdc++.h>
using namespace std;

filesystem::path tempFilePath;

void cleanup()
{
    if (filesystem::exists(tempFilePath)) filesystem::remove(tempFilePath);
}

typedef unsigned long long Board;

bool unaffected(Board board, int x)
{
    Board mask = 1;
    for (int i = 0; i < 64; i++)
    {
        if (board & mask)
        {
            if ((i % 8 == x % 8) || (i / 8 == x / 8) || abs((i % 8) - (x % 8)) == abs((i / 8) - (x / 8)))
                return false;
        }
        mask = mask << 1;
    }
    return true;
}

vector<Board> possibleSq(int rank, Board board)
{
    vector<Board> sq;
    for (int i = 0; i < 8; i++)
    {
        int j = rank * 8 + i;
        if (unaffected(board, j))
            sq.push_back(board ^ (1ULL << j));
    }
    return sq;
}

set<Board> answer()
{
    Board board = 0;
    set<Board> soln;

    for (Board r1 : possibleSq(0, board))
    {
        for (Board r2 : possibleSq(1, r1))
        {
            for (Board r3 : possibleSq(2, r2))
            {
                for (Board r4 : possibleSq(3, r3))
                {
                    for (Board r5 : possibleSq(4, r4))
                    {
                        for (Board r6 : possibleSq(5, r5))
                        {
                            for (Board r7 : possibleSq(6, r6))
                            {
                                for (Board r8 : possibleSq(7, r7))
                                {
                                    soln.insert(r8);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return soln;
}

string fen(Board b)
{
    string f = "";
    while (b)
    {
        int a = b % 256;
        b /= 256;
        int i = log2(a);
        if (i > 0)
            f += to_string(i);
        f += "Q";
        if (7 - i > 0)
            f += to_string(7 - i);
        if (b)
            f += "/";
    }

    return f;
}

string lichessLink(string f)
{
    return "https://lichess1.org/export/fen.gif?fen=" + f;
}

string imageTag(string src)
{
    return "<img src='" + src + "' alt='fuck off' width='300' height='300' style='margin: 10px'>";
}

string htmlCode()
{
    string code = "";

    for (Board b : answer())
    {
        code += imageTag(lichessLink(fen(b)));
    }
    return code;
}

int main()
{
    tempFilePath = filesystem::temp_directory_path() / "fu.html";

    atexit(cleanup);

    string html = htmlCode();

    ofstream ofs(tempFilePath);
    if (ofs << html)
    {
        ofs.close();

        string pathStr = tempFilePath.string();
        
        #ifdef _WIN32
        std::string command = "start \"\" \"" + pathStr + "\"";
        #elif __APPLE__
        std::string command = "open \"" + pathStr + "\"";
        #else
        std::string command = "xdg-open \"" + pathStr + "\"";
        #endif
        
        system(command.c_str());
    }

    cout << "watch this shit. press enter to exit" << endl;
    cin.get();
        
    return 0;
}