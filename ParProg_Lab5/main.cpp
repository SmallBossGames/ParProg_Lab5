#include <iostream>
#include <omp.h>
#include <chrono>


using namespace std;

double Integration(double from, double to, int splitCount, double(*calcFunc)(double x));

int main()
{
	double from, to;
	int splitCount;
	cout << "Vvedite interval:" << endl;
	cout << "Ot:"; cin >> from;
	cout << "Do:"; cin >> to;
	cout << "Vvedite kolichestvo razbienij:"; cin >> splitCount;
	//cout << "Vvedite kolichestvo potokov:"; cin >> threadCount;

	auto begin = chrono::high_resolution_clock::now();
	
	auto result = Integration(from, to, splitCount, [](double x) {return cos(x); });

	auto end = chrono::high_resolution_clock::now();

	cout << result;
	system("pause");
	return 0;
}


double Integration(double from, double to, int splitCount, double (*calcFunc)(double x))
{
	auto step = (to - from) / (double)splitCount;
	auto sum = 0.0;

#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < splitCount; i++)
	{
		auto x1 = from + i * step;
		auto x2 = from + (i + 1) * step;
		sum += calcFunc((x1 + x2) / 2.0) * (x2 - x1);
	}

	return sum;
}

