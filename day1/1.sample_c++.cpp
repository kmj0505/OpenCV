
#include <iostream>
#include <string>
#include <vector>
using namespace std;   //namespace를 선언하면 main의 string타입에 "std::"를 안붙여도 된다
//using namespace cv;


int main()
{
    const bool bComp = false;
    const int const_int = 100;
    const short const_short = 0xfff;
    const std::string const_str = "abcd";  //string만있으면 오류, namespace(std::)를 써줘야함
    std::string str_a = "a";
    std::string str_b = "b";
    std::string str_c = "c";   //namespace가 선언되지않았을 경우 std::를 붙여줘야함
    string str_d = "d";  //namespace std를 위에서 선언했기때문에 string타입 그대로 사용가능
    string str_e = "e";

    int a = 0;
    int b(0);
    std::cout << "Hello World!\n";
    
    int img1 = 0;
    int img2 = 0;
    int img3 = 0;
    int img4 = 0;
    int img5 = 0;

    int arrimg[25] = {0, };
    arrimg[5] = 5;
    arrimg[6] = 6;
    arrimg[7] = 7;
    arrimg[8] = 8;


    std::vector<int> vimg(5);

    int sz_int = sizeof(int);

    float f_data = 1.23;
    int n_data = (int)f_data;
    n_data = static_cast<int>(f_data); //c++_style

    const char const_string[] = "ABC";
    std::cout << const_string << std::endl;
    char* msg = const_cast<char*>(const_string);
    msg[0] = 'D';
    std::cout << const_string << std::endl;
    std::cout << msg << std::endl;

    //static_cast
    char cNum = 'a';
    int* pNum = nullptr;
    pNum = (int*)(&cNum); //c-style
    //pNum = static_cast<int*>(&cNum); //c++
    *pNum = 5;
    
    //f_data
    //??=(int)f_data;
    //n_data = ??

    return 0; //int 반환
}
