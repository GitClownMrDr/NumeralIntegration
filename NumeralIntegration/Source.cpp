#include <iostream>
#include <math.h>
#include <omp.h>
#include <ctime>
double f(double x) {
	return 2*x;
}
using namespace std;
/*
Численное интегрирование методом прямоугольников
*/

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	cout << "Введите отрезок: ";
	double a, b, dx, x, Sfx=0;
	cin >> a >> b;
	cout << "Введите число разбиений: ";
	int N;
	cin >> N;

	dx = (b - a) / N;
	x = a;
	unsigned int start_time = clock();
	for (int i = 0; i < N; ++i) {
		Sfx += f(x)*dx;
		x += dx;
	}
	unsigned int end_time = clock();
	cout << "Вычисление в одном потоке: " << Sfx << ' ' << end_time - start_time << '\n';
	x = a;
	Sfx = 0;
	start_time = clock();
	omp_set_num_threads(4);
	#pragma omp parallel for reduction(+:Sfx)
	for (int i = 0; i < N; ++i) {
		Sfx += f(x + dx*i) * dx;
	}

	end_time = clock();

	cout << "Многопоточное " << omp_get_max_threads() << " вычисление: " << Sfx << ' ' << end_time - start_time << '\n';
}