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

TOKEN Calc::token;

void Calc::get_token(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx)
{
	Calc::token = tokens[token_idx++];
}

void Calc::parse_factor(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string)
{
	if (Calc::token == TOKEN::NUMBER)
	{
		out << "load number" << std::endl;
		Calc::get_token(nums, tokens, token_idx);
		
		if (Calc::token == TOKEN::POW)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_factor(nums, tokens, token_idx, out);
			out << "calc pow" << std::endl;
		}
	}
	else if (Calc::token == TOKEN::LEFTPER)
	{
		Calc::parse_polynomial(nums, tokens, token_idx, out);
		
		if (Calc::token == TOKEN::RIGHTPER)
		{
			Calc::get_token(nums, tokens, token_idx);
		}
		else
		{
			throw std::string("syntax error : expected ')'");
		}
	}
	else if (Calc::token == TOKEN::MINUS)
	{
		Calc::get_token(nums, tokens, token_idx);
		Calc::parse_factor(nums, tokens, token_idx, out);
		out << "negative" << std::endl;
	}
	else
	{
		throw std::string("syntax error : undefined factor");
	}
}

void Calc::parse_term(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string)
{
	Calc::parse_factor(nums, tokens, token_idx, out);
	
	while (true)
	{
		if (Calc::token == TOKEN::ASTER)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_factor(nums, tokens, token_idx, out);
			out << "calc multiple" << std::endl;
		}
		else if (Calc::token == TOKEN::SLASH)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_factor(nums, tokens, token_idx, out);
			out << "calc devide" << std::endl;
		}
		else
		{
			break;
		}
	}
}

void Calc::parse_polynomial(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string)
{
	Calc::get_token(nums, tokens, token_idx);
	
	if (Calc::token == TOKEN::PLUS)
	{
		Calc::get_token(nums, tokens, token_idx);
		Calc::parse_term(nums, tokens, token_idx, out);
	}
	else if (Calc::token == TOKEN::MINUS)
	{
		Calc::get_token(nums, tokens, token_idx);
		Calc::parse_term(nums, tokens, token_idx, out);
		out << "negative" << std::endl;
	}
	else
	{
		Calc::parse_term(nums, tokens, token_idx, out);
	}
	
	while (true)
	{
		if (Calc::token == TOKEN::PLUS)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_term(nums, tokens, token_idx, out);
			out << "calc add" << std::endl;
		}
		else if (Calc::token == TOKEN::MINUS)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_term(nums, tokens, token_idx, out);
			out << "calc sub" << std::endl;
		}
		else
		{
			break;
		}
	}
}