#pragma once

#include "define.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stack>

namespace Calc
{
	int search(char key, const std::string str);
	int stoi(std::string s);
	std::vector<int> reduce_token(std::vector<TOKEN>& tokens, std::string& input);
	
	extern TOKEN token;
	void get_token(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx) throw(std::string);
	void parse_factor(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string);
	void parse_term(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string);
	void parse_polynomial(const std::vector<int>& nums, const std::vector<TOKEN>& tokens, int& token_idx, std::ofstream& out) throw(std::string);

	bool is_same(const std::string a, const std::string b);
	int pow(int a, int b);
};