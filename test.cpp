#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	vector<int> v(0);

	v.push_back(3);
	v.push_back(3);
	cout << "capa :"  << v.capacity() <<endl;
	cout << "size :"  << v.size() <<endl;

	v.reserve(5);

	cout << "capa :"  << v.capacity() <<endl;
	cout << "size :"  << v.size() <<endl;

	v.resize(5);
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it <<endl;

	cout << "capa: " << v.capacity() <<endl;
	cout << "size :"  << v.size() <<endl;

	v.insert(v.begin(), 1000, 4);

	cout << "capa: " << v.capacity() <<endl;
	cout << "size :"  << v.size() <<endl;

	v.insert(v.begin(), 4);

	cout << "capa: " << v.capacity() <<endl;
	cout << "size :"  << v.size() <<endl;
	// cout << v.capacity() <<endl;
	return 0;
}

