#include <iostream>

int
main()
{
	int arr[3] = {1,10,100};
	int& x = arr[0];
	int& y = arr[1];
	int& z = arr[2];
	
	std::cout << x << "\t" << y << "\t" << z << "\n";
	for (int i=0; i<3; i++)
		std::cout << arr[i] << "\t";
	std::cout << std::endl;
	std::cout << std::endl;
	
	x = 9;

	std::cout << x << "\t" << y << "\t" << z << "\n";
	for (int i=0; i<3; i++)
		std::cout << arr[i] << "\t";
	std::cout << std::endl;
	std::cout << std::endl;
	
	arr[0] = 14;

	std::cout << x << "\t" << y << "\t" << z << "\n";
	for (int i=0; i<3; i++)
		std::cout << arr[i] << "\t";
	std::cout << std::endl;
}
