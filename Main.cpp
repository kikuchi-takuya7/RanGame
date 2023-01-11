# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	
	const Texture background{ U"example/sky002_day.jpg" };
	double x = 0.0;

	while (System::Update())
	{
		
		x += (Scene::DeltaTime() * 180);
		background.draw(x, 0);
		Circle{ x, 100, 20 }.draw(Palette::Black);
		Vec2 player = {100, 500};

		Circle{ player.x, player.y, 20 }.draw(Palette::Black);
		Rect{ 0, 520, 1000, 10 }.draw(Palette::Black);

	}
}

