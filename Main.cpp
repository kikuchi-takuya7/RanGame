# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "Box.h"

double JumpY(double velocity,double sec);

double bottomO = 400.0;//修正がしやすいように障害物のy座標
double bottomE = 485.0;//敵のy座標
double scaleE = 50;//敵の大きさ

void Main()
{
	const Texture background{ U"example/sky002_day.jpg" };
	const Texture explosion{ U"example/explosion.png" };
	const Texture mob{ U"example/mob.png" };
	const Texture skymob{ U"example/skymob.png" };
	double move = 0.0;//最初
	double move2 = 800.0;//
	double move3 = 1600.0;//障害物が出てくるパターンの場所
	Vec2 playerPos = { 100, 480 };//プレイヤーの位置
	double start = 0.0;//最初だけの足場
	int die = 0;//死亡時に画面を止める変数
	double tMove = 0.0;//時間を獲得する変数　(Scene::DeltaTime() * 180);
	double limit = 30.0;
	const double velocity = -10.0f;//ジャンプの初速
	double angle = ToRadians(30);
	double jumpS = velocity * sin(angle);
	double time = 0.0;
	int pattern[2]; //オブジェクトの配置パターン
	int period = 0; //パターンの周期

	for (int i = 0; i < 2; i++) {
		pattern[i] = rand() % 2;
	}

	while (System::Update())
	{
		ClearPrint();

		tMove = (Scene::DeltaTime() * 180);

		//背景を移動する
		if (die == 0) {
			move -= tMove;
			move2 -= tMove;
			move3 -= tMove;
			if (move <= -1600) {
				move = 800.0;
			}
			if (move2 <= -1600) {
				move2 = 800.0;
			}
			if (move3 <= -1600) {
				move3 = 800.0;
				period += 1;
			}
		}
		background.draw(move, 0);
		background.draw(move2, 0);
		background.draw(move3, 0);

		//時間計測
		if (die == 0 && limit >= 0) {
			limit = 30 - Scene::Time();
			Print << limit;
		}
		else if(die != 0) {
			Print << limit;
		}

		//30秒経過したらクリア
		if (limit <= 0) {

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


		//ジャンプ
		if (KeySpace.down()) {
			time += Scene::DeltaTime();
			playerPos.y = playerPos.y + JumpY(velocity, time) * 4;
		}

		//敵の表示

		switch (pattern[period])
		{
		case 1:

			RectF object{ move2, bottomO, 100, 100 };
			object.draw(Palette::Black);

			Triangle enemyS{ move2 + 300, bottomE - 300, scaleE };
			enemyS.draw(Palette::Red);
			skymob.scaled(0.2).drawAt(move2 + 300, bottomE - 300);
			
			Triangle enemyS2{ move2 + 300, bottomE - 200, scaleE };
			enemyS2.draw(Palette::Red);

			Triangle enemy3{ move2 + 500, bottomE, scaleE };
			enemy3.draw(Palette::Red);
			mob.scaled(0.3).drawAt(move2 + 500, bottomE);

			Triangle enemy4{ move2 + 600, bottomE, scaleE };
			enemy4.draw(Palette::Red);

			RectF object2{ move2 + 650, bottomO, 100, 100 };
			object2.draw(Palette::Black);

			RectF object3{ move3 + 100, bottomO - 50, 100, 100 };
			object3.draw(Palette::Black);

			RectF object4{ move3 + 200, bottomO - 50, 100, 100 };
			object4.draw(Palette::Black);

			RectF object5{ move3 + 200, bottomO - 150, 100, 100 };
			object5.draw(Palette::Black);

			RectF object6{ move3 + 300, bottomO - 250, 100, 100 };
			object6.draw(Palette::Black);

			RectF object7{ move3 + 300, bottomO - 150, 100, 100 };
			object7.draw(Palette::Black);

			RectF object8{ move3 + 300, bottomO - 50, 100, 100 };
			object8.draw(Palette::Black);

			Triangle enemy5{ move3 + 300, bottomE, scaleE };
			enemy5.draw(Palette::Red);

			Triangle enemy6{ move3 + 500, bottomE, scaleE };
			enemy6.draw(Palette::Red);

			RectF object9{ move3 + 700, bottomO, 100, 100 };
			object9.draw(Palette::Black);


			//当たり判定
			//敵に当たったら、画面が止まる
			if (enemyS.intersects(player)) {
				die += 1;
			}

			//オブジェクトに当たったら、押し戻される
			if (object.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}

			break;
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



double JumpY(double velocity, double sec) {

	double gravity = 9.8f * 2;

	return velocity * sec + 0.5f * gravity * Square(sec);
}
