#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
	const char* test = "\"HTTP/1.1 302 Redirect\r\nLocation: http://warning.or.kr\r\n\"";
	cout << strlen(test) << endl;
	return 0;
}
