#include <iostream>
#include <math.h>
#include <omp.h>
#include <ctime>
double f(double x) {
	return 2*x;
}
using namespace std;
/*
��������� �������������� ������� ���������������
*/

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	cout << "������� �������: ";
	double a, b, dx, x, Sfx=0;
	cin >> a >> b;
	cout << "������� ����� ���������: ";
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
	cout << "���������� � ����� ������: " << Sfx << ' ' << end_time - start_time << '\n';
	x = a;
	Sfx = 0;
	start_time = clock();
	omp_set_num_threads(4);
	#pragma omp parallel for reduction(+:Sfx)
	for (int i = 0; i < N; ++i) {
		Sfx += f(x + dx*i) * dx;
	}

	end_time = clock();

	cout << "������������� " << omp_get_max_threads() << " ����������: " << Sfx << ' ' << end_time - start_time << '\n';
}