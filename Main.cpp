# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "Box.h"

void Pattern1(Circle _player, double _move);



void Main()
{
	Stopwatch timer{ StartImmediately::Yes };

	const Texture background{ U"example/sky002_day.jpg" };
	//const Texture background2{ U"example/sky002_day.jpg" };
	double move = 0.0;
	double move2 = 800.0;
	double moveP = 1600.0;
	Vec2 playerPos = { 100, 500 };
	double start = 0.0;

	while (System::Update())
	{
		ClearPrint();

		//背景を移動する
		move -= (Scene::DeltaTime() * 180);
		move2 -= (Scene::DeltaTime() * 180);
		if (move <= -800) {
			move = 795.0;
		}
		if (move2 <= -800) {
			move2 = 795.0;
		}
		background.draw(move, 0);
		background.draw(move2, 0);

		//時間計測
		const String time = timer.format();
		Print << time;

		//最初の足場
		start -= (Scene::DeltaTime() * 180);
		RectF{ start, 520, 800, 10 }.draw(Palette::Black);

		//プレイヤーの表示
		Circle player{ playerPos.x, playerPos.y, 20 };
		player.draw(Palette::Black);

		void Pattarn1(Circle player, double move);

		
	}
}

void Pattarn1(Circle _player, double _move) {

	RectF object{ _move, 400, 100, 100 };
	object.draw(Palette::Black);

	RectF object2{ _move, 400, 100, 100 };
	object2.draw(Palette::Black);

	Circle enemy{ _move, 500, 50};
	enemy.draw(Palette::Black);

	//当たり判定
	RectF scaffold{ _move, 520, 800, 10 };
	scaffold.draw(Palette::Black);
	if (object.intersects(_player)) {
	}

}
