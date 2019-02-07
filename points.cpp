#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>
#include <memory>

# define PI 3.14159265358979323846

using namespace std;

class Coordinates {           //класс для работы с точками на координатной плоскости
 private:
     string CoordinateSystem, PointName;
     double x, y;
 public:                      //инциализация: имя, вид координатной системы (полярная или декартова), и 2 координаты
     Coordinates(string PointName, string CoordinateSystem, double first, string second): PointName(PointName),
                                                                               CoordinateSystem(CoordinateSystem) {
         if (CoordinateSystem == "Polar") {   //если система полярная, то координаты имеют вид r = a, phi = pi/b
             string strAngle = second.substr(3);
             int angleCoef = stoi(strAngle);
             double radianAngle = PI / angleCoef;
             x = first * cos(radianAngle);
             y = first * sin(radianAngle);
         } else {                             //если система декартова, то координаты имеют вид x = a, y = b
             x = first;
             y = stoi(second);
         }

     }

     string name() {                         //возвращает имя точки
         return PointName;
     }

     pair<double, double> get_coordinates() {//возвращает координаты точки в декартовой системе
         auto coord = make_pair(x, y);
         return coord;
     }
};

double dist(shared_ptr<Coordinates> p1, shared_ptr<Coordinates> p2) { //расстояние между точками
    auto pair1 = p1->get_coordinates();
    auto pair2 = p2->get_coordinates();
    return(sqrt(pow(pair1.second - pair2.second, 2) + pow(pair1.first - pair2.second, 2)));
}

class PointDistances {                //класс для хранения точек
 private:
     vector<shared_ptr<Coordinates>> points;
 public:
     PointDistances(): points() {
     }

     void addPoint(Coordinates point) { //добавление точки в вектор
         auto pointer = make_shared<Coordinates>(point);
         points.push_back(pointer);
     }

     pair<shared_ptr<Coordinates>, shared_ptr<Coordinates>> closest_points() { //поиск двух ближайших друг к другу точек в массиве
         double mindist = 99999;
         int point1, point2;
         for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                double current = dist(points[i], points[j]);
                if (current < mindist && i != j) {
                    mindist = current;
                    point1 = i;
                    point2 = j;
                }
            }
         }
         pair<shared_ptr<Coordinates>, shared_ptr<Coordinates>> answer = make_pair(points[point1], points[point2]);
         cout << mindist << '\n';
         return answer;
     }

};

int main() {
    return 0;
}
