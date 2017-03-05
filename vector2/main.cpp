#include "vector2.h"
int main()
{
	Vector2 v1(1, 2), v2(0, 0);
	std::cin >> v2;
	Vector2 add = v1 + v2;
	Vector2 sub = v1 - v2;
	std::cout << "("<< v1 << ") + (" << v2 << ") = " << add << "      " << "("<< v1 << ") - (" << v2 << ") = " << sub << std::endl;
	v1 = v2 / 2;
	std::cout << "("<< v2 << ") / 2 = " << v1 << std::endl;
	v1 = 3 * v2;
	std::cout << "3 * ("<< v2 << ") = " << v1 << std::endl;
	std::cout << "("<< v1 << ") squareLen = " << v1.SquareLen() << std::endl;
	Vector2 v3 = v2 * 3;
	std::cout << "("<< v2 << ") * 3 = " << v3 << std::endl;
	v1 += v2;
	v3 -= v2;
	std::cout << "("<< v1 << ") += (" << v2 << ") : " << v1 << "      " << "("<< v3 << ") -= (" << v2 << ") : " << v3 << std::endl;
	std::cout << "("<< v1 << ") len = " << v1.Len() << "     Norm = "<< v1.Norm() << std::endl;
	std::cout << "("<< v3 << ") Perpendicular = " << v3.Perpendicular() << std::endl;
	float mul_s = v1 * v2;
	float mul_v = v1 ^ v2;
	std::cout << " ("<< v1 << ") * ("<< v2 << ") = " << mul_s << "      " << "("<< v1 << ") ^ (" << v2 << ") = " << mul_v << std::endl;
	std::cout << " - (" << v3 << ") = (" << -v3 << " )" << std::endl;
	v2 = v1.GetRotated(1.57);
	std::cout << "("<< v1 << ") rotate 1.57 = " << v2 << "      ("<< v1 << ") rotate 2 = " << v1.Rotate(2) << std::endl;
	std::cout << "("<< v1 << ")  (" << v2 << ") " << std::endl;
	v1 *= 5;
	v2 /= 2;
	std::cout << "("<< v1 << ")  (" << v2 << ") " << std::endl;
	return 0;
}
