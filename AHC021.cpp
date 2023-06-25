#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define reps(i, n) for (int i = 1; i <= (n); i++)

// ピラミッドの段数を固定
const int N = 30;

struct Node
{
    int x;
    int y;
    int value;
    vector<pair<int, int>> neighbors;

    Node(int _x, int _y, int _value) : x(_x), y(_y), value(_value) {}
};

class Pyramid
{
public:
    int N;
    vector<vector<Node>> nodes;
    vector<pair<pair<int, int>, pair<int, int>>> swaps;

    Pyramid(int _N, const vector<vector<int>> &values) : N(_N)
    {
        nodes.resize(N);
        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y <= x; y++)
            {
                nodes[x].push_back(Node(x, y, values[x][y]));
            }
        }
        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y <= x; y++)
            {
                if (x > 0)
                {
                    nodes[x][y].neighbors.push_back({x - 1, y});
                    if (y > 0)
                    {
                        nodes[x][y].neighbors.push_back({x - 1, y - 1});
                    }
                }
                if (y > 0)
                {
                    nodes[x][y].neighbors.push_back({x, y - 1});
                }
                if (x < N - 1)
                {
                    nodes[x][y].neighbors.push_back({x + 1, y});
                    if (y < x)
                    {
                        nodes[x][y].neighbors.push_back({x + 1, y + 1});
                    }
                }
            }
        }
    }
    void swapBalls(int x1, int y1, int x2, int y2)
    {
        swap(nodes[x1][y1].value, nodes[x2][y2].value);
        swaps.push_back({{x1, y1}, {x2, y2}});
    }
};

void performSwaps(Pyramid &pyramid)
{
    int K = 0;  // 操作回数
    bool swapped = true;

    while (swapped)
    {
        swapped = false;

        // 各段のボールに対して操作を行う
        for (int x = 0; x < pyramid.N - 1; x++)
        {
            for (int y = 0; y <= x; y++)
            {
                Node &node = pyramid.nodes[x][y];
                Node &belowNode1 = pyramid.nodes[x + 1][y];
                Node &belowNode2 = pyramid.nodes[x + 1][y + 1];

                // ボールの値を比較し、条件に合わない場合は交換操作を行う
                if (node.value > belowNode1.value)
                {
                    pyramid.swapBalls(node.x, node.y, belowNode1.x, belowNode1.y);
                    swapped = true;
                    K++;
                }

                if (node.value > belowNode2.value)
                {
                    pyramid.swapBalls(node.x, node.y, belowNode2.x, belowNode2.y);
                    swapped = true;
                    K++;
                }
            }
        }
    }
}



int main()
{
    vector<vector<int>> values(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            int b;
            cin >> b;
            values[i].push_back(b);
        }
    }
    Pyramid pyramid(N, values);

    performSwaps(pyramid);

    cout << pyramid.swaps.size() << endl;
    for (const auto &s : pyramid.swaps)
    {
        cout << s.first.first << " " << s.first.second << " " << s.second.first << " " << s.second.second << endl;
    }

    return 0;
}
