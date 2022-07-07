

/*******************************************************************************
*	include
*******************************************************************************/

#include <iostream>
#include <cstdint>


/*******************************************************************************
*	protype
*******************************************************************************/
void InfoDisplay(void);
uint64_t FurlongsConvertToYards(uint32_t Yards);
uint32_t AgeConvertToMonth(void);

/*******************************************************************************
*	defition
*******************************************************************************/
using namespace std;


/*******************************************************************************
*	code
*******************************************************************************/
int main(int argc, char *argv[])
{
	InfoDisplay();
	uint32_t Yards = 10;
	uint64_t Furlongs = FurlongsConvertToYards(Yards);
	AgeConvertToMonth();

	cout << "end , thanks" << endl;
	return 0;
}

void InfoDisplay(void)
{
	
	cout << "banner13" << endl;
	cout << "y15689397856@163.com" << endl;
	
}

uint64_t FurlongsConvertToYards(uint32_t Yards)
{
	uint16_t ConversionRate = 220;
	uint64_t Furlongs = (uint64_t)Yards;
	
	Furlongs *= ConversionRate;
	cout << Furlongs << endl;
	return Furlongs;
}


uint32_t AgeConvertToMonth(void)
{
	uint8_t ConversionRate = 12;
	uint16_t Age;

	cout << "Enter your age: " << endl;
	cin >> Age;
	
	uint32_t Month = (uint32_t)(Age * ConversionRate);
	cout << Age << endl;
	
	cout << "Month is: " << Month << endl;
	return Month;
}
