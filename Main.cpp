
# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "Box.h"
# include "main.h"


Vec2 playerPos = { 100, 480 };//プレイヤーの位置

void pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Vec2 _player, int _die,
				double _tMove, /*Vec2 _playerPos,*/ Texture _mob, Texture _skymob);

void Main()
{
	const Texture background{ U"example/sky002_day.jpg" };
	const Texture explosion{ U"example/explosion.png" };
	const Texture mob{ U"example/mob.png" };
	const Texture skymob{ U"example/skymob.png" };
	const Font gameclear{ 80 };
	double move = 0.0;//最初
	double move2 = 800.0;//
	double move3 = 1600.0;//障害物が出てくるパターンの場所
	int score = 0;
	double bottomO = 400.0;//修正がしやすいように障害物のy座標
	double bottomE = 485.0;//敵のy座標
	double scaleE = 50;//敵の大きさ
	double start = 0.0;//最初だけの足場
	int die = 0;//死亡時に画面を止める変数
	double tMove = 0.0;//時間を獲得する変数　(Scene::DeltaTime() * 180);
	double limit = 30.0;
	double velocity = 0;//ジャンプの初速
	double gravity = 0;//重力
	int pattern[2]; //オブジェクトの配置パターン
	int period = 0; //パターンの周期
	int jumpcount = 0;//ジャンプ回数
	//int jumptmp = 0;//空中ではジャンプが一回しか出ないように


	for (int i = 0; i < 2; i++) {
		pattern[i] = rand() % 2;
	}

	while (System::Update())
	{
		ClearPrint();

		if (period == 0) {
			tMove = (Scene::DeltaTime() * 180);
		}
		else if (period == 1) {
			tMove = (Scene::DeltaTime() * 300);
		}

		
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
				period += 1;//周期を一回終えて素早さアップしたい
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
		else if (die != 0) {
			Print << limit;
		}

		//30秒経過したらクリア
		if (limit <= 0) {

		}

		//最初の足場
		start -= tMove;
		RectF scaffold{ start, 500, 1600, 10 };
		scaffold.draw(Palette::Black);

		//画面恥の表示
		RectF edge{ 0, 0, 5, 800 };
		edge.draw(Palette::Red);

		//プレイヤーの表示
		Circle player{ playerPos.x, playerPos.y, 20 };
		if (die == 0) {
			player.draw(Palette::Black);
		}

		//スコアの表示
		if (die == 0 && limit >= 0) {
			score += tMove;
		}
		
		Print << score;

		//空中ジャンプは一回


		//ジャンプ
		if (KeySpace.down() && jumpcount <= 1) {
			velocity = 8.0f; //ジャンプの初速
			gravity = 2.0f; //重力
			jumpcount += 1;
		}

		playerPos.y -= velocity;
		playerPos.y += gravity;
		gravity += 0.1f;

		//急降下
		if (KeyDown.down() && velocity != 0) {
			gravity += 30.0f;
		}

		if (playerPos.y >= 480) {
				playerPos.y = 480;
				velocity = 0;
				jumpcount = 0;
		}

		//敵の表示
		Vec2 player3{ player.x, player.y };
		switch (pattern[period])
		{
		case 1:

			pattern1(move2, move3, bottomO, bottomE, scaleE, player3, die, tMove, /*playerPos,*/ mob, skymob);

			break;
		}



		//押し戻されて画面恥に言ったら画面が止まる
		if (playerPos.x <= 20) {
			die += 1;
		}

		//爆発のエフェクト
		if (die >= 1 && die <= 120) {
			explosion.draw(playerPos.x - 400, playerPos.y - 300);
		}
		else if (die >= 120 && die <= 300) {

			explosion.draw(playerPos.x - 400, playerPos.y - 300, ColorF{ 1.0, Periodic::Sine0_1(5s) });
		}

	}
}


void pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Vec2 _player,
				int _die, double _tMove, /*Vec2 _playerPos,*/ Texture _mob, Texture _skymob)
{

	RectF object{ _move2, _bottomO, 100, 100 };
	object.draw(Palette::Black);

	Triangle enemyS{ _move2 + 300, _bottomE - 300, _scaleE };
	enemyS.draw(Palette::Red);
	_skymob.scaled(0.2).drawAt(_move2 + 300, _bottomE - 300);

	Triangle enemyS2{ _move2 + 300, _bottomE - 200, _scaleE };
	enemyS2.draw(Palette::Red);

	Triangle enemy3{ _move2 + 500, _bottomE, _scaleE };
	enemy3.draw(Palette::Red);
	_mob.scaled(0.3).drawAt(_move2 + 500, _bottomE);

	Triangle enemy4{ _move2 + 600, _bottomE, _scaleE };
	enemy4.draw(Palette::Red);

	RectF object2{ _move2 + 650, _bottomO, 100, 100 };
	object2.draw(Palette::Black);

	RectF object3{ _move3 + 100, _bottomO - 50, 100, 100 };
	object3.draw(Palette::Black);

	RectF object4{ _move3 + 200, _bottomO - 50, 100, 100 };
	object4.draw(Palette::Black);

	RectF object5{ _move3 + 200, _bottomO - 150, 100, 100 };
	object5.draw(Palette::Black);

	RectF object6{ _move3 + 300, _bottomO - 250, 100, 100 };
	object6.draw(Palette::Black);

	RectF object7{ _move3 + 300, _bottomO - 150, 100, 100 };
	object7.draw(Palette::Black);

	RectF object8{ _move3 + 300, _bottomO - 50, 100, 100 };
	object8.draw(Palette::Black);

	Triangle enemy5{ _move3 + 300, _bottomE, _scaleE };
	enemy5.draw(Palette::Red);

	Triangle enemy6{ _move3 + 500, _bottomE, _scaleE };
	enemy6.draw(Palette::Red);

	RectF object9{ _move3 + 700, _bottomO, 100, 100 };
	object9.draw(Palette::Black);

	//当たり判定
			//敵に当たったら、画面が止まる
	if (enemyS.intersects(_player)) {
		_die += 1;
	}

	//オブジェクトに当たったら、押し戻される
	if (object.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
}
