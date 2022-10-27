// ZUMA PROJECT //
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

const float COLLIDE_DISTANCE = 1;
const float ROAD_SPEED = 1;
const float RADIUS = 0.5;
const float dt = 1;

enum Colour {
	red=0, green, blue, yellow
};

class Ball {
public:
	Ball(const float x, const float y, Colour col) : x{ x }, y{ y }, colour{ col } {};

	float get_x() const { return this->x; };
	float get_y() const { return this->y; };

	void set_position(const float x, const float y) {
		this->x = x;
		this->y = y;
	};

	float *get_position() const {
		return { this->x, this->y };
	};

	virtual void move(const Path &path) {
		if (this->push) {
			this->pos += speed * dt;
			{x, y} = path.return_xy(this->pos);
		}
	};

private:
	float x, y, pos;
	float speed = 0.1;
	bool last;
	bool push;
	Colour colour;
};

class FlyingBall {
public:
	FlyingBall(const float x, const float y, const float vx, const float vy, Colour colour) : x{ x }, y{ y }, vx{ vx }, vy{ vy }, colour {colour} {};
	~FlyingBall() = default;

	void move () {
		this->x += this->vx * dt;
		this->y += this->vy * dt;
	};

	bool collide(FlyingBall &FB1, FlyingBall &FB2) const {
		float dx = FB1.x - FB2.x;
		float dy = FB1.y - FB2.y;
		return bool(dx * dx + dy * dy < COLLIDE_DISTANCE* COLLIDE_DISTANCE);
	};

private:
	float x, y;
	float vx, vy;
	Colour colour;
};

class Frog {
public:
	Frog(const float x, const float y) : pos_x{ x }, pos_y{ y }, angle{ 0 }, shoot_speed{ 10 },  {};

	~Frog() = default;

	void set_angle (const Cursor &cursor) {
		this->angle = this->get_angle(cursor);
	};

	float get_angle (const Cursor &cursor) {
		float angle;
		float cursor_pos[2] = cursor.return_pos();
		angle = atan2((cursor_pos[0] - this->y) / (cursor_pos[1] - this->x));
		return angle;
	};

	void shoot() {
		float vx = this->shoot_speed * cos(this->angle);
		float vy = this->shoot_speed * sin(this->angle);
		FlyingBall *ball = new FlyingBall(this->x, this->y, vx, vy, this->current_colour);
	};

	void generate_next_colour() {
		this->current_colour = this->next_colour;
		this->next_colour = Colour(rand() % 4);
	}
private: 
	float x, y, angle;
	float shoot_speed;
	Colour current_colour, next_colour;
};

class Road {
public:
	void process_new_ball() {

	}
private:
	std::vector<Ball> balls = {};
	Path path;
};

class Path {
public:
	float* return_xy(float pos) const{

	}
};

class End_Hole {
public:
	End_Hole(float x, float y, float ang) : pos_x{ x }, pos_y{ y }, angle{ ang } {};

	float *position() {
		return { this->pos_x, this->pos_y };
	}
private:
	float pos_x, pos_y, angle;
};

class Cursor {
public:

	float* return_pos() const {
		float pos[2] = { this->x, this->y };
		return pos;
	}

	void set_pos() {
		//gatting position from special library and setting x,y
	};

private:
	float x, y;
};

class Event {
public:
	void process_mouse_click(Frog &frog) {
		frog.shoot();
	}

};

class Info {
public:

private:
	float Frof_x, Frog_y;
	float* road_points;

};

class Level {
public:
	Level (Info &info) 

	void process_Event(const Event event) {

	};
private: 
	bool state;
};

class Game {

};

void main(){
	Info gamefield = 
	Level *level = new Level(gamefield);

}
/*ѕлан по вычислению положени€ точки на кривой по длине пройденного пути (вариант с затратами по пам€ти):
ќбработка пути:
1. «адаем кривую массивом опорных точек, получаем аналитическую функцию кривой от параметра t
2. ѕроходимс€ по кривой с достаточно малым шагом по t, вычисл€€ длину пройденного пути. 
3. „ерез равные, достачно малые промежутки, записываем новые опорные точки и их отсто€ние от начала пути в массив размером N.
4. «аписываем полную длину пути L.
ѕолучение:
5. ѕолуча€ пройденный путь s, определ€ем приблизительный индекс в массиве как int( N*s/L )
6. —равнени€ми обнаруживаем два элемента, между которыми лежит точка: (r1, s1) и (r2, s2).
7. ”точн€ем положение как r = r1 + (r2-r1) * (s-s1) / (s2-s1). —тоит заметить, что s2-s1 = const дл€ всего массива. */