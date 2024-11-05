#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

void printVec(vector<double>& mat)
{
	for (int q = 0; q < mat.size() && q < 5; q++)
	{
		cout << mat[q] << " ";
	}
	for (int q = mat.size() - 5 > 5 ? mat.size() - 5 : 5; q < mat.size(); q++)
	{
		cout << mat[q] << " ";
	}
	cout << "\n";
}

void passingMethod(vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& f, vector<double>& y, vector<double>& alf, vector<double>& bet)
{
	alf[0] = b[0] / c[0];
	bet[0] = f[0] / c[0];
	int n = c.size(); // Длина нашего вектора диагонали
	double delt = 0;
	//cout << alf[0] << " " << bet[0] << "\n";
	for (int i = 1; i < n - 1; i++)
	{
		delt = c[i] - a[i - 1] * alf[i - 1];
		alf[i] = b[i] / delt;
		bet[i] = (f[i] + a[i - 1] * bet[i - 1]) / delt;
		//cout << delt << " " << alf[i] << " " << bet[i] << "\n";
	}
	n--; // Уменьшаем на 1 чтобы n стало индексом последнего эл-та
	delt = c[n] - a[n - 1] * alf[n - 1];
	bet[n] = (f[n] + a[n - 1] * bet[n - 1]) / delt;
	//cout << delt  << " " << bet[n] << "\n";

	y[n] = bet[n];
	for (int i = n - 1; i >= 0; i--)
	{
		y[i] = alf[i] * y[i + 1] + bet[i];
	}
}

int main()
{
	srand(time(0));	
	unsigned const int n = 1000;
	unsigned const int m = 12;

	vector<double> a(n - 1, 0);
	vector<double> b(n - 1, 0);
	vector<double> c(n, 0);
	vector<double> y(n, 0);
	vector<double> yImprecise(n, 0);
	vector<double> f(n, 0);
	
	vector<double> alf(n - 1, 0);
	vector<double> bet(n, 0);

	for (int i = 0; i < n - 1; i++)
	{
		a[i] = rand() % 201 - 100.0;
		b[i] = rand() % 201 - 100.0;
		y[i] = i + 1;
	}
	y[n - 1] = n;

	c[0] = rand() % (m + 1) + m * 1.0 + b[0];
	c[n - 1] = rand() % (m + 1) + m * 1.0 + a[n - 2];
	for (int i = 1; i <= n - 2; i++)
	{
		c[i] = rand() % (m + 1) + m * 1.0 + b[i] + a[i - 1];
	}

	/*a = { -2, -1, -1 };
	c = { 2, 3, -1, -1 };
	b = { -1, 1, -3 };
	y = { 1, 2, -1, 3};*/


	f[0] = c[0] * y[0] + (-b[0]) * y[1];
	f[n - 1] = (-a[n - 2]) * y[n - 2] + c[n - 1] * y[n - 1];
	for (int i = 1; i <= n - 2; i++)
	{
		f[i] = (-a[i - 1] * y[i - 1]) + c[i] * y[i] + (-b[i]) * y[i + 1];
	}

	auto start = chrono::high_resolution_clock::now();

	passingMethod(a, b, c, f, yImprecise, alf, bet);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	cout << "Solition:\n";
	printVec(y);
	cout << std::fixed << std::setprecision(22);
	cout << "Imprecise solution:\n";
	printVec(yImprecise);

	cout << "Time: " << duration.count() << " seconds\n";

	double normSol = 0;
	for (int i = 0; i < y.size(); i++)
	{
		normSol += abs(y[i]);
	}
	double normSolImprecise = 0;
	for (int i = 0; i < y.size(); i++)
	{
		normSolImprecise += abs(y[i] - yImprecise[i]);
	}
	cout << "Relative error: " << normSolImprecise / normSol << "\n";

	return 0;
}

//310