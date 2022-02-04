#pragma once

#include <cstdlib>
#include <cstdint>

class CubicS final
{
public:
	CubicS(double* x, double* y, int64_t n);
	~CubicS();

	void caculate(double* a, double* b, double* c, double* d);
	double result(double t);
private:
	CubicS();

	double* x = nullptr;
	double* y = nullptr;
	int64_t n = 0;//输入

	double* a = nullptr;
	double* b = nullptr;
	double* c = nullptr;
	double* d = nullptr;//输出

	double* A = nullptr;
	double* B = nullptr;
	double* C = nullptr;
	double* D = nullptr;
	double* E = nullptr;
	double* H = nullptr;
	double* M = nullptr;//中间缓存

	void TDMA(int64_t n);//三角矩阵求解

};