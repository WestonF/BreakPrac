#include <iostream>
#include <ctime>
#include <ctype.h>

		int** p_p_placeholder;
		int* p_placeholder;
		int placeholder;
class Calendar
{
	private:
		int MM = 1;
		int YYYY = 2000;
		int calendar[7][7] = {0};
		int* p_cal = &calendar[0][0];
		int** pp_cal = &p_cal;
		static const int dayspermonth[];
		bool leapyear = false;
		const std::string monthnames[12] = {"January" , "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		const std::string monthspacers[12] ={ "    ", "   ", "      ", "     ", "        ", "       ", "       ", "     ", "  ", "    ", "   ", "   "};
	public:

	enum class WEEK
	{
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};
	
	//bulk of this function adapted from external example as I was unclear what "unix time function" was expected to be used to determine the day of week for the first of a given month
	int dayofweek(int month, int year)
	{
		const int magic[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
		year -= month < 3;
		//[month - 1] to zero-index; + 1 because this formula is only being used for the first of the month 
		return ( (year + (year / 4) - (year / 100) + (year / 400) + magic[month - 1] + 1) % 7);
	}

	void populatemonth()
	{
		//set all values of calendar to 0
		/*for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				calendar[i][j] = 7;
			}
			std::cout << i << " ";
		}*/
		
		//clear contents of calendar
		for(int i = 0; i < (7 * 7); i++)
		{
			p_cal[i] = 0;
		}
		
		int day1 = dayofweek(MM, YYYY);
		int days = dayspermonth[MM - 1];	//zero-index MM
		if((MM == 2) && (leapyear))
		{
			days++;
		}

		int current_day = 1;
		int week = 0;			
		
		WEEK dayindex = static_cast<WEEK>(day1);
	
		while(current_day <= days)
		{ 
			calendar[static_cast<int>(dayindex)][week] = current_day;

			//dayindex++
			dayindex = static_cast<WEEK>(static_cast<int>(dayindex) + 1);
			
			if (dayindex > WEEK::SATURDAY)
			{
				dayindex = WEEK::SUNDAY;
				week++;
			}	
			current_day++;
		}
		
		//fill the rest of the week with nothings
		while(dayindex <= WEEK::SUNDAY)
		{
			calendar[static_cast<int>(dayindex)][week] = 0;
			dayindex = static_cast<WEEK>(static_cast<int>(dayindex) + 1);
		}

		//fill the next week with nothing 
		week++;
		for (int i = 0; i < 7; i++)
		{
			calendar[i][week] = 0;
		}

	}

	void set(int month, int year)
	{
		MM = month;
		YYYY = year;

		if(YYYY % 4 == 0)
		{
			leapyear = true;
		}

		populatemonth();
	}

	Calendar(int month, int year)
	{
		set(month, year);
	}

	void printmonth()	const
	{
		std::cout << monthspacers[MM-1] << monthnames[MM-1] << ", " << YYYY << std::endl;
		std::cout << " S  M  T  W  T  F  S" << std::endl;
		int week = 0;
		WEEK dayindex = WEEK::SUNDAY;
		while((calendar[0][week] != 0)||(calendar[6][week] != 0))	//if Sunday and Saturday are both zero, the week is empty
		//while(week < 6)
		{
			for( int i = 0; i < 7; i++)
			{
				if(calendar[i][week] == 0)
				{
					std::cout << "  ";
				}
				else
				{
					if(calendar[i][week] <= 9)
					{
						std::cout << " ";	//add buffer space for single-digit days
					}

					std::cout << calendar[i][week];
				}

				std::cout << " ";
			}
			std::cout << std::endl;
			week++;
		}
	}

	void getmmyyyy()
	{
		std::string textin;
		std::getline(std::cin, textin);
		getmmyyyy(textin);
	}
	void getmmyyyy(std::string textin)	
	{	
		if (textin.length() < 7)	// not MM YYYY
		{
			std::cout << "Invalid date format, please use MM YYYY." << std::endl;
			return;
		}
		
		textin.erase(2,1);	//delete the space
			
		for (unsigned int i = 0; i < textin.length(); i++)
		{
			if(!isdigit(textin[i]))
			{
				std::cout << "Invalid date format, please use MM YYYY." << std::endl;
				return;
			}
		}
	
		int temp = static_cast<int>((textin[0] - '0') * 10) + static_cast<int>(textin[1] - '0');
		if (temp < 0)
		{
			std::cout << "Invalid date format, please use MM YYYY." << std::endl;
			return;
		}
		else if (temp > 12)
		{
			std::cout << "Invalid date format, please use MM YYYY." << std::endl;
			return;
		}
		
		MM = temp;
		YYYY =	( static_cast<int>((textin[5] - '0') * 1)
			+ static_cast<int>((textin[4] - '0') * 10)
		       	+ static_cast<int>((textin[3] - '0') * 100) 
			+ static_cast<int>((textin[2] - '0') * 1000));
		
		set(MM,YYYY);
		
	}

	int** get()	const
	{
		return pp_cal;
	}
		
	void print()	const
	{
		printmonth();
	}

};

//						Jan, Feb, Mar, Apr, May, June, July, Aug, Sep, Oct, Nov, Dec
const int Calendar::dayspermonth[12] = {	 31,  28,  31,  30,  31,   30,   31,  31,  30,  31,  30,  31};
