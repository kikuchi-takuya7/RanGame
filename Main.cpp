# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	

	while (System::Update())
	{
		Circle{ 400, 300, 20 }.draw();
	}
}

