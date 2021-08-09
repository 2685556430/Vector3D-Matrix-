#pragma once
#include<iostream>
#include <cmath>
#include <assert.h>//��������޽�����û��������㲻������ѧ�߼� ����
using namespace std;

#define ERROR 1e-10
#define ESP(val) (fabs(val) <= ERROR) ? 0.0 : val	//����С��������Ϊ0
class Mat {
private:
	double **p;										//��άָ��
	int rows, cols;									//����ĳߴ�
	void initMatrix();								//Ϊ�������ռ�

	/*************************��������****************************/
public:
	/*��ʼ������*/
	explicit Mat(int r, int c);						//Ĭ��
	explicit Mat(int r, int c, double val);			//����
	explicit Mat(int r, int c, int val);			//����
	Mat(const Mat & m);								//����
	Mat(int r, int c, double *arr);					//����
	virtual ~Mat();
public:
	/*���ز��������*/
	Mat operator=(const Mat& arr);								//����ֵ����
	Mat operator=(double *arr);									//���鸳ֵ���������ǰ֪������ߴ磩
	bool operator==(const Mat& arr)const;						//�ȼ������
	Mat operator*=(const Mat& arr);								//�ӡ�������
	Mat operator+=(const Mat& arr);
	Mat operator-=(const Mat& arr);
	Mat operator*(const Mat& arr)const;
	Mat operator+(const Mat& arr)const;
	Mat operator-(const Mat& arr)const;
	double* operator[](int index)const;							//[] ����
	friend istream &operator >> (istream &in, Mat &arr);		//cin����
	friend ostream &operator << (ostream &out,const Mat &arr);	//cout���
public:
	void Solve(Mat& outArr)const;				//���nԪһ�η���
	Mat T()const;								//ת�þ���
	Mat Inv()const;								//�������
	double det()const;							//����ʽ
	Mat matPow(int n)const;						//�����n����
	void Normalizing(int r, int c);				//��λ������
	int row()const;
	int col()const;
	void swapLine(int r1, int r2);				//�н���
	void Show()const;

};
/******************************������*********************************/
void Mat::initMatrix() {//����ռ�
	p = new double * [rows];
	for (int i = 0; i < rows; i++) {
		p[i] = new double[cols];
	}
}
Mat::Mat(int r = 1, int c = 1) {//����Ĭ��ȫΪ0�ľ���
	rows = r, cols = c;
	initMatrix();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			p[i][j] = 0.0;
		}
	}
}
Mat::Mat(int r, int c, double val) {//�������ʼֵ�ľ���
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
Mat::~Mat() {//��������
	for (int i = 0; i < rows; ++i) {
		delete[] p[i];
	}
	delete[] p;
}
Mat Mat::operator = (const Mat &arr) {
	if (this == &arr) return *this;//��ַ��ͬ��һ������

	if (!(rows == arr.rows&&cols == arr.cols)) {	//�ߴ粻ͬ���¹���
		this->~Mat();								//�ͷŵ���ǰ�ľ���
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
			throw "����Խ�磡\n";
	}
	catch (char *a) {
		cout << a;
	}
	return *(p + index);
}

void Mat::Solve(Mat& outArr)const {					//ͨ��������� ��� ��˹��Ԫ��Ax = b�Ľ�
	if (rows != cols - 1) assert(0);				//���������޷����
	Mat A(*this);									//�����󿽱�
	/*�����б任ת��Ϊ������*/
	for (int i = 0; i < A.rows; i++) {
		for (int j = i + 1; j < A.rows; j++) {
			double k;
			if (A.p[i][i] == 0) {			//�����һ��Ԫ����0������������ķ����н���
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
	/*�õ� �����Ǿ���*/
	/*���¶��ϴ������*/
	outArr = Mat(A.rows, 1);
	if (A.p[A.rows - 1][A.rows - 1] == 0 && A.p[A.rows - 1][A.cols - 1] != 0) assert(0);//��һ��ϵ������ȫΪ0�ҳ����Ϊ0���޽�
	for (int i = A.rows - 1; i >= 0; i--) {
		double s = 0.0;
		for (int j = i + 1; j < A.cols - 1; j++) s += outArr.p[j][0] * A.p[i][j];
		if (A.p[i][i] != 0) {
			outArr.p[i][0] = (A.p[i][cols - 1] - s) / A.p[i][i];
		}
	}
}
Mat Mat::T()const {//ת�þ���
	Mat T(cols, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			T.p[j][i] = p[i][j];
		}
	}
	return T;
}
Mat Mat::Inv()const {//�������
	if (rows != cols) assert(0);
	Mat E;
	E.Normalizing(rows, cols);
	Mat A(*this);		  //������ľ��󿽱�
	/*�����б任ת��Ϊ������*/
	for (int i = 0; i < A.rows; i++) {
		for (int j = i + 1; j < A.rows; j++) {
			double k;
			if (A.p[i][i] == 0) {//�����һ��Ԫ����0������������ķ����н���
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
	/*�ڶ���ת��Ϊ������*/
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
	/*�Խǻ���λ��*/
	for (int i = 0; i < A.rows; i++) {
		if (A.p[i][i] == 0) assert(0);//�������
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
			if (A.p[i][i] == 0) {//�����һ��Ԫ����0������������ķ����н���
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
	/*�����ݳ�*/
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