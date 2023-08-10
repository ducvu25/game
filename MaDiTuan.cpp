#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // Cstdlib Ä‘á»ƒ dÃ¹ng cho hÃ m exit(0)
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <time.h>
using namespace std;
#define COLORTABLE1 11
#define COLORPLAYER1 4
#define COLORPLAYER2 9
#define COLORPLAYER3 10
void TextColor(int color); // đổi màu kí tự
void gotoXY(int x, int y); // di chuyển tới vị trí x, y
void LineX(int x1, int x2, int y, int c = 196);
void LineY(int y1, int y2, int x, int c = 179);
void VeBan(int m, int n, int x, int y, int color);
void VeBan(int **a, int m, int n, int x, int y, int color);
int **TaoBan(int m, int n);
void Start(int m, int n);
void Line(int **a, bool **check, int m, int n, int x, int y, int i1, int j1);
int main()
{
    char c;
    gotoXY(50, 10);
    // TextColor(11);
    // cout << "Ma sinh vien";
    // Sleep(2000);
    srand(time(0));
    system("cls");
    while (true)
    {
        system("cls");
        int m = 5, n = 5;
        cout << "Nhap kich thuoc (m x n): ";
        cin >> m >> n;
        Start(m, n);
        system("cls");
        cout << "\nBan muon tiep tuc khong (y/n): ";
        cin >> c;
        if (c == 'N' || c == 'n')
            break;
    }
    return 0;
}
void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoXY(int x, int y)
{ // x la ngang, y la doc
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void LineX(int x1, int x2, int y, int c) // c - +
{
    for (int i = x1; i <= x2; i++)
    {
        gotoXY(i, y);
        if ((i - x1) % 4 != 0) // +---+
            cout << char(196);
        else
            cout << char(c);
    }
}
void LineY(int y1, int y2, int x, int c)
{
    for (int i = y1; i <= y2; i++)
    {
        gotoXY(x, i);
        if ((i - y1) % 2 == 1)
            cout << char(179);
        else
            cout << char(c);
    }
}
void VeBan(int m, int n, int x, int y, int color) // m x n
{
    TextColor(color);
    LineY(y, y + 2 * m, x, 195);
    LineY(y, y + 2 * m, x + 4 * n, 180);
    for (int i = 1; i < m; i++)
    {
        LineX(x + 1, x + 4 * n - 1, y + 2 * i);
    }
    for (int i = 1; i < n; i++)
    {
        LineY(y, y + 2 * m, x + 4 * i, 197);
    }
    LineX(x, x + 4 * n, y, 194);
    LineX(x, x + 4 * n, y + 2 * m, 193);
}
void VeBan(int **a, int m, int n, int x, int y, int color)
{
    VeBan(m, n, x, y, color);
    TextColor(7);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            gotoXY(j * 4 + x + 1, i * 2 + y + 1);
            cout << a[i][j];
        }
}
int **TaoBan(int m, int n)
{
    int **a = new int *[m];
    for (int i = 0; i < m; i++)
        a[i] = new int[n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 1000;
        }
    return a;
}
void Start(int m, int n)
{
    int x = 10, y = 2;
    int **a = TaoBan(m, n);

    LineX(x, x + n * 4 - 10, y);
    LineX(x, x + n * 4 - 10, y + 2);
    TextColor(COLORTABLE1);
    gotoXY(x + n * 2 - 15, y + 1);
    cout << "Kich thuoc ban: " << m << " x " << n;
    VeBan(a, m, n, x - 5, y + 5, COLORTABLE1);
    LineX(x + n * 4 + 20, x + n * 4 + 60, y);
    LineX(x + n * 4 + 20, x + n * 4 + 60, y + 2);
    int x1 = 0, y1 = 0;
    do
    {
        TextColor(COLORTABLE1);
        gotoXY(x + n * 4 + 25, y + 1);
        cout << "Vi tri bat dau:                  ";
        TextColor(7);
        gotoXY(x + n * 4 + 25 + 15, y + 1);
        cin >> x1 >> y1;
    } while (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n);

    LineX(x + n * 4 + 20, x + n * 4 + 60, y + 4);
    LineX(x + n * 4 + 20, x + n * 4 + 60, y + 6);
    TextColor(COLORTABLE1);
    gotoXY(x + n * 4 + 25, y + 5);
    cout << "Dem nguoc: ";
    TextColor(5);
    for (int i = 0; i < 4; i++)
    {
        gotoXY(x + n * 4 + 35, y + 5);
        cout << 3 - i << "s";
        Sleep(1000);
    }
    gotoXY(x + n * 4 + 35, y + 7);
    TextColor(COLORPLAYER1);
    cout << "Mau do: o da di qua";
    gotoXY(x + n * 4 + 35, y + 8);
    TextColor(COLORPLAYER3);
    cout << "Mau xanh la: o xuat phat";
    gotoXY(x + n * 4 + 35, y + 9);
    TextColor(COLORPLAYER2);
    cout << "Mau xanh lam: o dich";
    bool **check = new bool *[m];
    for (int i = 0; i < m; i++)
        check[i] = new bool[n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            check[i][j] = false;
    Line(a, check, m, n, x - 4, y + 6, x1, y1);
}
void Line(int **a, bool **check, int m, int n, int x, int y, int i1, int j1)
{
    check[i1][j1] = true;
    gotoXY(x + j1 * 4, y + i1 * 2);
    TextColor(COLORPLAYER1);
    cout << a[i1][j1];
    // getch();
    Sleep(1000);
    int I[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int J[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int i = 0; i < 8; i++)
    {
        if (i1 + I[i] >= 0 && i1 + I[i] < m && j1 + J[i] >= 0 && j1 + J[i] < n && !check[i1 + I[i]][j1 + J[i]])
        {
            gotoXY(x + j1 * 4, y + i1 * 2);
            TextColor(COLORPLAYER3);
            cout << a[i1][j1];
            gotoXY(x + (j1 + J[i]) * 4, y + (i1 + I[i]) * 2);
            TextColor(COLORPLAYER2);
            cout << a[i1 + I[i]][j1 + J[i]];
            // getch();
            // getch();
            Sleep(1000);
            gotoXY(x + j1 * 4, y + i1 * 2);
            TextColor(COLORPLAYER1);
            cout << a[i1][j1];
            Line(a, check, m, n, x, y, i1 + I[i], j1 + J[i]);
        }
    }
}