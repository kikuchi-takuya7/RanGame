﻿
# include <Siv3D.hpp> // OpenSiv3D v0.6.3
# include "Box.h"

//double JumpY(double velocity,Vec2 pos);

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
	double velocity = 0;//ジャンプの初速
	double gravity = 0;//重力
	int pattern[2]; //オブジェクトの配置パターン
	int period = 0; //パターンの周期

	//Vec2 ballVelocity{ 0,0 };
	////ボールの大きさ
	//Circle ball{ 400, 400, 8 };

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
		else if (die != 0) {
			Print << limit;
		}

		//30秒経過したらクリア
		if (limit <= 0) {

		}

		//最初の足場
		start -= tMove;
		RectF scaffold{ move, 500, 1600, 10 };
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
			velocity = 8.0f;
			gravity = 2.0f;
		}

		playerPos.y -= velocity;
		playerPos.y += gravity;
		gravity += 0.1f;

			if (playerPos.y >= 480) {
				playerPos.y = 480;
				velocity = 0;
			}

		//敵の表示

		switch (pattern[period])
		{
		case 1:
			
			RectF object10{ move3 + 100, bottomO - 40, 305, 100 };
			object10.draw(Palette::Black);
			//横の壁のオブジェクト
			RectF object{ move2, bottomO, 10, 100 };
			object.draw(Palette::Black);
			//上の壁のオブジェクト
			RectF objectsub{ move2+1, bottomO, 101, 100 };
			objectsub.draw(Palette::Black);

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
			//横の壁のオブジェクト
			RectF object2{ move2 + 650, bottomO, 10, 100 };
			object2.draw(Palette::Black);
			//上の壁のオブジェクト
			RectF object2sub{ move2 +652, bottomO, 101, 100 };
			object2sub.draw(Palette::Black);
			//横の壁のオブジェクト
			RectF object3{ move3 + 100, bottomO - 50, 10, 100 };
			  object3.draw(Palette::Black);//当たり判定必要
			  //上の壁のオブジェクト
			RectF object3sub{ move3 + 105, bottomO - 50, 101, 100 };
			object3sub.draw(Palette::Black);

			RectF object4{ move3 + 200, bottomO - 50, 100, 100 };
			object4.draw(Palette::Black);
			//横の壁のオブジェクト
			RectF object5{ move3 + 200, bottomO - 150, 10, 100 };
			object5.draw(Palette::Black);//当たり判定必要
			//上の壁のオブジェクト
			RectF object5sub{ move3 + 201, bottomO - 150, 101, 100 };
			object5sub.draw(Palette::Black);
			//横の壁のオブジェクト
			RectF object6{ move3 + 300, bottomO - 250, 10, 100 };
			object6.draw(Palette::Black);//当たり判定必要
			//上の壁のオブジェクト
			RectF object6sub{ move3 + 305, bottomO - 250, 100, 100 };
			object6sub.draw(Palette::Black);

			RectF object7{ move3 + 300, bottomO - 150, 105, 100 };
			object7.draw(Palette::Black);

			RectF object8{ move3 + 300, bottomO - 50, 105, 100 };
			object8.draw(Palette::Black);

			Triangle enemy5{ move3 + 300, bottomE, scaleE };
			enemy5.draw(Palette::Red);

			Triangle enemy6{ move3 + 500, bottomE, scaleE };
			enemy6.draw(Palette::Red);
			//横の壁のオブジェクト
			RectF object9{ move3 + 700, bottomO, 10, 100 };
			object9.draw(Palette::Black);
			//上の壁のオブジェクト
			RectF object9sub{ move3 + 705, bottomO, 100, 100 };
			object9sub.draw(Palette::Black);

			/*RectF object10{ move3 + 100, bottomO - 40, 305, 100 };
			object10.draw(Palette::Black);*/

			//当たり判定
			//敵に当たったら、画面が止まる
			if (enemyS.intersects(player)) {
				die += 1;
			}
			if (enemyS2.intersects(player)) {
				die += 1;
			}
			if (enemy3.intersects(player)) {
				die += 1;
			}
			if (enemy4.intersects(player)) {
				die += 1;
			}
			if (enemy5.intersects(player)) {
				die += 1;
			}
			if (enemy6.intersects(player)) {
				die += 1;
			}
			
			/*オブジェクトに当たったら、押し戻される*/
			if (object.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (objectsub.intersects(player)) {
				if (playerPos.y >= 379) {
					playerPos.y = 379;
					velocity = 0;
					gravity = 0;
				}

			}
			/*オブジェクトに当たったら、押し戻される*/

			if (object2.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (object2sub.intersects(player)) {
				if (playerPos.y >= 379) {
					playerPos.y = 379;
					velocity = 0;
					gravity = 0;
				}

			}
			if (object3.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (object3sub.intersects(player)) {
				if (playerPos.y >= 329) {
					playerPos.y = 329;
					velocity = 0;
					gravity = 0;
				}

			}
			if (object5.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (object5sub.intersects(player)) {
				if (playerPos.y >= 229) {
					playerPos.y = 229;
					velocity = 0;
					gravity = 0;
				}

			}
			if (object6.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (object6sub.intersects(player)) {
				if (playerPos.y >= 129) {
					playerPos.y = 129;
					velocity = 0;
					gravity = 0;
				}

			}
			if (object9.intersects(player)) {
				playerPos.x = playerPos.x - tMove;
			}
			if (object9sub.intersects(player)) {
				if (playerPos.y >= 380) {
					playerPos.y = 380;
					velocity = 0;
					gravity = 0;
				}

			}
			if (object10.intersects(player)) {

				playerPos.y = 480;
				velocity = 0;
				gravity = 0;

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




