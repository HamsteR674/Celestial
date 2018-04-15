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
	void cel::eval(double FTA, double FBT, int j, double t){
			double a;
			a = (FTA + FBT)/ this->getmass();	// расчет ускорения через силу
			this->setspeed(this->getspeed(j) + a * t, j); //расчет скорости через ускорение
			this->setcoord(this->getcoord(j) + this->getspeed(j) + a * pow(t, 2) / 2, j); // расчет координат через скорость и ускорение
			//cout << getcoord(j) << endl;
	}


cel::cel(string name){
	for (int i = 0; i < 3; i++){
		speed[i] = 0;
		coord[i] = rand() % 100; // случайные координаты от 0 до 100
	}
	name = name;
	mass = rand() % 6000 + 2000; // масса тела от 2000 до 8000
	cout << "mass = " << mass << endl; // вывод в терминал значений массы
	file.open("log.csv", fstream::out|fstream::app);
	cout << " coords: x = " << coord[0] << " y = " << coord[1] << " z = " << coord[2] << endl; // вывод в терминал значений координат
	file << name << ", " << coord[0] << ", " << coord[1] << ", " << coord[2] << endl; // запись в файл значений координат
	file.close();
}



int main(){
	srand(time(0));
	double FTA[3]; //x, y, z сила притяжения Tul Arc
	double FAB[3]; //x, y, z сила притяжения Arc Ber
	double FBT[3]; //x, y, z сила притяжения Ber Tul
	double dt = 0.1; //шаг
	double t = 0; // начальное время
	double G = 6.6740831 * pow(0.1,11); // гравитационная постоянная
	file.open("log.csv", fstream::out|fstream::app);
	file << "--0--" << endl;
	file.close();
	cout << "Tul" << endl;
	cel Tul("Tul"); // создание экземпляра класса (файл cel.hpp)
	cout << "Arc" << endl;
	cel Arc("Arc");
	cout << "Ber" << endl;
	cel Ber("Ber"); 
	if(!file){
		cout << "error" << endl;
		return -1;
	}
	file.open("log.csv", fstream::out|fstream::app);
	int iteration = 1;
	while(1){
		t = t + dt;
		file << "--" << iteration << "--" <<endl;
		for(int j = 0; j < 3; j++){
			FTA[j] = G * Tul.getmass() * Arc.getmass() / pow(Tul.getcoord(j) - Arc.getcoord(j), 2); // расчитали силу притяжения Tul и Arc
			FAB[j] = G * Arc.getmass() * Ber.getmass() / pow(Arc.getcoord(j) - Ber.getcoord(j), 2);	// расчитали силу притяжения Arc и Бер 
			FBT[j] = G * Ber.getmass() * Tul.getmass() / pow(Ber.getcoord(j) - Tul.getcoord(j), 2);	// расчитали силу притяжения Ber и Tul
			Tul.eval(FTA[j], FBT[j], j, t); //строка 30
			Arc.eval(FTA[j], FAB[j], j, t);
			Ber.eval(FBT[j], FAB[j], j, t);
		}
		//file.open("log.csv", fstream::out|fstream::app);
		cout << "Tul, " << Tul.getcoord(0) << ", " << Tul.getcoord(1) << ", " << Tul.getcoord(2) << endl; //вывод в терминал
		cout << "Arc, " << Arc.getcoord(0) << ", " << Arc.getcoord(1) << ", " << Arc.getcoord(2) << endl;
		cout << "Ber, " << Ber.getcoord(0) << ", " << Ber.getcoord(1) << ", " << Ber.getcoord(2) << endl;
		file << "Tul, " << Tul.getcoord(0) << ", " << Tul.getcoord(1) << ", " << Tul.getcoord(2) << " speeds " << Tul.getspeed(0) << ", " << Tul.getspeed(1) << ", " << Tul.getspeed(2) << endl; //запись в файл
		file << "Arc, " << Arc.getcoord(0) << ", " << Arc.getcoord(1) << ", " << Arc.getcoord(2) << " speeds " << Arc.getspeed(0) << ", " << Arc.getspeed(1) << ", " << Arc.getspeed(2) << endl;
		file << "Ber, " << Ber.getcoord(0) << ", " << Ber.getcoord(1) << ", " << Ber.getcoord(2) << " speeds " << Ber.getspeed(0) << ", " << Ber.getspeed(1) << ", " << Ber.getspeed(2) << endl;

		iteration++;
	}
	file.close();
	return 0;
}