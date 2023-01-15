# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "Box.h"


int bottom = 400;//修正がしやすいように敵のy座標


void Main()
{
	const Texture background{ U"example/sky002_day.jpg" };
	const Texture explosion{ U"example/explosion.png" };
	double move = 0.0;//最初
	double move2 = 800.0;//
	double moveP = 1600.0;//障害物が出てくるパターンの場所
	Vec2 playerPos = { 100, 480 };//プレイヤーの位置
	double start = 0.0;//最初だけの足場
	int die = 0;//死亡時に画面を止める変数
	double tMove = 0.0;//時間を獲得する変数　(Scene::DeltaTime() * 180);
	double time = 30.0;

	while (System::Update())
	{
		ClearPrint();

		tMove = (Scene::DeltaTime() * 180);

		//背景を移動する
		if (die == 0) {
			move -= tMove;
			move2 -= tMove;
			if (move <= -800) {
				move = 795.0;
			}
			if (move2 <= -800) {
				move2 = 795.0;
			}
		}
		background.draw(move, 0);
		background.draw(move2, 0);

		//時間計測
		if (die == 0 && time >= 0) {
			time = 30 - Scene::Time();
			Print << time;
		}
		else {
			Print << time;
		}

		//30秒経過したらクリア
		if (time <= 0) {

		}

		//最初の足場
		start -= tMove;
		RectF scaffold{ move, 500, 800, 10 };
		scaffold.draw(Palette::Black);

		//画面恥の表示
		RectF edge{ 0, 0, 5, 800 };
		edge.draw(Palette::Red);

		//プレイヤーの表示
		Circle player{ playerPos.x, playerPos.y, 20 };
		if (die == 0) {
			player.draw(Palette::Black);
		}

		//敵の表示
		RectF object{ move2, bottom, 100, 100 };
		object.draw(Palette::Black);

		Circle enemy{ move2 + 400, bottom + 50, 50 };
		enemy.draw(Palette::Black);

		//当たり判定
		//敵に当たったら、画面が止まる
		if (enemy.intersects(player)) {
			die = 1;
		}

		//オブジェクトに当たったら、押し戻される
		if (object.intersects(player)) {
			playerPos.x = playerPos.x - tMove;
		}

		//押し戻されて画面恥に言ったら画面が止まる
		if (playerPos.x <= 20) {
			die += 1;
		}

		//爆発のエフェクト
		if (die >= 1 && die <= 120) {
			explosion.draw(player.x - 400, player.y - 300);
		}
		else if (die >= 120 && die <= 300) {
			explosion.draw(player.x - 400, player.y - 300, ColorF{ 1.0, Periodic::Sine0_1(5s) });
		}
	}
}
