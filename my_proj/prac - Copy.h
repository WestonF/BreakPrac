#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>


typedef std::vector<std::vector<std::string>>	longmult_str;
typedef std::vector<std::vector<int>>		longmult_int;

class BigNumber
{
	private:
		long int value;
		bool quiet = false;
	public:


		void set(long int n_value)
		{
			value = n_value;
		}

		BigNumber(long int i_value)
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
				std::cout << vect.at(i) << " ";
			}
				std::cout << std::endl;
			}
		}

		void multiply(const BigNumber& input, BigNumber& output)
		{
			
			longmult_int results;
		
			int multa = input.number(), multb = output.number(); //copies to destroy
			std::cout << "mult a = " << multa << std::endl << "multb = " << multb << std::endl;
			int i = 0;
			while(multb > 0)
			{
				std::vector<int> multrow;
				int tempb = multb % 10;	// get just the smallest decamal place
				while (multa > 0)
				{
					long tempa = multa % 10;	//get smallest decamal pf multa
					multrow.push_back(tempb * tempa);
						
					multa /= 10;	//remove the decamal place just used, prepare for next round
				}
				print_vect(multrow);	
				//manage all elements that are greater than 9
				int carry = 0;
				for (unsigned int k = multrow.size() - 1; k >= 0; k--)
				{
					multrow.at(k) += carry;		//add existing carry
					carry = multrow.at(k) / 10;	//get next carry
					multrow.at(k) %= 10;		//remove carried value from current element
				}
				if(carry) //if carry != 0
				{
					multrow.push_back(carry);	
				}
							
				//unreverse results
				std::vector<int> temprow;
				for (unsigned int k = multrow.size(); k > 0; k--)
				{
					temprow.push_back(multrow.at(k));
				}
					
				multrow = temprow;
				
				//insert the decamal place offet for the higher digits of multa
				for (int k = i; k > 0; k--)
				{
					multrow.push_back(0);
				}
			
				i++;	//need one more offset of the above for each time loop has reached this point
				print_vect(multrow);
				results.push_back(multrow);//each row of results has the product of multa and one digit of multb
				multa = input.number();	//reset for next loop
				multb /= 10;
			}	
			
			//insert zeros at the front of each row vector until all vectors have the same number of elements as the last one
			unsigned int biggest_size = results.back().size();
			for (unsigned int k = 0; k < results.size(); k++)
			{
				while (results.at(k).size() < biggest_size)
				{
					results.at(k).insert(results.at(k).begin(), 0);
				}
			}
				
			//add elements
			std::vector<int> sums;
			int carry = 0;
			for (unsigned int k = biggest_size - 1; k >= 0; k--)
			{	
				int accumulator = 0;
				for(unsigned int j = 0; j < results.size(); j++)
				{	
					accumulator += results.at(j).at(k);	//take the k-th element of each vector and add them together
				}
			
				accumulator += carry;
				carry = accumulator / 10;
				accumulator %= 10;
				sums.push_back(accumulator);
			}
			
			if(carry)
			{
				sums.push_back(carry);
			}
			
			//un-reverse sums
			std::vector<int> tempvect;
			for(int k = 0; k < sums.size(); k++)
			{
				tempvect.push_back(sums.at(k));
			}
			sums = tempvect;
			
			long int result = 0;
			
			for (int k = sums.size() -1; k >= 0; k--)
			{
				result += sums.at(k) * pow(10, k);
			}
			
			output.set(result);
		
		}



};

