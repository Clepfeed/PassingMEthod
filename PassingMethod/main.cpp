#include <iostream>
#include <vector>
#include <random>
//#include <math.h>

using namespace std;

void printVec(vector<double>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << "\n";
}

int main()
{
	srand(time(0));	
	unsigned const int n = 5;
	unsigned const int m = 12;

	vector<double> a(n - 1, 0);
	vector<double> b(n - 1, 0);
	vector<double> c(n, 0);
	vector<double> y(n, 0);

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




	return 0;
}