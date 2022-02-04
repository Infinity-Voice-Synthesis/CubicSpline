#include "CubicS.h"

CubicS::CubicS()
{

}

CubicS::CubicS(double* x, double* y, int64_t n)
	:x(x), y(y), n(n)
{
	A = new double[n - 2];
	B = new double[n - 2];
	C = new double[n - 2];
	D = new double[n - 2];
	E = new double[n - 2];
	H = new double[n - 1];
	M = new double[n];
}

CubicS::~CubicS()
{
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
	delete[] E;
	delete[] H;
	delete[] M;
}

void CubicS::caculate(double* a, double* b, double* c, double* d)
{
	if (
		a == nullptr ||
		b == nullptr ||
		c == nullptr ||
		d == nullptr
		){
		return;
	}
	if (
		this->x == nullptr ||
		this->y == nullptr ||
		this->n < 2
		) {
		return;
	}

	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;

	if (this->n == 2) {
		this->a[0] = 0;
		this->b[0] = 0;
		this->c[0] = (this->y[1] - this->y[0]) / (this->x[1] - this->x[0]);
		this->d[0] = this->y[0] - this->x[0] * this->c[0];
		return;
	}//只有两点，无需三次插值

	for (int64_t i = 0; i < this->n - 1; i++) {
		this->H[i] = this->x[i + 1] - this->x[i];
	}//h[i]赋值

	for (int64_t i = 0; i < this->n - 2; i++) {
		this->A[i] = this->H[i];
		this->B[i] = 2 * (this->H[i] + this->H[i + 1]);
		this->C[i] = this->H[i + 1];
	}//自然边界下左侧矩阵前后有常数，舍去

	for (int64_t i = 0; i < this->n - 2; i++) {
		this->D[i] = 6 * ((this->y[i + 2] - this->y[i + 1]) / this->H[i + 1] - (this->y[i + 1] - this->y[i]) / this->H[i]);
	}//自然边界下右侧矩阵前后有常数，舍去

	this->TDMA(this->n - 2);//矩阵求解

	if (this->n == 3) {
		this->E[0] = (6 * ((this->y[2] - this->y[1]) / this->H[1] - (this->y[1] - this->y[0]) / this->H[0])) / (2 * (this->H[0] + this->H[1]));
	}//只有三点时直接求解

	this->M[0] = 0;
	this->M[n - 1] = 0;
	for (int64_t i = 1; i < n - 1; i++) {
		this->M[i] = this->E[i - 1];
	}//二阶导数

	for (int64_t i = 0; i < n - 1; i++) {
		this->a[i] = (this->M[i + 1] - this->M[i]) / (6 * this->H[i]);
		this->b[i] = this->M[i] / 2;
		this->c[i] = (this->y[i + 1] - this->y[i]) / this->H[i] - this->H[i] * this->M[i] / 2 - this->H[i] * (this->M[i + 1] - this->M[i]) / 6;
		this->d[i] = this->y[i];
	}//求解系数
}

void CubicS::TDMA(int64_t n)
{
	if (n < 1) {
		return;
	}

	this->C[0] /= this->B[0];
	this->D[0] /= this->B[0];

	for (int64_t i = 1; i < n; i++) {
		double temp = this->B[i] - this->A[i] * this->C[i - 1];
		this->C[i] /= temp;
		this->D[i] = (this->D[i] - this->A[i] * this->D[i - 1]) / temp;
	}

	this->E[n - 1] = this->D[n - 1];

	for (int64_t i = n - 2; i >= 0; i--) {
		this->E[i] = this->D[i] - this->C[i] * this->E[i + 1];
	}
}

double CubicS::result(double t)
{
	if (
		a == nullptr ||
		b == nullptr ||
		c == nullptr ||
		d == nullptr
		) {
		return 0;
	}
	if (
		this->x == nullptr ||
		this->y == nullptr ||
		this->n < 2
		) {
		return 0;
	}
	for (int64_t i = 0; i < this->n - 1; i++) {
		if (t >= this->x[i] && t < this->x[i + 1]) {
			double delta = t - this->x[i];
			double res = ((this->a[i] * delta + this->b[i]) * delta + this->c[i]) * delta + this->d[i];
			return res;
		}
	}
	return 0;
}
