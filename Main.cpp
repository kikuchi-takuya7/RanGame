# include <Siv3D.hpp> // OpenSiv3D v0.6.3
//# include "main.h"


Vec2 playerPos = { 100, 480 };//プレイヤーの位置

//オブジェの上に乗ったときに重力などをなくす関数
void Reset(double& _velocity, double& _gravity, int& _jummptmp, int& _jumpcount);

//void collision()

//敵が出てくるパターん
void Pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Vec2 _player, int &_die,
				double _tMove, /*Vec2 _playerPos,*/ Texture _mob, Texture _skymob,
				double &_velocity, double &_gravity, int &_jummptmp, int &_jumpcount);

void Main()
{
	const Texture background{ U"example/sky002_day.jpg" };
	const Texture explosion{ U"example/explosion.png" };
	const Texture mob{ U"example/mob.png" };
	const Texture skymob{ U"example/skymob.png" };
	const Font gameclear{ 80 };
	const String text = U"GAME CLEAR";
	double move = 0.0;//最初
	double move2 = 800.0;//
	double move3 = 1600.0;//障害物が出てくるパターンの場所
	int score = 0;
	const double bottomO = 400.0;//修正がしやすいように障害物のy座標
	const double bottomE = 485.0;//敵のy座標
	const double scaleE = 50;//敵の大きさ
	double start = 0.0;//最初だけの足場
	int die = 0;//死亡時に画面を止める変数
	double tMove = 0.0;//時間を獲得する変数　(Scene::DeltaTime() * 180);
	double limit = 30.0;
	double velocity = 0;//ジャンプの初速
	double gravity = 0;//重力
	int pattern[4] = {0,0,0,0}; //オブジェクトの配置パターン
	int period = 0; //パターンの周期
	int jumpcount = 0;//ジャンプ回数
	int jumptmp = 0;//1ならジャンプの処理が続いて0なら処理しない・時間があれば関数にしたい
	double y = 0;
	double x = 0;

	/*for (int i = 0; i < 2; i++) {
		pattern[i] = rand() % 2;
	}*/

	while (System::Update())
	{
		ClearPrint();

		if (period == 0) {
			tMove = (Scene::DeltaTime() * 180);
		}
		else if (period == 1) {
			tMove = (Scene::DeltaTime() * 240);
		}
		else if (period == 2) {
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
				period += 1;//周期を一回終えて素早さアップしたい
			}
			if (move3 <= -1600) {
				move3 = 800.0;
				
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
			gameclear(text).draw(20, 200);
		}

		//最初の足場
		start -= tMove;
		RectF scaffold{ start, 500, 38000, 10 };
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

		//ジャンプ
		if (KeySpace.down() && jumpcount <= 1 && die == 0) {
			velocity = 8.0f; //ジャンプの初速
			gravity = 2.0f; //重力 
			jumpcount += 1;
			jumptmp = 1;
		}

		if (jumptmp == 1) {
			playerPos.y -= velocity;
			playerPos.y += gravity;
			gravity += 0.1f;
		}

		

		//急降下
		if (KeyDown.down() && velocity != 0) {
			gravity += 20.0f;
		}

		if (playerPos.y >= 480) {
			playerPos.y = 480;
			Reset(velocity, gravity, jumptmp, jumpcount);
		}

		//敵の表示
		Vec2 player3{ player.x, player.y };
		switch (pattern[period])
		{
		case 0:

			Pattern1(move2, move3, bottomO, bottomE, scaleE, player3, die, tMove,
						/*playerPos,*/ mob, skymob, velocity, gravity, jumptmp, jumpcount);
			break;

		case 1:
			break;


		}



		//押し戻されて画面恥に言ったら画面が止まる
		if (playerPos.x <= 20) {
			die += 1;
		}

		//爆発のエフェクト
		/*if (die == 1) { 
			double x = playerPos.x;
			double y = playerPos.y;
		}*/
		if (die >= 1 && die <= 120) {
			explosion.draw(playerPos.x - 400, playerPos.y - 300);
		}
		else if (die >= 120 && die <= 300) {

			explosion.draw(playerPos.x - 400, playerPos.y - 300, ColorF{ 1.0, Periodic::Sine0_1(6s) });
		}

	}
}


void Reset(double& _velocity, double& _gravity, int& _jumptmp, int& _jumpcount) {

	_velocity = 0;
	_gravity = 0;
	_jumptmp = 0;
	_jumpcount = 0;
}


void Pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Vec2 _player,
				int &_die, double _tMove, /*Vec2 _playerPos,*/ Texture _mob, Texture _skymob,
				double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount)
{

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

	Triangle enemy5{ _move3 + 300, _bottomE, _scaleE };
	enemy5.draw(Palette::Red);

	Triangle enemy6{ _move3 + 500, _bottomE, _scaleE };
	enemy6.draw(Palette::Red);

	RectF object{ _move2, _bottomO, 10, 100 };
	object.draw(Palette::Black);

	RectF objectsub{ _move2 + 10, _bottomO, 90, 100 };
	objectsub.draw(Palette::Orange);

	RectF object2{ _move2 + 650, _bottomO, 10, 100 };
	object2.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object2sub{ _move2 + 660, _bottomO, 90, 100 };
	object2sub.draw(Palette::Orange);

	RectF object3{ _move3 + 100, _bottomO - 50, 10, 110 };
	object3.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object3sub{ _move3 + 110, _bottomO - 50, 90, 50 };
	object3sub.draw(Palette::Blue);

	RectF object4{ _move3 + 200, _bottomO - 50, 100, 100 };
	object4.draw(Palette::Black);

	RectF object5{ _move3 + 200, _bottomO - 150, 10, 100 };
	object5.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object5sub{ _move3 + 210, _bottomO - 150, 95 , 100 };
	object5sub.draw(Palette::Black);

	RectF object6{ _move3 + 300, _bottomO - 250, 10, 100 };
	object6.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object6sub{ _move3 + 305, _bottomO - 250, 95, 100 };
	object6sub.draw(Palette::Black);

	RectF object7{ _move3 + 300, _bottomO - 150, 100, 100 };
	object7.draw(Palette::Black);

	RectF object8{ _move3 + 300, _bottomO - 50, 100, 100 };
	object8.draw(Palette::Black);

	RectF object9{ _move3 + 700, _bottomO, 10, 100 };
	object9.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object9sub{ _move3 + 710, _bottomO, 90, 100 };
	object9sub.draw(Palette::Black);

	RectF object10{ _move3 + 110, _bottomO - 40, 290, 100 };
	object10.draw(Palette::White);

	//当たり判定
	//敵に当たったら、画面が止まる
	if (enemyS.intersects(_player)) {
		_die += 1;
	}
	if (enemyS2.intersects(_player)) {
		_die += 1;
	}
	if (enemy3.intersects(_player)) {
		_die += 1;
	}
	if (enemy4.intersects(_player)) {
		_die += 1;
	}
	if (enemy5.intersects(_player)) {
		_die += 1;
	}
	if (enemy6.intersects(_player)) {
		_die += 1;
	}
	//Vec2 objsub2{ _move2 + 660, _bottomO }; 試しにvec2型に座標を入れてから当たり判定を作ったけど変わらず


	/*オブジェクトに当たったら、押し戻される*/
	if (object.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;//交差した瞬間に止まるはずなのに少しめり込んでから止まる
	}
	if (playerPos.y + _gravity >= objectsub.y && playerPos.x <= objectsub.x + 90 && playerPos.x >= objectsub.x) {
		playerPos.y = 380;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
		//一回目だけ上手く行くのもわからない。一回目の処理で何かしらの数字が変わってしまっている?
		/*_jumptmp = 0;
		_velocity = 0;
		_jumpcount = 0;*/
	}
	//if (objectsub.intersects(_player)) {
	//	playerPos.y = 380;
	//	/*_velocity = 0;
	//	_gravity = 0;
	//	_jumptmp = 0;
	//	_jumpcount = 0;*/
	//	Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	//}
	else if (playerPos.x >= objectsub.x + 90){
		_jumptmp = 1;
	}
	if (object2.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	} 
	/*if (object2sub.intersects(_player)) {
		playerPos.y = 380;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}*/
	if (playerPos.y + _gravity >= object2sub.y && playerPos.x <= object2sub.x + 90 && playerPos.x >= object2sub.x) {
		playerPos.y = 380;
		//Reset(_velocity, _gravity, _jumptmp, _jumpcount);
		//_gravity = 0; //重力だけ初期化しなかったらオブジェから離れたら急降下しちゃうけどちゃんと乗りはする。ガチでわけわからん
		//そもそもオブジェクトの当たり判定がおそらくxy20ずつ小さくなってる。何で？多分これが解決すれば全部治る
		_jumptmp = 0;
		_velocity = 0;
		_jumpcount = 0;
	}
	else if (playerPos.x >= object2sub.x + 90) {
		_jumptmp = 1;
	}
	if (object3.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	/*if (object3sub.intersects(_player)) {
		playerPos.y = 330;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}*/
	if (playerPos.y + _gravity >= object3sub.y && playerPos.x <= object3sub.x + 90 && playerPos.x >= object3sub.x
			&& object3sub.y + 50 >= playerPos.y) {
		playerPos.y = 330;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object3sub.x + 90) {
		_jumptmp = 1;
	}
	if (object5.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (object5sub.intersects(_player)) {
		playerPos.y = 230;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object5sub.x + 90) {
		_jumptmp = 1;
	}
	if (object6.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (object6sub.intersects(_player)) {
		playerPos.y = 130;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object6sub.x + 90) {
		_jumptmp = 1;
	}
	if (object9.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (object9sub.intersects(_player)) {
		playerPos.y = 380;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object9sub.x + 90) {
		_jumptmp = 1;
	}
	if (object10.intersects(_player)) {
			playerPos.y = 480;
			Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
}
