#pragma once
#include <cmath>
#include <iostream>
using namespace std;
const double PI = 3.1415926;
//转角度
double Deg(double rad) { return rad * 180.0 / PI; }
//转弧度
double Rad(double deg) { return deg / 180.0 * PI; }
/*3D向量头*/

class Vector3D {
public:
	explicit Vector3D(double px = 1, double py = 0, double pz = 0) :x(px), y(py), z(pz) {};
	~Vector3D() {};
	double x, y, z;
	Vector3D operator = (const Vector3D &b) {
		this->x = b.x, this->y = b.y, this->z = b.z;
		return *this;
	}
	Vector3D operator + (const Vector3D &b)const {			//加法
		return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Vector3D operator - (const Vector3D &b)const {			//减法
		return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	Vector3D operator += (const Vector3D &b) {				//加法
		this->x += b.x, this->y += b.y, this->z += b.z;
		return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Vector3D operator -= (const Vector3D &b) {				//减法
		this->x -= b.x, this->y -= b.y, this->z -= b.z;
		return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	Vector3D operator () (double px, double py, double pz) {
		this->x = px, this->y = py, this->z = pz;
		return *this;
	}

	double operator * (const Vector3D &b)const {			//向量内积 标量
		return (this->x * b.x + this->y * b.y + this->z*b.z);
	}
	Vector3D operator * (const double &k)const {			//向量数乘
		return Vector3D(this->x * k, this->y * k, this->z * k);
	}
	Vector3D operator *= (const double &k) {				//向量数乘
		this->x *= k, this->y *= k, this->z *= k;
		return *this;
	}
	bool operator ==(const Vector3D &b)const {
		if (this->norm2() == b.norm2()) {
			double alpha;
			if (this->norm2() == 0) return true;
			alpha = Deg(acos((*this)*b / (this->norm()*b.norm())));
			if (fabs(alpha - 180) <= 1e-3 || fabs(alpha) <= 1e-3) return true;
		}

		return false;
	}
	bool operator !=(const Vector3D &b)const {
		return !(*this == b);
	}

public:														//成员函数
	double norm()const {									//向量的模
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}
	double norm2()const {
		return (this->x*this->x + this->y*this->y + this->z*this->z);
	}
	void Normalizing() {
		//单位化
		double k = (*this).norm();
		if (k == 0) return;
		this->x /= k, this->y /= k, this->z /= k;
	}
};

double Angle(const Vector3D &a, const Vector3D &b) {					//两个向量夹角
	if (a.norm() == 0) return 0;
	return Deg(acos(a*b / (a.norm()*b.norm())));
}

Vector3D multiply(const Vector3D &a, const Vector3D &b) {//向量叉乘 矢量
	return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

ostream& operator<<(ostream &out, const Vector3D &a) {
	out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
	return out;
}
