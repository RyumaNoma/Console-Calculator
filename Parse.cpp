#include "Calc.hpp"

int Calc::search(char key, const std::string str)
{
	int idx = 0;
	int N = str.size();
	
	for (int i = 0; i < N; i++)
	{
		if (key == str[i])
		{
			return i;
		}
	}
	
	return -1;
}

int Calc::stoi(std::string str)
{
	int N = str.size();
	int out = 0;
	int rate = 1;
	
	for (int i = 0; i < N; i++)
	{
		out += (static_cast<int>(str[N - i - 1]) - '0') * rate;
		rate *= 10;
	}
	
	return out;
}

std::vector<int> Calc::reduce_token(std::vector<TOKEN>& tokens, std::string& input)
{
	std::vector<TOKEN> out_tokens;
	std::vector<int> nums;
	
	int N = tokens.size();
	
	int token_idx = 0;
	while (token_idx < N)
	{
		if (tokens[token_idx] == TOKEN::DIGIT)
		{
			int i = 0;
			while (tokens[token_idx + i] == TOKEN::DIGIT)
			{
				i++;
			}
			
			int num = Calc::stoi(input.substr(token_idx, i));
			nums.push_back(num);
			out_tokens.push_back(TOKEN::NUMBER);
			
			token_idx += i - 1;
		}
		else if (tokens[token_idx] == TOKEN::SPACE)
		{
		}
		else
		{
			out_tokens.push_back(tokens[token_idx]);
		}
		
		token_idx++;
	}
	
	tokens = out_tokens;
	return nums;
}