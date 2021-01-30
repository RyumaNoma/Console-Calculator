#include "Calc.hpp"

TOKEN Calc::token;

void Calc::get_token(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx)
{
	Calc::token = tokens[token_idx++];
}

void Calc::parse_factor(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx)
{
	if (Calc::token == TOKEN::NUMBER)
	{
		std::cout << "load num" << std::endl;
		Calc::get_token(nums, tokens, token_idx);
	}
	else if (Calc::token == TOKEN::LEFTPER)
	{
		Calc::parse_polynomial(nums, tokens, token_idx);
		
		if (Calc::token == TOKEN::RIGHTPER)
		{
			Calc::get_token(nums, tokens, token_idx);
		}
		else
		{
			std::cerr << "syntax error : expected )" << std::endl;
		}
	}
	else
	{
		std::cerr << "syntax error : undefined factor" << std::endl;
		std::cerr << "syntax error : expected number or (" << std::endl;
	}
}

void Calc::parse_term(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx)
{
	Calc::parse_factor(nums, tokens, token_idx);
	
	while (true)
	{
		if (Calc::token == TOKEN::ASTER)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_factor(nums, tokens, token_idx);
			std::cout << "calc mult" << std::endl;
		}
		else if (Calc::token == TOKEN::SLASH)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_factor(nums, tokens, token_idx);
			std::cout << "calc div" << std::endl;
		}
		else
		{
			break;
		}
	}
}

void Calc::parse_polynomial(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx)
{
	Calc::get_token(nums, tokens, token_idx);
	
	if (Calc::token == TOKEN::PLUS)
	{
		Calc::get_token(nums, tokens, token_idx);
		Calc::parse_term(nums, tokens, token_idx);
	}
	else if (Calc::token == TOKEN::MINUS)
	{
		Calc::get_token(nums, tokens, token_idx);
		Calc::parse_term(nums, tokens, token_idx);
		std::cout << "calc neg" << std::endl;
	}
	else
	{
		Calc::parse_term(nums, tokens, token_idx);
	}
	
	while (true)
	{
		if (Calc::token == TOKEN::PLUS)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_term(nums, tokens, token_idx);
			std::cout << "calc add" << std::endl;
		}
		else if (Calc::token == TOKEN::MINUS)
		{
			Calc::get_token(nums, tokens, token_idx);
			Calc::parse_term(nums, tokens, token_idx);
			std::cout << "calc sub" << std::endl;
		}
		else
		{
			break;
		}
	}
}