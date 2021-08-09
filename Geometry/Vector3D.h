#pragma once
#include <cmath>
#include <iostream>
using namespace std;
const double PI = 3.1415926;
//ת�Ƕ�
double Deg(double rad) { return rad * 180.0 / PI; }
//ת����
double Rad(double deg) { return deg / 180.0 * PI; }
/*3D����ͷ*/

class Vector3D {
public:
	explicit Vector3D(double px = 1, double py = 0, double pz = 0) :x(px), y(py), z(pz) {};
	~Vector3D() {};
	double x, y, z;
	Vector3D operator = (const Vector3D &b) {
		this->x = b.x, this->y = b.y, this->z = b.z;
		return *this;
	}
	Vector3D operator + (const Vector3D &b)const {			//�ӷ�
		return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Vector3D operator - (const Vector3D &b)const {			//����
		return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	Vector3D operator += (const Vector3D &b) {				//�ӷ�
		this->x += b.x, this->y += b.y, this->z += b.z;
		return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Vector3D operator -= (const Vector3D &b) {				//����
		this->x -= b.x, this->y -= b.y, this->z -= b.z;
		return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	Vector3D operator () (double px, double py, double pz) {
		this->x = px, this->y = py, this->z = pz;
		return *this;
	}

	double operator * (const Vector3D &b)const {			//�����ڻ� ����
		return (this->x * b.x + this->y * b.y + this->z*b.z);
	}
	Vector3D operator * (const double &k)const {			//��������
		return Vector3D(this->x * k, this->y * k, this->z * k);
	}
	Vector3D operator *= (const double &k) {				//��������
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

public:														//��Ա����
	double norm()const {									//������ģ
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}
	double norm2()const {
		return (this->x*this->x + this->y*this->y + this->z*this->z);
	}
	void Normalizing() {
		//��λ��
		double k = (*this).norm();
		if (k == 0) return;
		this->x /= k, this->y /= k, this->z /= k;
	}
};

double Angle(const Vector3D &a, const Vector3D &b) {					//���������н�
	if (a.norm() == 0) return 0;
	return Deg(acos(a*b / (a.norm()*b.norm())));
}

Vector3D multiply(const Vector3D &a, const Vector3D &b) {//������� ʸ��
	return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

ostream& operator<<(ostream &out, const Vector3D &a) {
	out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
	return out;
}
