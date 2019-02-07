#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>
#include <memory>

# define PI 3.14159265358979323846

using namespace std;

class Coordinates {
 private:
     string CoordinateSystem, PointName;
     double x, y;
 public:
     Coordinates(string PointName, string CoordinateSystem, double first, string second): PointName(PointName),
                                                                               CoordinateSystem(CoordinateSystem) {
         if (CoordinateSystem == "Polar") {
             string strAngle = second.substr(3);
             int angleCoef = stoi(strAngle);
             double radianAngle = PI / angleCoef;
             x = first * cos(radianAngle);
             y = first * sin(radianAngle);
         } else {
             x = first;
             y = stoi(second);
         }

     }

     string name() {
         return PointName;
     }

     pair<double, double> get_coordinates() {
         auto coord = make_pair(x, y);
         return coord;
     }
};

double dist(shared_ptr<Coordinates> p1, shared_ptr<Coordinates> p2) {
    auto pair1 = p1->get_coordinates();
    auto pair2 = p2->get_coordinates();
    return(sqrt(pow(pair1.second - pair2.second, 2) + pow(pair1.first - pair2.second, 2)));
}

class PointDistances {
 private:
     vector<shared_ptr<Coordinates>> points;
 public:
     PointDistances(): points() {
     }

     void addPoint(Coordinates point) {
         auto pointer = make_shared<Coordinates>(point);
         points.push_back(pointer);
     }

     pair<shared_ptr<Coordinates>, shared_ptr<Coordinates>> closest_points() {
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

void printCoords(pair<double, double> x) {
    cout << x.first << ' ' << x.second << '\n';
}

int main() {
    PointDistances vec = PointDistances();
    Coordinates p1("A", "Polar", 8, "pi/6");
    Coordinates p2("B", "Polar", 10, "pi/3");
    Coordinates p3("C", "Cartesian", 2, "8");
    Coordinates p4("D", "Cartesian", 4, "10");
    vec.addPoint(p1);
    vec.addPoint(p2);
    vec.addPoint(p3);
    vec.addPoint(p4);
    auto closestPoints = vec.closest_points();
    auto coords1 = closestPoints.first->get_coordinates();
    auto coords2 = closestPoints.second->get_coordinates();
    cout << closestPoints.first->name() << ' ';
    printCoords(coords1);
    cout << closestPoints.second->name() << ' ';
    printCoords(coords2);
    return 0;
}
