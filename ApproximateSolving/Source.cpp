#include <iostream>
#include <cstdlib>
#include <cassert>
#include <omp.h>
#include <cmath>
#include <list>
#include <vector>
using namespace std;

vector <double> sub (vector <double> a, vector <double> b) {
	assert(a.size() == b.size());
	vector <double> c(a.size());
	for (int i = 0; i < a.size(); i++) {
		c[i] = a[i] - b[i];
	}
	return c;
}
vector <double> mulMatrix(vector < vector < double>> A, vector <double> b) {
	assert(A[0].size() == b.size());
	vector <double> c(b.size());
	for (int i = 0; i < b.size(); i++) {
		c[i] = 0;
		for (int j = 0; j < b.size(); j++) {
			c[i] += A[i][j] * b[j];
		}
	}
	return c;
}
vector <double> mulScalar(vector <double> b, double t) {
	vector <double> c(b.size());
	for (int i = 0; i < b.size(); i++) {
			c[i] = t* b[i];
	}
	return c;
}
void n(vector < vector < double>> A, vector <double> b, vector <double>& x, double t) {
	x = sub(x, mulScalar(sub(mulMatrix(A, x), b), t));
}
double norm(vector <double> a) {
	double norm1=0;
	for (int i = 0; i < a.size(); i++) {
		norm1 += a[i] * a[i];
	}
	return sqrt(norm1);
}
vector <double> solve(vector < vector < double>> A, vector <double> b, vector <double> x0, double t, double e) {
	while (norm(sub(mulMatrix(A, x0), b)) / norm(b) >= e) {
		n(A, b, x0, t);
	}
	return x0;
}
int main() {
	double t, e;
	int N;
	cin >> N;
	vector < vector < double>> A(N, vector <double> (N));
	vector <double> b(N);
	vector <double> x0(N);
	t = 0.1;
	e = 1E-6;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < N; i++) {
		x0[i] = 1;
	}
	x0 = solve(A, b, x0, t, e);
	for (int i = 0; i < N; i++) {
		cout << x0[i] << endl;
	}
}