#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<double> find_circle(vector<pair<double, double> > dots)
{
    double A = dots[1].first - dots[0].first;
    double B = dots[1].second - dots[0].second;
    double C = dots[2].first - dots[0].first;
    double D = dots[2].second - dots[0].second;
    double E = A * (dots[0].first + dots[1].first) + B * (dots[0].second + dots[1].second);
    double F = C * (dots[0].first + dots[2].first) + D * (dots[0].second + dots[2].second);
    double G = 2 * (A * (dots[2].second - dots[1].second) - B * (dots[2].first - dots[1].first));

    if (G == 0)
    {
        return { 0, 0, -1 };
    }

    double Cx = (D * E - B * F) / G;
    double Cy = (A * F - C * E) / G;
    double R = sqrt(pow(dots[0].first - Cx, 2) + pow(dots[0].second - Cy, 2));
    return { Cx, Cy, R };
}

bool circle_check(vector<pair<double, double> > dots)
{
    for (int i = 0; i < dots.size() - 2; i++)
    {
        for (int j = i + 1; j < dots.size() - 1; j++)
        {
            for (int l = j + 1; l < dots.size(); l++)
            {
                double A = dots[1].first - dots[0].first;
                double B = dots[1].second - dots[0].second;
                double G = 2 * (A * (dots[2].second - dots[1].second) - B * (dots[2].first - dots[1].first));
                if (G != 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "\nУсловие задачи:\nДаны два множества точек на плоскости. Найти центр и радиус окружности, проходящей через k (k>=3) точек первого множества и содержащей строго внутри себя n точек второго множества\n\n";

    int k, n;
    vector<pair<double, double> > dots1;
    vector<pair<double, double> > dots2;

    cout << "k = ";
    for (cin >> k; k < 3; cin >> k)
    {
        cout << "k < 3, введите k ещё раз\n\n";
        cout << "k = ";
    }
    cout << "n = ";
    cin >> n;
    cout << "\n";

    bool check = false;
    cout << "Введите точки, лежащие на окружности:\n";
    while (!check)
    {
        for (int i = 0; i < k; i++)
        {
            double x, y;
            cin >> x >> y;
            dots1.push_back(make_pair(x, y));
        }

        if (circle_check(dots1))
        {
            check = true;
        }
        else
        {
            cout << "В введённых вами точках, нет ни одной тройки точек, лежащих на одной окружности\n\nВведите точки ещё раз:\n";
            dots1.clear();
        }
    }
    cout << endl;

    if (n != 0)
    {
        cout << "Введите точки втрого множества:\n";
        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            dots2.push_back(make_pair(x, y));
        }
        cout << "\n";
    }

    int mx = 0;
    vector<double> mxsolution = { 0, 0, -1 };
    for (int i = 0; i < k - 2; i++)
    {
        for (int j = i + 1; j < k - 1; j++)
        {
            for (int l = j + 1; l < k; l++)
            {
                int c = 0;
                vector<double> solution = find_circle({ dots1[i], dots1[j], dots1[l] });
                if (solution[2] != -1)
                {
                    for (int m = 0; m < n; m++)
                    {
                        double dist = sqrt(pow(dots2[m].first - solution[0], 2) + pow(dots2[m].second - solution[1], 2));
                        if (dist < solution[2])
                        {
                            c++;
                        }
                    }
                    if (c >= mx)
                    {
                        mx = c;
                        mxsolution = solution;
                    }
                }
            }
        }
    }

    if (mx < n)
    {
        cout << "Окружность с максимальным количеством точек в себе содержит только " << mx << " точку/ек, а должна содержать " << n << " точку/ек" << endl;
    }
    cout << "Центр окружности = (" << mxsolution[0] << ", " << mxsolution[1] << ")" << endl;
    cout << "Радиус окружности = " << mxsolution[2] << endl;

    return 0;
}

