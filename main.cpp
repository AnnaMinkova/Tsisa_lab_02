#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
double myF(double x)
{
    return pow((1-x),2)+exp(x);
}
double F(const double x)
{
    return myF(x) * sin(5*x);
}
const double A=-2;
const double B=4;
const vector<double> P_VALUES = {0.9, 0.91, 0.92, 0.93, 0.94,
                                      0.95, 0.96, 0.97, 0.98, 0.99};
const vector<double> Q_VALUES = {0.005, 0.01, 0.015, 0.02, 0.025,
                                      0.03, 0.035, 0.04, 0.045, 0.05,
                                      0.055, 0.06, 0.065, 0.07, 0.075,
                                      0.08, 0.085, 0.09, 0.095, 0.1};
void printLine()
{
    cout << '+' << std::string(7, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << std::string(10, '-')
         << '+' << std::string(10, '-') << '+' << '\n';
}

void TableHead(const vector<double>& p)
{
printLine();

    cout << '|' << setw(5) << "q/P" << setw(3) << '|';
    for(auto item : p) cout <<setw(9) << item << " |";
    cout << '\n';

printLine();
}

void Table(const vector<double>& p, const vector<double>& q,const vector<vector<double>>& table)
{
TableHead(p);

    for (size_t i = 0; i < q.size(); ++i)
    {
        cout << '|' << setw(6) << q[i] << " |";
        for(size_t j = 0; j < p.size(); ++j)
        {
            cout << setw(9) << table[i][j] << " |";
        }
        cout << '\n';
    }
printLine();
}

vector<vector<double>> pointsNumber(const vector<double>& p,const vector<double>& q)
{
    vector<vector<double>> points(q.size());
    for(size_t i = 0; i < q.size(); ++i)
    {
        points[i].resize(p.size());
        for(size_t j = 0; j < p.size(); ++j)
        {
            points[i][j] = ceil(log(1 - p[j]) / log(1 - q[i]));
        }
    }
    return points;
}
double random(const double a, const double b)
{
    return a + rand() * 1./RAND_MAX * (b - a);
}
template<class F>
vector<vector<double>> rndSearch(const vector<vector<double>>& numbers,const double a, const double b, F function)
{
    vector<vector<double>> table;
    table.resize(numbers.size());
    for(size_t i = 0; i < table.size(); ++i)
    {
        table[i].resize(numbers[i].size());
        for(size_t j = 0; j < table[i].size(); ++j)
        {
            table[i][j] = function(a);
            for(size_t k = 0; k < numbers[i][j]; ++k)
            {
                double newValue = function(random(a, b));
                if(newValue < table[i][j])
                {
                    table[i][j] = newValue;
                }
            }
        }
    }

    return table;
}

int main()
{
    cout << "Variant 10: "<<endl;
    cout << "Table with number of points for each p and q:\n";
    auto points = pointsNumber(P_VALUES, Q_VALUES);
    Table(P_VALUES, Q_VALUES, points);

    srand(time(nullptr));
    auto valuesForF = rndSearch(points, A, B, myF);
    cout << "Table for function 1:\n";
    Table(P_VALUES, Q_VALUES, valuesForF);
    auto valuesForF_ = rndSearch(points, A, B, F);
    cout << "Table for function 2:\n";
    Table(P_VALUES, Q_VALUES, valuesForF_);

    return 0;
}