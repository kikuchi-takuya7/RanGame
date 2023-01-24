# include <Siv3D.hpp> // OpenSiv3D v0.6.3

#define NUM 3

Vec2 playerPos = { 200, 480 };//プレイヤーの位置

void Main();

void InitAll(double &_move, double &_move2, double &_move3, int &_score, int &_die, double &_tMove, double &_limit,
				double &_velocity, double &_gravity, int _pattern[], int _NUM, int &_period, int &_jumpcount, int &_jumptmp);

//ほぼすべての処理
void UpdateAll(int &_period,double &_tMove,double &_move, double &_move2, double &_move3, double &_limit, int &_score,
				int &_die, double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount, Font _speadup, String _Up, int &_speadtmp);

//背景の表示を一番後ろに
void DrawBack(Texture _background, double _move, double _move2, double _move3);

//ほとんどすべての表示
void DrawAll(double _move, double _move2, double _move3, int _die, double _limit, Font gameclear, String text, Font gameover, String text2,
				RectF _scaffold, RectF _edge, Circle _player, Texture _explosion);

//オブジェの上に乗ったときに重力などをなくす関数
void Reset(double& _velocity, double& _gravity, int& _jummptmp, int& _jumpcount);

//地面にくっついてる100×100オブジェクトの当たり判定
void CollisionO(double _tMove, double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount,
				Circle _player, RectF _object, RectF objectsub);

//敵の当たり判定
void CollisionE(int &_die, Circle _player, Triangle _enemy);

//敵が出てくるパターん
void Pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Circle _player, int &_die,
				double _tMove, Texture _mob, Texture _skymob, double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount);

void Pattern2(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Circle _player, int& _die,
				double _tMove, Texture _mob, Texture _skymob, double& _velocity, double& _gravity, int& _jumptmp, int& _jumpcount);

void Pattern2Draw(Texture _skymob, double _move2, double _move3, double _bottomE, RectF _object, RectF _objectsub, RectF _object2,
					RectF _object2sub, RectF _object3, RectF _object3sub, RectF _object9, RectF _object9sub);

void Main()
{
	const Texture background{ U"example/sky002_day.jpg" };
	const Texture explosion{ U"example/explosion.png" };
	const Texture mob{ U"example/mob.png" };
	const Texture skymob{ U"example/skymob.png" };
	const Font gameclear{ 80 };
	const Font gameover { 80 };
	const Font speadUp { 80 };
	const String text = U"GAME CLEAR";
	const String text2 = U"GAME OVER";
	const String Up = U"SPEAD UP!";
	//最初の足場
	RectF scaffold{ 0, 500, 800, 10 };
	//画面恥の表示
	RectF edge{ 0, 0, 5, 800 };
	double move;//最初
	double move2;//
	double move3;//障害物が出てくるパターンの場所
	int score;
	const double bottomO = 400.0;//修正がしやすいように障害物のy座標
	const double bottomE = 480.0;//敵のy座標
	const double scaleE = 50;//敵の大きさ
	int die;//死亡時に画面を止める変数
	double tMove;//時間を獲得する変数　(Scene::DeltaTime() * 180);
	double limit;
	double velocity;//ジャンプの初速
	double gravity;//重力
	int pattern[NUM]; //オブジェクトの配置パターン
	int period;//パターンの周期
	int jumpcount;//ジャンプ回数
	int jumptmp;//1ならジャンプの処理が続いて0なら処理しない・時間があれば関数にしたい
	int speadtmp = 0;//スピードアップを表示させるためのやつ
	
	InitAll(move, move2, move3, score, die, tMove,limit, velocity, gravity, pattern, NUM, period, jumpcount, jumptmp);

	while (System::Update())
	{
		ClearPrint();

		DrawBack(background, move, move2, move3);

		UpdateAll(period, tMove, move, move2, move3, limit, score, die, velocity, gravity, jumptmp, jumpcount, speadUp, Up, speadtmp);

		//プレイヤーの表示
		Circle player{ playerPos.x, playerPos.y, 20 };

		//敵の表示
		//Vec2 player3{ player.x, player.y };  ←こいつのせいだった。確かにこれだと座標の真ん中にしか判定が出来なくなる。スッキリ
		switch (pattern[period])
		{
		case 0:

			if (limit >= 0) {
				Pattern1(move2, move3, bottomO, bottomE, scaleE, player, die, tMove,
						 mob, skymob, velocity, gravity, jumptmp, jumpcount);
			}

			break;

		case 1:

			if (limit >= 0) {
				Pattern2(move2, move3, bottomO, bottomE, scaleE, player, die, tMove,
						 mob, skymob, velocity, gravity, jumptmp, jumpcount);
			}

			break;
		}
		
		DrawAll(move, move2, move3, die, limit, gameclear, text, gameover, text2, scaffold, edge, player, explosion);

	}
}

void InitAll(double &_move, double &_move2, double &_move3, int &_score, int &_die, double &_tMove, double &_limit,
				double &_velocity, double &_gravity, int _pattern[], int _NUM, int &_period, int &_jumpcount, int &_jumptmp){

	_move = 0.0;
	_move2 = 800.0;
	_move3 = 1600.0;
	_score = 0;
	_die = 0;
	_tMove = 0.0;
	_limit = 30.0;
	_velocity = 0;
	_gravity = 0;
	_pattern[NUM];
	_period = 0;
	_jumpcount = 0;
	_jumptmp = 0;

	//ランダムなパターンを選出
	for (int i = 0; i < NUM; i++) {
		_pattern[i] = rand() % 2;
	}
}

void UpdateAll(int &_period, double &_tMove,double &_move, double &_move2, double &_move3,double &_limit, int &_score,/*, double _bottomO, double _bottomE, double _scaleE, Vec2 _player*/
				int &_die, double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount, Font _speadup, String _Up, int &_speadtmp){

	if (_period == 0) {
		_tMove = (Scene::DeltaTime() * 180);
	}
	else if (_period == 1) {
		_tMove = (Scene::DeltaTime() * 240);
	}
	else if (_period == 2) {
		_tMove = (Scene::DeltaTime() * 300);
	}


	//背景を移動する
	if (_die == 0 && _limit >= 0) {
		_move -= _tMove;
		_move2 -= _tMove;
		_move3 -= _tMove;
		if (_move <= -1600) {
			_move = 800.0;
			_speadtmp = 1;
		}
		if (_move2 <= -1600) {
			_move2 = 800.0;
			_period += 1;//周期を一回終えて素早さアップ
			
		}
		if (_move3 <= -1600) {
			_move3 = 800.0;

		}
	}


	if (_limit >= 5 && _die == 0) {
		if (_speadtmp == 1) {
			_speadup(_Up).draw(_move, 200);
		}
	}


	//時間計測
	if (_die == 0 && _limit >= 0) {
		_limit = 30 - Scene::Time();
		Print << U"Time:" << _limit;
	}
	else if (_die != 0) {
		Print << U"Time:" << _limit;
	}

	//スコアの増加と表示
	if (_die == 0 && _limit >= 0) {
		_score += _tMove;
		_score += playerPos.x;//高得点を目指せるようにプレイヤーの位置分の得点を加算するようにした
	}

	Print << U"score:" << _score;
	

	//ジャンプ
	if (KeySpace.down() && _jumpcount <= 1 && _die == 0) {
		_velocity = 8.0f; //ジャンプの初速
		_gravity = 2.0f; //重力 
		_jumpcount += 1;
		_jumptmp = 1;
	}

	if (_jumptmp == 1) {
		playerPos.y -= _velocity;
		playerPos.y += _gravity;
		_gravity += 0.1f;
	}



	//急降下
	if (KeyDown.down() && _velocity != 0) {
		_gravity = 30.0f;
	}

	if (playerPos.y >= 480) {
		playerPos.y = 480;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}

	//押し戻されて画面恥に言ったら画面が止まる
	if (playerPos.x <= 20) {
		_die += 1;
	}
}

void DrawBack(Texture _background, double _move, double _move2, double _move3){

	//背景の表示
	_background.draw(_move, 0);
	_background.draw(_move2, 0);
	_background.draw(_move3, 0);

}

void DrawAll(double _move, double _move2, double _move3, int _die, double _limit, Font gameclear, String text, Font gameover ,String text2,
				RectF _scaffold, RectF _edge, Circle _player, Texture _explosion){

	//30秒経過したらクリア
	if (_limit <= 0) {
		gameclear(text).draw(20, 200);
	}

	_scaffold.draw(Palette::Black);

	_edge.draw(Palette::Red);

	if (_die == 0) {
		_player.draw(Palette::Black);
	}

	//爆発のエフェクト
	if (_die >= 1 && _die <= 120) {
		_explosion.draw(playerPos.x - 400, playerPos.y - 300);
	}
	else if (_die >= 120 && _die <= 300) {

		_explosion.draw(playerPos.x - 400, playerPos.y - 300, ColorF{ 1.0, Periodic::Sine0_1(6s) });
	}
	//ゲームオーバー表示
	if (_die > 1)
	{
		gameover(text2).draw(20, 200);
	}
}


void Reset(double& _velocity, double& _gravity, int& _jumptmp, int& _jumpcount) {

	_velocity = 0;
	_gravity = 0;
	_jumptmp = 0;
	_jumpcount = 0;
}

void CollisionO(double _tMove, double& _velocity, double& _gravity, int& _jumptmp, int& _jumpcount,
				Circle _player, RectF _object, RectF _objectsub){

	/*オブジェクトに当たったら、押し戻される*/
	if (_object.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (_player.y + _gravity + 20 >= _objectsub.y && _player.x <= _objectsub.x + 90 && _player.x >= _objectsub.x) {
		playerPos.y = 380;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (_player.x >= _objectsub.x + 90) {
		_jumptmp = 1;
	}
}

void CollisionE(int &_die, Circle _player, Triangle _enemy){

	if (_enemy.intersects(_player)) {
		_die += 1;
	}
}


void Pattern1(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Circle _player,
				int &_die, double _tMove, Texture _mob, Texture _skymob,
				double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount)
{

	Triangle enemyS{ _move2 + 300, _bottomE - 300, _scaleE };
	_skymob.scaled(0.2).drawAt(_move2 + 300, _bottomE - 300);

	Triangle enemyS2{ _move2 + 300, _bottomE - 200, _scaleE };
	_skymob.scaled(0.2).drawAt(_move2 + 300, _bottomE - 200);

	Triangle enemy3{ _move2 + 500, _bottomE, _scaleE };
	_mob.scaled(0.3).drawAt(_move2 + 500, _bottomE);

	Triangle enemy4{ _move2 + 600, _bottomE, _scaleE };
	_mob.scaled(0.3).drawAt(_move2 + 600, _bottomE);

	Triangle enemy5{ _move3 + 300, _bottomE, _scaleE };
	_mob.scaled(0.3).drawAt(_move3 + 300, _bottomE);

	Triangle enemy6{ _move3 + 500, _bottomE, _scaleE };
	_mob.scaled(0.3).drawAt(_move3 + 500 , _bottomE);

	RectF object{ _move2, _bottomO, 1, 100 };
	object.draw(Palette::Black);

	RectF objectsub{ _move2 + 1, _bottomO, 99, 100 };
	objectsub.draw(Palette::Black);

	RectF object2{ _move2 + 650, _bottomO, 1, 100 };
	object2.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object2sub{ _move2 + 651, _bottomO, 99, 100 };
	object2sub.draw(Palette::Black);

	RectF object3{ _move3 + 100, _bottomO - 55, 1, 110 };
	object3.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object3sub{ _move3 + 101, _bottomO - 55, 99, 110 };
	object3sub.draw(Palette::Black);

	RectF object4{ _move3 + 200, _bottomO - 55, 100, 100 };
	object4.draw(Palette::Black);

	RectF object5{ _move3 + 200, _bottomO - 155, 1, 100 };
	object5.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object5sub{ _move3 + 201, _bottomO - 155, 99 , 100 };
	object5sub.draw(Palette::Black);

	RectF object6{ _move3 + 300, _bottomO - 255, 1, 100 };
	object6.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object6sub{ _move3 + 301, _bottomO - 255, 99, 100 };
	object6sub.draw(Palette::Black);

	RectF object7{ _move3 + 300, _bottomO - 155, 100, 100 };
	object7.draw(Palette::Black);

	RectF object8{ _move3 + 300, _bottomO - 55, 100, 100 };
	object8.draw(Palette::Black);

	RectF object9{ _move3 + 700, _bottomO, 1, 100 };
	object9.draw(Palette::Black);

	//上の壁のオブジェクト
	RectF object9sub{ _move3 + 701, _bottomO, 99, 100 };
	object9sub.draw(Palette::Black);

	RectF object10{ _move3 + 110, _bottomO - 45, 290, 100 };
	object10.draw(Palette::Black);

	//当たり判定
	//敵に当たったら、画面が止まる
	CollisionE(_die, _player, enemyS);
	CollisionE(_die, _player, enemyS2);
	CollisionE(_die, _player, enemy3);
	CollisionE(_die, _player, enemy4);
	CollisionE(_die, _player, enemy5);
	CollisionE(_die, _player, enemy6);

	/*オブジェクトに当たったら、押し戻される*/
	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object, objectsub);
	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object2, object2sub);

	if (object3.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (playerPos.y + _gravity + 20 >= object3sub.y && playerPos.x <= object3sub.x + 90 && playerPos.x >= object3sub.x
			&& object3sub.y + 45 >= playerPos.y) {
		playerPos.y = 325;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object3sub.x + 90) {
		_jumptmp = 1;
	}

	if (object5.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (playerPos.y + _gravity + 20 >= object5sub.y && playerPos.x <= object5sub.x + 90 && playerPos.x >= object5sub.x
			&& object5sub.y + 45 >= playerPos.y) {
		playerPos.y = 225;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object5sub.x + 90) {
		_jumptmp = 1;
	}

	if (object6.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (playerPos.y + _gravity + 20 >= object6sub.y && playerPos.x <= object6sub.x + 90 && playerPos.x >= object6sub.x
			&& object6sub.y + 45 >= playerPos.y) {
		playerPos.y = 125;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object6sub.x + 90) {
		_jumptmp = 1;
	}

	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object9, object9sub);

	if (object10.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (object10.intersects(_player)) {
		playerPos.y = playerPos.y + _tMove;
			Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
}

void Pattern2(double _move2, double _move3, double _bottomO, double _bottomE, double _scaleE, Circle _player,int &_die, double _tMove,
				Texture _mob, Texture _skymob, double &_velocity, double &_gravity, int &_jumptmp, int &_jumpcount){

	Triangle enemyS{ _move2 + 300, _bottomE - 300, _scaleE };
	Triangle enemyS2{ _move3 + 750, _bottomE - 200, _scaleE };
	Triangle enemy3{ _move2 + 500, _bottomE - 150, _scaleE };
	Triangle enemy4{ _move2 + 600, _bottomE - 100, _scaleE };
	Triangle enemy5{ _move3 + 300, _bottomE - 200, _scaleE };
	Triangle enemy6{ _move3 + 500, _bottomE - 100, _scaleE };
	Triangle enemy7{ _move3 + 750, _bottomE - 400, _scaleE };	
	RectF object{ _move2, _bottomO, 1, 100 };
	RectF objectsub{ _move2 + 1, _bottomO, 99, 100 };
	RectF object2{ _move2 + 400, _bottomO, 1, 100 };
	//上の壁のオブジェクト
	RectF object2sub{ _move2 + 401, _bottomO, 99, 100 };
	RectF object3{ _move3 + 100, _bottomO, 3, 100 };
	//上の壁のオブジェクト
	RectF object3sub{ _move3 + 101, _bottomO, 299, 100 };
	RectF object9{ _move3 + 700, _bottomO, 1, 100 };
	//上の壁のオブジェクト
	RectF object9sub{ _move3 + 701, _bottomO, 99, 100 };

	Pattern2Draw(_skymob, _move2, _move3, _bottomE, object, objectsub, object2, object2sub, object3, object3sub, object9, object9sub);

	//当たり判定
	//敵に当たったら、画面が止まる
	CollisionE(_die, _player, enemyS);
	CollisionE(_die, _player, enemyS2);
	CollisionE(_die, _player, enemy3);
	CollisionE(_die, _player, enemy4);
	CollisionE(_die, _player, enemy5);
	CollisionE(_die, _player, enemy6);
	CollisionE(_die, _player, enemy7);

	/*オブジェクトに当たったら、押し戻される*/
	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object, objectsub);
	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object2, object2sub);
	CollisionO(_tMove, _velocity, _gravity, _jumptmp, _jumpcount, _player, object9, object9sub);

	//obj3だけ長いから別処理
	if (object3.intersects(_player)) {
		playerPos.x = playerPos.x - _tMove;
	}
	if (playerPos.y + _gravity + 20 >= object3sub.y && playerPos.x <= object3sub.x + 290 && playerPos.x >= object3sub.x
			&& object3sub.y + 45 >= playerPos.y) {
		playerPos.y = 380;
		Reset(_velocity, _gravity, _jumptmp, _jumpcount);
	}
	else if (playerPos.x >= object3sub.x + 90) {
		_jumptmp = 1;
	}

}

void Pattern2Draw(Texture _skymob, double _move2, double _move3, double _bottomE, RectF _object, RectF _objectsub, RectF _object2, RectF _object2sub, RectF _object3, RectF _object3sub, RectF _object9, RectF _object9sub){

	_skymob.scaled(0.2).drawAt(_move2 + 300, _bottomE - 300);//enemyS
	_skymob.scaled(0.2).drawAt(_move3 + 750, _bottomE - 200);//enemyS2
	_skymob.scaled(0.2).drawAt(_move2 + 500, _bottomE - 150);//enemy3
	_skymob.scaled(0.2).drawAt(_move2 + 600, _bottomE - 100);//enemy4
	_skymob.scaled(0.2).drawAt(_move3 + 300, _bottomE - 200);//enemy5
	_skymob.scaled(0.2).drawAt(_move3 + 500, _bottomE - 100);//enemy6
	_skymob.scaled(0.2).drawAt(_move3 + 750, _bottomE - 400);//enemy7
	_object.draw(Palette::Black);
	_objectsub.draw(Palette::Black);
	_object2.draw(Palette::Black);
	_object2sub.draw(Palette::Black);
	_object3.draw(Palette::White);
	_object3sub.draw(Palette::Black);
	_object9.draw(Palette::Black);
	_object9sub.draw(Palette::Black);
}
