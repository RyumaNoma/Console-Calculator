#include "Calc.hpp"
#define MAX_SIZE 256

int main()
{
	int idx = 0;
	std::string input;	
	
	while (true)
	{
		std::vector<TOKEN> tokens(0);
		
		// 入力
		std::cout << idx << " : ";
		std::getline(std::cin, input);
		
		// get token
		int char_count = 0;
		bool is_defined_char = false;
		while (input[char_count] != '\0')
		{
			is_defined_char = false;
			for (int i = 0; i < token_num; i++)
			{
				if (Calc::search(input[char_count], char_group[i]) >= 0)
				{
					tokens.push_back(static_cast<TOKEN>(i));
					is_defined_char = true;
					break;
				}
			}
			
			// 定義されていない文字
			if (!is_defined_char)
			{
				std::cout << input[char_count] << " is not defined." << std::endl;
				break;
			}
			
			char_count++;
		}
		
		if (!is_defined_char)
		{
			idx++;
			continue;
		}
		
		std::vector<int> nums = Calc::reduce_token(tokens, input);
		// 終端記号の追加
		tokens.push_back(TOKEN::END);
		
		// 表示
		/*
		int N = tokens.size();
		int a = 0;
		for(int i = 0; i < N; i++)
		{
			if (tokens[i] == TOKEN::NUMBER)
			{
				// printf("NUMBER(%d)", nums[a++]);
				std::cout << nums[a++];
			}
			else
			{
				std::cout << token_name[static_cast<int>(tokens[i])];
			}
			
			std::cout << ' ';
		}
		putchar('\n');
		*/
		
		// 構文解析、中間コード生成
		std::ofstream out("./code.txt");
		if (!out.is_open())
		{
			std::cout << "could not open code.txt(output)" << std::endl;
			idx++;
			continue;
		}
		
		try
		{
			int token_idx = 0;
			Calc::parse_polynomial(nums, tokens, token_idx, out);
		}
		catch (std::string ex)
		{
			std::cout << ex << std::endl;
			out.close();
			idx++;
			continue;
		}
		
		out.close();
		
		// 実行
		std::ifstream input("./code.txt");
		if (!input.is_open())
		{
			std::cout << "could not open code.txt(input)" << std::endl;
			idx++;
			continue;
		}
		
		std::stack<int> st;
		int num_idx = 0;
		std::string line;
		while (std::getline(input, line))
		{
			if (Calc::is_same(std::string("load number"), line))
			{
				st.push(nums[num_idx++]);
			}
			else if (Calc::is_same(std::string("calc pow"), line))
			{
				int a = st.top(); st.pop();
				int b = st.top(); st.pop();
				st.push(Calc::pow(b, a));
			}
			else if (Calc::is_same(std::string("calc multiple"), line))
			{
				int a = st.top(); st.pop();
				int b = st.top(); st.pop();
				st.push(b * a);
			}
			else if (Calc::is_same(std::string("calc devide"), line))
			{
				int a = st.top(); st.pop();
				int b = st.top(); st.pop();
				st.push(b / a);
			}
			else if (Calc::is_same(std::string("negative"), line))
			{
				int a = st.top(); st.pop();
				st.push(-a);
			}
			else if (Calc::is_same(std::string("calc add"), line))
			{
				int a = st.top(); st.pop();
				int b = st.top(); st.pop();
				st.push(b + a);
			}
			else if (Calc::is_same(std::string("calc sub"), line))
			{
				int a = st.top(); st.pop();
				int b = st.top(); st.pop();
				st.push(b - a);
			}
		}
		
		std::cout << "=> " << st.top() << std::endl;
		
		idx++;
		tokens.resize(0);
		nums.resize(0);
	}
}