vector <double> solve_system(vector<vector<double> > matrix)
{
    vector<vector<double> > copy = matrix;
    vector<vector<double> > center;

    for (int i = 0; i < copy.size() - 1; i++)
    {
        for (int j = i + 1; j < copy.size(); j++)
        {
            double koef = copy[j][i] / copy[i][i];
            for (int k = i; k < 6; k++)
            {
                copy[j][k] -= copy[i][k] * koef;
            }
        }
    }


    for (int i = 1; i < copy.size(); i++)
    {
        center.push_back({ copy[i][1], copy[i][3], copy[i][5] });
    }

    vector<double> solution{ 0, 0, 0 };
    for (int i = int(center.size()) - 1; i >= 0; i--)
    {
        if (center[i][1] != 0)
        {
            solution[1] = center[i][2] / center[i][1];
            break;
        }
    }
    for (int i = int(center.size()) - 1; i >= 0; i--)
    {
        if (center[i][0] != 0)
        {
            solution[0] = (center[i][2] - solution[1] * center[i][1]) / center[i][0];
            break;
        }
    }
    solution[2] = sqrt(pow(solution[0], 2) + solution[0] * copy[0][1] + pow(solution[1], 2) + solution[1] * copy[0][3] - copy[0][5]);
    return solution;
}