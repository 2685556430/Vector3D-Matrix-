#include <iostream>
#include <vector>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <Vector3D.h>
using namespace std;
using namespace ddwl;
vector<Vector3D> V;									//顶点集			
void LINE(Vector3D &sp, Vector3D &ep) {				//方便画线
	line(sp.x, sp.y, ep.x, ep.y);
}
void initDrawStyle() {//初始化绘画风格
	setlinecolor(RGB(120, 150, 255));
	setlinestyle(PS_SOLID, 4);
}
void initSet() {//初始化点集
	/*一个棱锥*/
	{
		V.push_back({ 500,300,100 });
		V.push_back({ 400,400,0 });
		V.push_back({ 400,400,200 });
		V.push_back({ 600,400,200 });
		V.push_back({ 600,400,0 });
		V.push_back({ 500,500,100 });
	}

}
void drawGraph() {				//绘图
	int sz = V.size();
	while (1) {
		for (int i = 0; i < sz; i++) {
			V[i].RotateByVector(0.03, Vector3D(2, 1, 0));//绕着窗口主对角线旋转
		}
		BeginBatchDraw();
		for (int i = 1; i < 5; i++) {
			LINE(V[0], V[i]);
			LINE(V[5], V[i]);
		}
		LINE(V[1], V[2]);
		LINE(V[1], V[4]);
		LINE(V[3], V[4]);
		LINE(V[2], V[3]);
		EndBatchDraw();
		cleardevice();
	}
}
int main() {
	/*绘制一个绕轴旋转的物体*/
	initgraph(1920, 1080);
	initDrawStyle();
	initSet();
	drawGraph();
	_getch();
	system("pause");
	return 0;
}