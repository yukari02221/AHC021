#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define reps(i, n) for (int i = 1; i <= (n); i++)

// 回文判定
bool isPali(string s)
{
    int len = s.size();
    for (int i = 0; i < len / 2; i++)
    {
        if (s[i] != s[len - i - 1])
            return false;
    }
    return true;
}

int main()
{
    int N;
    cin >> N;
    vector<string> A(N);
    rep(i, N) cin >> A[i];
    bool flag = false;

    // 二重ループで合体文字を作る
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;                           // i と j が同じときはスキップ
            string kaibun1 = A[i] + A[j];           // Si + Sj の順
            string kaibun2 = A[j] + A[i];           // Sj + Si の順
            if (isPali(kaibun1) || isPali(kaibun2)) // どちらかが回文ならフラグを立てる
            {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
    if (flag)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
