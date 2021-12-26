#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>


typedef std::vector<std::vector<std::string>>	longmult_str;
typedef std::vector<std::vector<int>>		longmult_int;
typedef std::vector<std::vector<unsigned char>> numvec;
constexpr int ARRAYSIZE = 64;


class BigNumber
{
	private:
		long int value;
		bool quiet = false;
		longmult_int results;
		longmult_int ur_results;
		unsigned char sadstorage[ARRAYSIZE] = {0};
		numvec charresults;

		bool multiplicand_neg = false;
		bool multiplier_neg = false;
		//std::vector<int> accumulator;
	public:


		
		int UCharToInt(unsigned char number)
		{
			if(number < '0')
			{
				return -1;
			}
			else if(number > '9')
			{
				return -1;
			}
			return static_cast<int>(number - '0');
		}

		void set(long int n_value)
		{
			value = n_value;
		}
		void set(unsigned char n_value[ARRAYSIZE])
		{

			int newnum;
			long int bignumber = 0;
			long long int extrabignumber = 0;
			unsigned char refunit = '0';
			int insize = ARRAYSIZE;
			//insize = sizeof(n_value) / sizeof(refunit);
			for(int i = 0; i < insize; i++)
			{
				newnum = UCharToInt(n_value[i]);
				bignumber = newnum * pow(10, i);
				extrabignumber = newnum * pow(10, i);
				insize = i;
			}
			if(bignumber == extrabignumber)
			{
				set(bignumber);
			}
			else
			{
				for(int i = 0; i < insize; i++)
				{
					sadstorage[i] = n_value[i];
				}
			}
		}
		BigNumber(long int i_value)
		{
			set(i_value);
		}
		BigNumber(unsigned char i_value[ARRAYSIZE])
		{
			set(i_value);	
		}


		long number() const
		{
			return value;
		}

		void print_vect(std::vector<int> vect)
		{
			if (!quiet)
			{
			for( int i = 0; i < vect.size(); i++)
			{
				std::cout << vect.at(i);
			}
				std::cout << std::endl;
			}
		}
		
		void print_vect(std::vector<unsigned char> vect)
		{
			if (!quiet)
			{
			for( int i = 0; i < vect.size(); i++)
			{
				std::cout << vect.at(i);
			}
				std::cout << std::endl;
			}
		}

		void print_results()
		{
			bool temp = quiet;
			quiet = false;
			for(int i = 0; i < results.size(); i++)
			{
				print_vect(results.at(i));
			}
			quiet = temp;
		}

		void print_ur_results()
		{
			bool temp = quiet;
			quiet = false;
			for(int i = 0; i < ur_results.size(); i++)
			{
				print_vect(ur_results.at(i));
			}
			quiet = temp;
		}

		void print_charresults()
		{
			bool temp = quiet;
			quiet = false;
			for(int i = 0; i < charresults.size(); i++)
			{
				print_vect(charresults.at(i));
			}
			quiet = temp;
		}

		void simulate_multiply(const BigNumber& input, BigNumber& output)
		{
			results.clear();

			//STEP 1: MAKE VECTORS
			multiplicand_neg = false;
			multiplier_neg = false;
			if(input.number() < 0)
			{
				multiplicand_neg = true;
			}
			
			if(output.number() < 0)
			{
				multiplier_neg  = true;
			}
			
			int multa = input.number(); //copy to destroy

			std::vector<int> multiplicand;
			while (multa > 0)
			{
				multiplicand.push_back(multa % 10);	//get smallest decamal of multa
				multa /= 10;	//remove the decamal place just used, prepare for next round
			}
			
			std::vector<int> multiplier;
			multa = output.number(); 
			while (multa > 0)
			{
				multiplier.push_back(multa % 10);	//get smallest decamal of multa
				multa /= 10;	//remove the decamal place just used, prepare for next round
			}
			
			results.push_back(multiplicand);
			results.push_back(multiplier);

			for(unsigned int i = 0; i < multiplier.size(); i++)
			{
				std::vector<int> outp;
				
				//apply offset for magnitude of multiplier term
				for (int j = 0; j < i; j++)	//if i = 0, want to treat i-1 as -1, not as 4,294,967,295
				{
					outp.push_back(0);
				}
				
				//multiply an element of multiplier by all elements of multiplicand
				for (unsigned int j = 0; j < multiplicand.size(); j++)
				{
					outp.push_back(multiplier.at(i) * multiplicand.at(j));
				}
				

				//carry
				int carry = 0;
				for(unsigned int j = 0; j < outp.size(); j++)
				{
					outp.at(j) += carry;
					carry = outp.at(j) /10;
					outp.at(j) %= 10;
				}
				if(carry)
				{
					outp.push_back(carry);
				}

				results.push_back(outp);
			}

			//Sum rows

			//Set size of accumulating vector
			std::vector<int> accumulator = results.back();	
			//Set all elements of accumulator to zero
			//print_vect(accumulator);
			for (unsigned int i = 0; i < accumulator.size(); i++)
			{
				accumulator.at(i) = 0;
			}
			//print_vect(accumulator);

			//actually sum the rows
			for(unsigned int i = 2; i < results.size(); i++)	//skip the first two rows which are the multiplicand and the multiplier
			{
				for (unsigned int j = 0; j < results.at(i).size(); j++)
				{
					accumulator.at(j) += results.at(i).at(j);
				}
			}
			
			//do the carrying thing
			int carry = 0;
			for(unsigned int i = 0; i < accumulator.size(); i++)
			{
				accumulator.at(i) += carry;
				carry = accumulator.at(i) / 10;
				accumulator.at(i) %= 10;
			}
			if(carry)
			{
				accumulator.push_back(carry);
			}

			results.push_back(accumulator);



			//create un-reversed results vector for easy braining
			for(unsigned int i = 0; i < results.size(); i++)
			{
				std::vector<int> tempvect;
				for(int j = results.at(i).size() - 1; j >= 0; j--)
				{
					tempvect.push_back(results.at(i).at(j));
				}
			
				ur_results.push_back(tempvect);
			}	
			
						
/*			std::vector<int> tempvect;
			for(int i = accumulator.size() - 1; i >= 0; i--)
			{
				tempvect.push_back(accumulator.at(i));
			}
			
			accumulator = tempvect;
			results.push_back(accumulator);
*/
		}

		void multiply(BigNumber& input, BigNumber& output)
		{
			simulate_multiply(input, output);

			//make it an actual number
			std::vector<int> accumulator = results.back();
			long int accum = 0;
			for (unsigned int i = 0; i < accumulator.size(); i++)
			{
				accum += (accumulator.at(i) * pow(10, i));
			}
			
			if(multiplicand_neg ^ multiplier_neg)
			{
				accum = accum * -1;
			}

			//store it to output
			output.set(accum);
		}

		unsigned char IntToChar(int number)
		{
			return static_cast<unsigned char>(number + static_cast<int>('0'));
		}
	
		void MakeLongMultString()
		{

			for(unsigned int i = 0; i < ur_results.size(); i++)
			{	
				std::vector<unsigned char> tempvect;
				for (unsigned int j = 0; j < ur_results.at(i).size(); j++)
				{
					tempvect.push_back(IntToChar(ur_results.at(i).at(j)));
				}
	
				charresults.push_back(tempvect);
			}
			
			int thingwidth = ur_results.back().size();
			bool out_neg = multiplicand_neg ^ multiplier_neg;
			if (out_neg)
			{
				thingwidth++;	//add one character space for negative
			}

			int tempwidth = charresults.at(1).size() + 2;		//width of multiplier plus space plus x
			thingwidth = thingwidth > tempwidth ? thingwidth : tempwidth;
			if(multiplicand_neg)
			{
				tempwidth = charresults.at(0).size() + 1;	//width of multiplicand plus negative sign
				thingwidth = thingwidth > tempwidth ? thingwidth : tempwidth;
			}

			if(multiplicand_neg)
			{
				charresults.at(0).insert(charresults.at(0).begin(), '-');
			}
			if(multiplier_neg)
			{
				charresults.at(1).insert(charresults.at(1).begin(), '-');
			}

			for (unsigned int i = 0; i < charresults.size(); i++)
			{
				unsigned char bufferspace = ' ';
				while(charresults.at(i).size() < thingwidth)
				{
					charresults.at(i).insert(charresults.at(i).begin(), bufferspace);
				}
			}


			charresults.at(1).at(0) = 'x';	//set the leftmost char on the multiplier line to be 'x'
			std::vector<unsigned char> hyphens;
			for (int i = 0; i < thingwidth; i++)
			{
				hyphens.push_back('-');
			}
			charresults.insert(charresults.begin() + 2, hyphens);
			charresults.insert(charresults.end() - 1, hyphens);

			print_charresults();
		}


};

