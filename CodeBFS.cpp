#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <memory>

using namespace std;

#define MAX 100
#define TRUE 1
#define FALSE 0
#define MAXN 10000000
fstream fin, fout;
int n; // s? d?nh c?a d? th?.
int s; //d?nh d?u.
int t; //d?nh cu?i
char input;
vector<int> d(MAX, 0);     // m?ng dánh d?u kho?ng cách.
vector<int> before(MAX, 0); // m?ng dánh d?u du?ng di.
// int Matrix[MAX][MAX];//ma tr?n tr?ng s?
vector<vector<int>> Matrix(MAX, vector<int>(MAX, 0));
vector<int> visited(MAX, 0); // m?ng dánh d?u d?nh dã du?c gán nhãn.

struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;
    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;
void *operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    fout << "\nMemory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

void Nhap()
{
    fin.open("test.txt", ios::in);
    fin >> n >> s >> t;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Matrix[i][j] = MAXN;
    while (!fin.eof())
    {
        int u, v, w;
        fin >> u >> v >> w;
        Matrix[u][v] = w;
        Matrix[v][u] = w;
    }
    fin.close();
}

void KetquaBFS()
{
    fout.open("out.txt", ios::out | ios::trunc);
    fout << "K?t qu? BFS: " << endl;
    fout << t << " <= ";
    int i = before[t];
    while (i != s)
    {
        fout << i << " <= "; // in ra k?t qu? du?i d?ng char.
        i = before[i];
    }
    fout << s << endl;
    fout << "T?ng quãng du?ng nh? nh?t là: " << d[t] << endl;
}

void BFS()
{
    int u, minp;
    // kh?i t?o nhãn t?m th?i cho các d?nh.
    for (int v = 0; v < n; v++)
    {
        d[v] = Matrix[s][v];
        before[v] = s;
        visited[v] = FALSE;
    }
    before[s] = 0;
    d[s] = 0;
    visited[s] = TRUE;
    while (!visited[t])
    {
        minp = MAXN;
        // tìm d?nh u sao cho d[u] là nh? nh?t
        for (int v = 0; v < n; v++)
        {
            if ((!visited[v]) && (minp > d[v]))
            {
                u = v;
                minp = d[v];
            }
        }
        visited[u] = TRUE; // u la dinh co nhan tam thoi nho nhat
        if (!visited[t])
        {
            // gán nhãn l?i cho các d?nh.
            for (int v = 0; v < n; v++)
            {
                if ((!visited[v]) && (d[u] + Matrix[u][v] < d[v]))
                {
                    d[v] = d[u] + Matrix[u][v];
                    before[v] = u;
                }
            }
        }
    }
}



int main()
{
    clock_t start = clock();
    Nhap();
    BFS();
    KetquaBFS();
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    fout << "Execution time: " << time_taken * 1000 << " miliseconds";
    PrintMemoryUsage();
    fout.close();
    return 0;
}
