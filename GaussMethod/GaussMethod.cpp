#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

vector<double> solve_system(vector<vector<double> > matrix)
{
    vector<vector<double> > copy = matrix;

    for (int i = 0; i < copy.size() - 1; i++)
    {
        for (int j = i + 1; j < copy.size(); j++)
        {
            double sum = 0, koef = 0;
            if (copy[i][i] == 0)
            {
                for (int m = i + 1; i < copy.size() + 1; i++)
                {
                    sum += copy[m][i];
                    if (copy[m][i] != 0)
                    {
                        vector<double> tmp = copy[m];
                        copy[m] = copy[i];
                        copy[i] = tmp;
                        break;
                    }
                }
                if (sum == 0)
                {
                    koef = 0;
                }
            }
            else
            {
                koef = copy[j][i] / copy[i][i];
            }
            for (int k = i; k < copy.size() + 1; k++)
            {
                copy[j][k] -= copy[i][k] * koef;
            }
        }
    }

    vector<double> solution(copy.size());
    for (int i = copy.size() - 1; i >= 0; i--)
    {
        if (copy[copy.size() - 1][copy.size() - 1] == 0 && copy[copy.size() - 1][copy.size()] == 0)
        {
            return vector<double>(copy.size(), -1);
        }
        double result = 0;
        for (int j = 0; j < copy.size(); j++)
        {
            result += copy[i][j] * solution[j];
        }
        solution[i] = (copy[i][copy.size()] - result) / copy[i][i];
    }
    return solution;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    ifstream f1_output("f1.txt");
    f1_output >> n;
    vector<vector<double>> matrix(n, vector<double>(n + 1));
    int i = 0, j = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            f1_output >> matrix[i][j];
        }
    }
    f1_output.close();
    cout << "Матрица: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    vector<double> solution = solve_system(matrix);
    if (solution == vector<double>(n, -1))
    {
        cout << "Есть множество решений" << endl;
    }
    else
    {
        cout << "Решение: " << endl;
        for (double m : solution)
        {
            cout << m << " ";
        }
    }
    return 0;
}
