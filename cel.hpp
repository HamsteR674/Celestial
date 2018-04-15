#ifndef cel_h
#define cel_h

using namespace std;
class cel{
private:
	double speed[3]; // x, y, z
	double coord[3]; // x, y, z
	int mass;
	string name;
public:
	cel(string name);
	double getspeed(int i);
	double getcoord(int i);
	int  getmass();
	void setspeed(double speed_buf, int i);
	void setcoord(double coord_buf, int i);
	void setmass(int mass_buf);
	void eval(double FTA, double FBT, int j, double t);
};

#endif