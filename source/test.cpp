# include <stdint.h>
# include <string>
# include <iostream>
# include <stdlib.h>
# include <map>
# define I 1
# define V 5
# define X 10
# define L 50
# define C 100
# define D 500
# define M 1000
using namespace std;

string solution3(int number) {
	    const map<int, string> bases = {
			        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
					    };
		    string rnum("");
			    for (auto it = bases.crbegin(); it != bases.crend(); ) {
					        if (number >= it->first) {
								            number -= it->first;
											            rnum += it->second;
														        } else {
																	            it++;
																				        }
							    }
				    
				    return rnum;
}

string solution2(int number){
	  
	  string c[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
	    int    n[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
		  
		  string result;
		    
		    for (int i = 0; i < 13; i++)
				    while (number-n[i] >= 0) {
						      result += c[i];
							        number -= n[i];
									    }

			  return result;
			    
}

string solution(int number)
{
  string  result;
  int32_t stretchFactor;
  int32_t tmp;
  
  for (; number >= M; number -= M)
      result.push_back('M');
  tmp     = number / 100 * 100;
  number -= tmp;
  if (tmp >= 500)
  {
    stretchFactor = (tmp - D) - (M - tmp) - 100;
    if (stretchFactor > 0)
    {
      for (int i = (M - tmp) / 100; i; --i)
        result.push_back('C');
      result.push_back('M');
    }
    else
    {
      result.push_back('D');
      for (int i = (tmp - D) / 100; i; --i)
        result.push_back('C');
    }
  }
  else if (tmp >= 100)
  {
    stretchFactor = (tmp - C) - (D - tmp) - 100;
    if (stretchFactor > 0)
    {
      for (int i = (D - tmp) / 100; i; --i)
        result.push_back('C');
      result.push_back('D');
    }
    else
    {
      result.push_back('C');
      for (int i = (tmp - C) / 100; i; --i)
        result.push_back('C');
    }
  }
  tmp = number / 10 * 10;
  number -= tmp;
  if (tmp >= 50)
  {
	  stretchFactor = (tmp - L) - (C - tmp) - 10;
	  if (stretchFactor > 0)
	  {
		  for (int i = (C - tmp) / 10; i; --i)
			result.push_back('X');
		  result.push_back('C');
	  }
	  else
	  {
		  result.push_back('L');
		  for (int i = (tmp - L) / 10; i; --i)
			  result.push_back('X');
	  }
  }
  else if (tmp >= 10)
  {
	  stretchFactor = (tmp - X) - (L - tmp) - 10;
	  if (stretchFactor > 0)
	  {
		  for (int i = (L - tmp) / 10; i; --i)
			  result.push_back('X');
		  result.push_back('L');
	  }
	  else
	  {
		  result.push_back('X');
		  for (int i = (tmp - X) / 10; i; --i)
			  result.push_back('X');
	  }
  }
  if (number >= 5)
  {
	  stretchFactor = (number - V) - (X - number) - 1;
	  if (stretchFactor > 0)
	  {
		  for (int i = (X - number); i; --i)
			  result.push_back('I');
		  result.push_back('X');
		}
	  else
	  {
		  result.push_back('V');
		  for (int i = number - V; i; --i)
			  result.push_back('I');
	  }
  }
  else if (number > 0)
  {
	  stretchFactor = (number - I) - (V - number) - 1;
	  if (stretchFactor > 0)
	  {
		  for (int i = (V - number); i; --i)
			  result.push_back('I');
		  result.push_back('V');
	}
	  else
	  {
		  for (int i = (number - I); i; --i)
		  	result.push_back('I');
		  result.push_back('I');
	  }
  }	
  return (result);
}

int main(int argc, char **argv)
{
	string result;
	if (atoi(argv[2]) == 1)
		for (int i = 0; i < 10000000; ++i)
			result = solution2(atoi(argv[1]));
	else if (atoi(argv[2]) == 2)
		for (int i = 0; i < 1000000; ++i)
			result = solution3(atoi(argv[1]));
	else
		for (int i = 0; i < 10000000; ++i)
			result = solution(atoi(argv[1]));
	std::cout << result << std::endl;
	return (0);
}
