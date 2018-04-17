#include <iostream> // cout 
#include <math.h> // pow 
//#include <unistd.h>
#include <stdlib.h> //rand
#include <fstream> //
#include <string> //string
#include "cel.hpp"

using namespace std;
fstream file;

	double cel::getspeed(int i){
		return speed[i];
	}
	double cel::getcoord(int i){
		return coord[i];
	}
	int    cel::getmass(){
		return mass;
	}
	void cel::setspeed(double speed_buf, int i){
		speed[i] = speed_buf;
	}
	void cel::setcoord(double coord_buf, int i){
		coord[i] = coord_buf;
	}
	void cel::setmass(int mass_buf){
		mass = mass_buf;
	}
	void cel::eval(double F, int j, double t, double dt){
			double a;
			a = F / this->getmass();	// расчет ускорения через силу
			double dv = a * dt;
			this->setspeed(this->getspeed(j) + dv, j); //расчет скорости через ускорение
			double dx = dv * dt;
			this->setcoord(this->getcoord(j) + this->getspeed(j) + dx, j); // расчет координат через скорость и ускорение
			//cout << getcoord(j) << endl;
	}


cel::cel(){
	for (int i = 0; i < 3; i++){
		speed[i] = 0;
		coord[i] = rand() % 100; // случайные координаты от 0 до 100
	}
	mass = rand() % 6000 + 2000; // масса тела от 2000 до 8000
	cout << "mass = " << mass << endl; // вывод в терминал значений массы
	file.open("log.csv", fstream::out|fstream::app);
	cout << " coords: x = " << coord[0] << " y = " << coord[1] << " z = " << coord[2] << endl; // вывод в терминал значений координат
	file << coord[0] << ", " << coord[1] << ", " << coord[2] << endl; // запись в файл значений координат
	file.close();
}


int main(){
	srand(time(0));
	double F[3]; //x, y, z сила притяжения
	double FAB[3]; //x, y, z сила притяжения
	double FBT[3]; //x, y, z сила притяжения
	double dt = 0.1; //шаг
	double t = 0; // начальное время
	double G = 6.6740831 * pow(0.1,11); // гравитационная постоянная
	file.open("log.csv", fstream::out|fstream::app);
	file << "--0--" << endl;
	file.close();
	cel B[3];

	file.open("log.csv", fstream::out|fstream::app);
	int iteration = 1;
	while(1){
		t = t + dt;
		file << "--" << iteration << "--" <<endl;
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				F[j] = G * B[k].getmass() * B[(k + 1) % 3].getmass() * (B[k].getcoord(j) - B[(k + 1) % 3].getcoord(j))/abs(B[k].getcoord(j) - B[(k + 1) % 3].getcoord(j)) / pow(B[k].getcoord(j) - B[(k + 1) % 3].getcoord(j), 2); 
	 			F[j] += G * B[k].getmass() * B[(k + 2) % 3].getmass() * (B[k].getcoord(j) - B[(k + 2) % 3].getcoord(j))/abs(B[k].getcoord(j) - B[(k + 2) % 3].getcoord(j))/ pow(B[k].getcoord(j) - B[(k + 2) % 3].getcoord(j), 2);
	 			B[k].eval(F[j], j, t, dt); //строка 30
	 		}
	 	}
	 	// cout << "1, " << B[1].getcoord(0) << ", " << B[1].getcoord(1) << ", " << B[1].getcoord(2) << endl; //вывод в терминал
	 	// cout << "2, " << B[2].getcoord(0) << ", " << B[2].getcoord(1) << ", " << B[2].getcoord(2) << endl;
	 	// cout << "3, " << B[3].getcoord(0) << ", " << B[3].getcoord(1) << ", " << B[3].getcoord(2) << endl;
		file << "0, " << B[0].getcoord(0) << ", " << B[0].getcoord(1) << ", " << B[0].getcoord(2) << " speeds " << B[0].getspeed(0) << ", " << B[0].getspeed(1) << ", " << B[0].getspeed(2) << endl; //запись в файл
	 	file << "1, " << B[1].getcoord(0) << ", " << B[1].getcoord(1) << ", " << B[1].getcoord(2) << " speeds " << B[1].getspeed(0) << ", " << B[1].getspeed(1) << ", " << B[1].getspeed(2) << endl;
	 	file << "2, " << B[2].getcoord(0) << ", " << B[2].getcoord(1) << ", " << B[2].getcoord(2) << " speeds " << B[2].getspeed(0) << ", " << B[2].getspeed(1) << ", " << B[2].getspeed(2) << endl;

	 	iteration++;
	}
	file.close();
	return 0;
}