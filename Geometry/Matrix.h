#pragma once
#include<iostream>
#include <cmath>
#include <assert.h>//如果方程无解或矩阵没有逆或运算不符合数学逻辑 报错
using namespace std;

#define ERROR 1e-10
#define ESP(val) (fabs(val) <= ERROR) ? 0.0 : val	//过于小的数字视为0
class Mat {
private:
	double **p;										//二维指针
	int rows, cols;									//矩阵的尺寸
	void initMatrix();								//为矩阵分配空间

	/*************************函数声明****************************/
public:
	/*初始化构造*/
	explicit Mat(int r, int c);						//默认
	explicit Mat(int r, int c, double val);			//浮点
	explicit Mat(int r, int c, int val);			//整型
	Mat(const Mat & m);								//矩阵
	Mat(int r, int c, double *arr);					//数组
	virtual ~Mat();
public:
	/*重载操作运算符*/
	Mat operator=(const Mat& arr);								//矩阵赋值矩阵
	Mat operator=(double *arr);									//数组赋值矩阵（最好提前知道矩阵尺寸）
	bool operator==(const Mat& arr)const;						//等价运算符
	Mat operator*=(const Mat& arr);								//加、减、乘
	Mat operator+=(const Mat& arr);
	Mat operator-=(const Mat& arr);
	Mat operator*(const Mat& arr)const;
	Mat operator+(const Mat& arr)const;
	Mat operator-(const Mat& arr)const;
	double* operator[](int index)const;							//[] 访问
	friend istream &operator >> (istream &in, Mat &arr);		//cin输入
	friend ostream &operator << (ostream &out,const Mat &arr);	//cout输出
public:
	void Solve(Mat& outArr)const;				//求解n元一次方程
	Mat T()const;								//转置矩阵
	Mat Inv()const;								//矩阵的逆
	double det()const;							//行列式
	Mat matPow(int n)const;						//矩阵的n次幂
	void Normalizing(int r, int c);				//单位化矩阵
	int row()const;
	int col()const;
	void swapLine(int r1, int r2);				//行交换
	void Show()const;

};
/******************************函数体*********************************/
void Mat::initMatrix() {//分配空间
	p = new double * [rows];
	for (int i = 0; i < rows; i++) {
		p[i] = new double[cols];
	}
}
Mat::Mat(int r = 1, int c = 1) {//构造默认全为0的矩阵
	rows = r, cols = c;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = 0.0;
		}
	}
}
Mat::Mat(int r, int c, double val) {//构造带初始值的矩阵
	rows = r, cols = c;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = val;
		}
	}
}
Mat::Mat(int r, int c, int val) {
	rows = r, cols = c;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = val;
		}
	}
}
Mat::Mat(const Mat & m) {
	rows = m.rows;
	cols = m.cols;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = m.p[i][j];
		}
	}
}
Mat::Mat(int r, int c, double *arr) {
	rows = r, cols = c;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = *(arr + i*cols + j);
		}
	}
}
Mat::~Mat() {//析构函数
	for (int i = 0; i < rows; ++i) {
		delete[] p[i];
	}
	delete[] p;
}
Mat Mat::operator = (const Mat &arr) {
	if (this == &arr) return *this;//地址相同是一个矩阵

	if (!(rows == arr.rows&&cols == arr.cols)) {	//尺寸不同重新构造
		this->~Mat();								//释放掉先前的矩阵
		rows = arr.rows;
		cols = arr.cols;
		initMatrix();
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = arr.p[i][j];
		}
	}
	return *this;
}
Mat Mat::operator = (double *arr) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = *(arr + i*cols + j);
		}
	}
	return *this;
}
bool Mat::operator == (const Mat& arr)const {
	if (!(rows == arr.rows&&cols == arr.cols)) return false;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (p[i][j] != arr.p[i][j]) return false;
		}
	}
	return true;
}
Mat Mat::operator *= (const Mat& arr) {
	if (rows != arr.cols) assert(0);
	Mat temp(rows, arr.cols);
	for (int i = 0; i < temp.rows; i++) {
		for (int j = 0; j < temp.cols; j++) {
			for (int k = 0; k < cols; k++) {
				temp.p[i][j] += p[i][k] * arr.p[k][j];
			}
			temp.p[i][j] = ESP(temp.p[i][j]);
		}
	}
	*this = temp;
	return *this;
}
Mat Mat::operator * (const Mat& arr)const {
	if (rows != arr.cols) assert(0);
	Mat temp(rows, arr.cols, 0.0);
	for (int i = 0; i < temp.rows; i++) {
		for (int j = 0; j < temp.cols; j++) {
			for (int k = 0; k < cols; k++) {
				temp.p[i][j] += p[i][k] * arr.p[k][j];
			}
			temp.p[i][j] = ESP(temp.p[i][j]);//
		}
	}
	return temp;
}
Mat Mat::operator += (const Mat& arr) {
	if (!(rows == arr.rows&&cols == arr.cols)) assert(0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] += arr.p[i][j];
		}
	}
	return *this;
}
Mat Mat::operator -= (const Mat& arr) {
	if (!(rows == arr.rows&&cols == arr.cols)) assert(0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] -= arr.p[i][j];
		}
	}
	return *this;
}
Mat Mat::operator + (const Mat& arr)const {
	if (!(rows == arr.rows&&cols == arr.cols)) assert(0);
	Mat temp(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			temp.p[i][j] = p[i][j] + arr.p[i][j];
		}
	}
	return temp;
}
Mat Mat::operator - (const Mat& arr)const {
	if (!(rows == arr.rows&&cols == arr.cols)) assert(0);
	Mat temp(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			temp.p[i][j] = p[i][j] - arr.p[i][j];
		}
	}
	return temp;
}
double* Mat::operator[](int index)const {
	try{
		if (index >= cols - 1)
			throw "访问越界！\n";
	}
	catch (char *a) {
		cout << a;
	}
	return *(p + index);
}

void Mat::Solve(Mat& outArr)const {					//通过增广矩阵 结合 高斯消元求Ax = b的解
	if (rows != cols - 1) assert(0);				//条件不足无法求解
	Mat A(*this);									//将矩阵拷贝
	/*进行行变换转换为上三角*/
	for (int i = 0; i < A.rows; i++) {
		for (int j = i + 1; j < A.rows; j++) {
			double k;
			if (A.p[i][i] == 0) {			//如果这一个元素是0，尝试与下面的非零行交换
				for (int m = i + 1; m < A.rows; m++) {
					if (A.p[m][i] != 0) {
						A.swapLine(i, m);
						break;
					}
				}
				if (A.p[i][i] == 0) k = 0;
				else k = A.p[j][i] / A.p[i][i];
			}
			else k = A.p[j][i] / A.p[i][i];
			for (int m = i; m < A.cols; m++) {
				A.p[j][m] -= A.p[i][m] * k;
			}
		}
	}
	/*得到 “三角矩阵”*/
	/*自下而上待入求解*/
	outArr = Mat(A.rows, 1);
	if (A.p[A.rows - 1][A.rows - 1] == 0 && A.p[A.rows - 1][A.cols - 1] != 0) assert(0);//有一行系数矩阵全为0且常数项不为0则无解
	for (int i = A.rows - 1; i >= 0; i--) {
		double s = 0.0;
		for (int j = i + 1; j < A.cols - 1; j++) s += outArr.p[j][0] * A.p[i][j];
		if (A.p[i][i] != 0) {
			outArr.p[i][0] = (A.p[i][cols - 1] - s) / A.p[i][i];
		}
	}
}
Mat Mat::T()const {//转置矩阵
	Mat T(cols, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			T.p[j][i] = p[i][j];
		}
	}
	return T;
}
Mat Mat::Inv()const {//矩阵的逆
	if (rows != cols) assert(0);
	Mat E;
	E.Normalizing(rows, cols);
	Mat A(*this);		  //将求逆的矩阵拷贝
	/*进行行变换转换为上三角*/
	for (int i = 0; i < A.rows; i++) {
		for (int j = i + 1; j < A.rows; j++) {
			double k;
			if (A.p[i][i] == 0) {//如果这一个元素是0，尝试与下面的非零行交换
				for (int m = i + 1; m < A.rows; m++) {
					if (A.p[m][i] != 0) {
						A.swapLine(i, m);
						E.swapLine(i, m);
						break;
					}
				}
				if (A.p[i][i] == 0) k = 0;
				else k = A.p[j][i] / A.p[i][i];
			}
			else k = A.p[j][i] / A.p[i][i];
			for (int m = 0; m < A.cols; m++) {

				A.p[j][m] -= A.p[i][m] * k;
				E.p[j][m] -= E.p[i][m] * k;
			}
			
		}
	}
	/*第二次转换为下三角*/
	for (int i = A.rows - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			double k;
			if (A.p[i][i] == 0) k = 0;
			else k = A.p[j][i] / A.p[i][i];

			for (int m = A.rows - 1; m >= 0; m--) {
				A.p[j][m] -= A.p[i][m] * k;
				E.p[j][m] -= E.p[i][m] * k;
			}
		}
	}
	/*对角化单位阵*/
	for (int i = 0; i < A.rows; i++) {
		if (A.p[i][i] == 0) assert(0);//无逆矩阵
		double k = A.p[i][i];
		A.p[i][i] = 1;
		for (int j = 0; j < A.cols; j++)
			E.p[i][j] /= k;
	}
	return E;
}
double Mat::det()const {
	double res = 1.0;
	Mat A(*this);
	for (int i = 0; i < A.rows; i++) {
		for (int j = i + 1; j < A.rows; j++) {
			double k;
			if (A.p[i][i] == 0) {//如果这一个元素是0，尝试与下面的非零行交换
				for (int m = i + 1; m < A.rows; m++) {
					if (A.p[m][i] != 0) {
						A.swapLine(i, m);
						res *= -1.0;
						break;
					}
				}
				if (A.p[i][i] == 0) k = 0;
				else k = A.p[j][i] / A.p[i][i];
			}
			else k = A.p[j][i] / A.p[i][i];
			for (int m = 0; m < A.cols; m++) {
				A.p[j][m] -= A.p[i][m] * k;
			}

		}
	}
	for (int i = 0; i < A.rows; i++) res *= A.p[i][i];
	return res;
}
Mat Mat::matPow(int n)const {
	/*快速幂乘*/
	if (cols != rows) assert(0);
	Mat t(rows, cols), a = *this;
	t.Normalizing(rows, cols);
	while (n) {
		if (n & 1)
			t *= a;
		n >>= 1;
		a *= a;
	}
	return t;
}
void Mat::Normalizing(int r, int c) {
	if (r != c) assert(0);
	*this = Mat(r, c, 0);
	for (int i = 0; i < r; i++)
		p[i][i] = 1;
}
int Mat::row()const {
	return rows;
}
int Mat::col()const {
	return cols;
}
void Mat::swapLine(int r1, int r2) {
	double *t = p[r1];
	p[r1] = p[r2];
	p[r2] = t;
}
void Mat::Show() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << p[i][j] << " ";
		cout << '\n';
	}
}
istream &operator >> (istream &in, Mat &arr) {
	for (int i = 0; i < arr.rows; i++) {
		for (int j = 0; j < arr.cols; j++) {
			in >> arr.p[i][j];
		}
	}
	return in;
}
ostream &operator << (ostream &out,const Mat &arr) {

	for (int i = 0; i < arr.rows; i++) {
		for (int j = 0; j < arr.cols; j++)
			out << arr.p[i][j] << ' ';
		out << '\n';
	}
	return out;
}