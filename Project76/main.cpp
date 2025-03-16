#include<iostream>
#include<vector>
#include<cmath>
#include <iomanip>


using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Term
{
private:
	int group; //表示1的个数 或 组别
    vector<int> oct;//项中包含的所有最小项的编号
	vector<int> binary;//使用二维数组 存储 项中所有最小项的二进制形式
public:
	int nbit;
	bool combine_flag;//合并标志
	Term(vector<int> arr,vector<int> index, int k)
	{
		group = 0;
		combine_flag = 0;
		nbit = k;
		int n = 0;
		binary.resize(k);
		for (int i = 0;i < index.size();i++)
		{
			n = arr[index[i]];
			oct.push_back(n);
		}
		n = arr[index[0]];
		for (int j = k - 1;j >= 0;j--)
		{
			binary[j] = n % 2;
			n /= 2;
		}
	};
	void set_binary(vector<int> nbinary)
	{
		binary.assign(nbinary.begin(), nbinary.end());
	}
	int count()//记录第一个最小项中1的个数
	{
		int m = 0;
		for (int i = 0;i < binary.size();i++)
		{
			if (binary[i] == 1)
			{
				m++;
			}
		}
		return m;
	}
	vector<int> element_oct()
	{
		vector<int> ans(oct);
		return ans;
	}
	vector<int> element_bin()
	{
		vector<int> nbinary(binary);
		return nbinary;
	}
	Term operator+(const Term term)const
	{
		vector<int> index(oct.size());
		for (int i = 0;i < oct.size();i++)
		{
			index[i] = i;
		}
		Term combine(oct, index, nbit);
		combine.set_binary(binary);
		int n = 0;
		for (int i = 0;i < term.oct.size();i++)
		{
			combine.oct.push_back(term.oct[i]);
		}
		for (int i = 0;i < nbit;i++)
		{
			if (combine.binary[i] != term.binary[i])
			{
				combine.binary[i] = -1;
			}
		}
		return combine;
	}
};

void print_form0(vector<vector<Term>> form)
{
	cout << "======第一步，按1的个数分组======" << endl;
	cout << "组别\t\t\t最小项\t\t\t逻辑表示" << endl;
	vector<int> binary,oct;
	int k = 0;
	for (int i = 0;i < form.size();i++)
	{
		for (int j = 0;j < form[i].size();j++)
		{
			binary.clear();
			oct.clear();
			oct = form[i][j].element_oct();
			cout << i << " \t\t\t";
			for (k = 0;k < (oct.size() - 1); k++)
			{
				cout << oct[k];
				cout << ',';
			}
			cout << oct[k]<<" \t\t\t";
			binary=form[i][j].element_bin();
			for (k = 0;k < binary.size(); k++)
			{
				if (binary[k] == -1)
				{
					cout << '-';
				}
				else
				{
					cout << binary[k];
				}
			}
			cout << endl;
		}
	}
}
void print_form1(vector<vector<Term>> form,int t)
{
	cout << "======第 "<<t<<" 步， "<<t-1<<" 次合并======" << endl;
	cout << "组别\t\t\t合并项\t\t";
	for (int i = 0;i < t;i++)
	{
		cout << "  \t";
	}
	cout<<"逻辑表示" << endl;
	vector<int> binary,oct;
	int k = 0;
	for (int i = 0;i < form.size();i++)
	{
		for (int j = 0;j < form[i].size();j++)
		{
			binary.clear();
			oct.clear();
			oct = form[i][j].element_oct();
			cout << i << " \t\t\t";
			for (k = 0;k < (oct.size()-1); k++)
			{
				cout << std::right << std::setw(3) << oct[k];
				cout << ',';
			}
			cout << std::right << std::setw(4) << oct[k];
			cout << " \t\t\t";
			binary = form[i][j].element_bin();
			for (k = 0;k < binary.size(); k++)
			{
				if (binary[k] == -1)
				{
					cout << '-';
				}
				else
				{
					cout << binary[k];
				}
			}
			cout << endl;
		}
	}
}

void print_group(vector<Term> group,int t)
{
	cout << "======第 "<<t<<" 步，提取质蕴含项======\n";
	cout << "质蕴涵项" << "\t\t\t" << "逻辑表示" << endl;
	vector<int> binary, oct;
	int k = 0;
	for (int i = 0;i < group.size();i++)
	{
		binary.clear();
		oct.clear();
		oct = group[i].element_oct();
		for (k = 0;k < (oct.size() - 1); k++)
		{
			cout << std::right << std::setw(3) << oct[k];
			cout << ',';
		}
		cout << std::right << std::setw(3) << oct[k];
		cout << "\t\t\t";
		binary = group[i].element_bin();
		for (int k = 0;k < binary.size(); k++)
		{
			if (binary[k] == -1)
			{
				cout << '-';
			}
			else
			{
				cout << binary[k];
			}
		}
		cout << endl;
	}
}

void print_group1(vector<Term> group, int t)
{
	cout << "======第 " << t << " 步，提取实质蕴含项======\n";
	cout << "实质蕴涵项" << "\t\t\t" << "逻辑表示" << endl;
	vector<int> binary, oct;
	int k = 0;
	for (int i = 0;i < group.size();i++)
	{
		binary.clear();
		oct.clear();
		oct = group[i].element_oct();
		for (k = 0;k < (oct.size() - 1); k++)
		{
			cout << std::right << std::setw(3) << oct[k];
			cout << ',';
		}
		cout << std::right << std::setw(3) << oct[k];
		cout << "\t\t\t";
		binary = group[i].element_bin();
		for (int k = 0;k < binary.size(); k++)
		{
			if (binary[k] == -1)
			{
				cout << '-';
			}
			else
			{
				cout << binary[k];
			}
		}
		cout << endl;
	}
}

void print_group2(vector<Term> group, int t)
{
	cout << "======第 " << t << " 步，选择最小覆盖质蕴含组合======\n";
	cout << "选择后的质蕴涵项" << "\t\t " << "逻辑表示" << endl;
	vector<int> binary, oct;
	int k = 0;
	for (int i = 0;i < group.size();i++)
	{
		binary.clear();
		oct.clear();
		oct = group[i].element_oct();
		for (k = 0;k < (oct.size() - 1); k++)
		{
			cout << std::right << std::setw(3) << oct[k];
			cout << ',';
		}
		cout << std::right << std::setw(3) << oct[k];
		cout << "\t\t\t";
		binary = group[i].element_bin();
		for (int k = 0;k < binary.size(); k++)
		{
			if (binary[k] == -1)
			{
				cout << '-';
			}
			else
			{
				cout << binary[k];
			}
		}
		cout << endl;
	}
}

void print_result(vector<Term> result, int t)
{
	cout << "======第 " << t << " 步，转换为与或表达式(大写字母为是，小写字母为非）======\n";
	cout << "化简结果：";
	vector<int> binary;
	for (int i = 0;i < result.size();i++)
	{
		binary.clear();
		binary = result[i].element_bin();
		for (int j = 0;j < binary.size();j++)
		{
			if (binary[j] == 1)
			{
				cout << (char)(j + 65);//ASCII码: 65->A  97->a
			}
			if (binary[j] == 0)
			{
				cout << (char)(j + 97);//ASCII码: 65->A  97->a
			}
		}
		if (i < result.size() - 1)
		{
			cout << "+";
		}
	}
	cout << endl << "======化简完成，按回车键退出======" << endl;
}

void simplify_group(vector<Term> &group)
{
	for (int i = 0;i < (group.size()-1);i++)
	{
		if (group[i].element_bin() == group[i + 1].element_bin())
		{
			group.erase(group.begin() + i);
		}
	}
}

vector<Term> extract_group(vector<Term> group)
{
	vector<Term> result;
	vector<int> oct1,oct2;
	int flag = 0;
	for (int i = 0;i < group.size();i++)
	{
		oct1.clear();
		oct1 = group[i].element_oct();
		for (int j = 0;j < oct1.size();j++)
		{
			flag = 1;
			for (int k = 0;k < group.size();k++)
			{
				if (k != i)
				{
					oct2.clear();
					oct2 = group[k].element_oct();
					for (int m = 0;m < oct2.size();m++)
					{
						if (oct1[j] == oct2[m])
						{
							flag = 0;
						}
					}
				}
			}
			if (flag)
			{
				result.push_back(group[i]);
				break;
			}
		}
	}
	return result;
}

vector<vector<Term>> combine(vector<vector<Term>> form, vector<Term> &group1)
{
	vector<vector<Term>> new_form;
	vector<Term> term;
	vector<int> binary1,binary2;
	int count;
	for (int i = 0;(i + 1) < form.size();i++)
	{
		term.clear();
		for (int j = 0;j < form[i].size();j++)
		{
			for (int k = 0;k < form[i + 1].size(); k++)
			{
				binary1.clear();
				binary2.clear();
				count = 0;
				binary1 = form[i][j].element_bin();
				binary2 = form[i+1][k].element_bin();
				for (int m = 0;m < binary1.size();m++)
				{
					if (binary1[m] == binary2[m])
					{
						count++;
					}
				}
				if (count == (binary1.size() - 1))
				{
					form[i][j].combine_flag = 1;
					form[i + 1][k].combine_flag = 1;
					term.push_back(form[i][j] + form[i + 1][k]);
				}
			}
		}
		new_form.push_back(term);
	}
	for (int i = 0;i < form.size();i++)
	{
		for (int j = 0;j < form[i].size();j++)
		{
			if (form[i][j].combine_flag == 0)
			{
				group1.push_back(form[i][j]);
			}
		}
	}
	return new_form;
}

vector<Term> remainder(vector<int> s, vector<Term> group, vector<Term> group1)
{
	vector<int> s1(s),s2,oct;
	vector<Term> result,tempo;
	int count,min,flag;
	for (int i = 0;i < group1.size();i++)
	{
		oct.clear();
		oct = group1[i].element_oct();
		for (int j = 0;j < oct.size();j++)
		{
			for (int k = 0;k < s1.size();k++)
			{
				if (oct[j] == s1[k])
				{
					s1.erase(s1.begin() + k);
					k--;
				}
			}
		}
	}
	min = group1.size();
	for (int m = 0;m < group.size();m++)
	{
		count = 0;
		tempo.clear();
		s2.clear();
		s2 = s1;
		for (int i = m;i < group.size();i++)
		{
			flag = 0;
			oct.clear();
			oct = group[i].element_oct();
			for (int j = 0;j < oct.size();j++)
			{
				for (int k = 0;k < s2.size();k++)
				{
					if (oct[j] == s2[k])
					{

						s2.erase(s2.begin() + k);
						k--;
						flag = 1;
					}
				}
			}
			if (flag)
			{
				tempo.push_back(group[i]);
				count++;
			}
		}
		if (count <= min && s2.size()==0)
		{
			min = count;
			result.clear();
			result = tempo;
		}
	}
	for (int i = 0;i < group1.size();i++)
	{
		result.push_back(group1[i]);
	}
	return result;
}

int main()
{
	vector<vector<Term>> form,form1;
	int n,nbit;
	vector<int> s;//暂存输入的最小项
	int i = 0;
	cout << "============Q-M法化简多变量逻辑============" << endl;
	cout << "请输入最小项编号（空格键分隔，回车键结束输入）" << endl;
	while (cin>>n)
	{
		s.push_back(n);
		if (cin.get() == '\n')
		{
			break;
		}
	}
	n = 0;
	for (i = 0;i < s.size();i++)
	{
		if (s[i] < 0)
		{
			cout << "数据错误，程序终止。\n";
			return 0;
		}
		else if (s[i] > n)
		{
			n = s[i];
		}
	}
	nbit = 0;
	while (pow(2,nbit) <= n)
	{
		nbit++;
	}
	vector<Term> group,group1;//group前期用于向form传递数据，中期用于存储质蕴含项,group1存储实质蕴含项(essential prime implicant)
	vector<int> index(1);
	for (i = 0;i < s.size();i++)
	{
		index[0] = i;
		Term term(s, index, nbit);
		group.push_back(term);
	}
	for (i = 0;i < group.size();i++)//按1的个数进行分组，从group中提取数据，构造form表
	{
		int m = group[i].count();
		group1.clear();
		while (form.size() <= m)
		{
			form.push_back(group1);
		}
		form[m].push_back(group[i]);
	}
	print_form0(form);
	group.clear();
	i = 2;
	while (form.size())
	{
		form = combine(form, group);
		n = 0;
		for (int j = 0;j < form.size();j++)
		{
			n += form[j].size();
		}
		if (n)
		{
			print_form1(form, i);
			i++;
		}
	}
	simplify_group(group);
	print_group(group,i++);
	group1 = extract_group(group);
	print_group1(group1,i++);
	vector<Term> result = remainder(s,group,group1);
	print_group2(result, i++);
	print_result(result, i);
	getchar();
	return 0;



}