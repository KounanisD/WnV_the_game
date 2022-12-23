#include<iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "WnV.h"

using namespace std;

int main()
{

	WnV wnv("output.bin");  //obj wnv creating level using output.bin file

	wnv.playGame();  //main game function



	return 0;
}