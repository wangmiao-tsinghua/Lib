#pragma once
#pragma warning (disable: 4996)
/*Common header*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <ctime>
#include <fstream>
#include <assert.h>
//#include <windows.h>

/*OpenCV header*/
#include <opencv.hpp>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>



#define FOR(i,a,b) for (int i(a); i < (b); i++)
#define REP(i,b) for (int i(0); i < (b); i++)
#define SORT(v) sort((v).begin(),(v).end())
#define ALL(v) ((v).begin(),(v),end())
#define UNIQUE(v) sort((v).begin(),(v).end()),v.erase(unique(v.begin(),v.end()),v.end())
#define CLR(a,b) memset(a,b,sizeof(a))
#define SZ(Z) ((int)(Z).size())
#define PB push_back
#define MP make_pair
#define EPS 1e-6
#define SET_FONT_GREEN {SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);}

#define SET_FONT_RED {SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);}

#define SET_FONT_BLUE {SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);}

#define SET_FONT_YELLOW {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN);}

#define SET_FONT_MAGENTA {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);}

#define SET_FONT_CYAN {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);}

#define SET_FONT_WHITE {SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);}

#define SHOW_IMG(title,img){\
	imshow(title, img); \
	waitKey(); \
}
#define SET_CONSOLE {\
	system("mode con: cols=130");\
	system("title DreamFinder_v1");\
}
#define SEG_LINE {\
	SET_FONT_CYAN;\
	cout<<"--------------------------------------------------------------------------"<<endl;\
	SET_FONT_WHITE;\
}

const double PI = acos(-1.0);


using namespace std;
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib,"opencv_core231d.lib")
#pragma comment(lib,"opencv_features2d231d.lib")
#pragma comment(lib,"opencv_highgui231d.lib")
#pragma comment(lib,"opencv_imgproc231d.lib")
#else
#pragma comment(lib,"opencv_core231.lib")
#pragma comment(lib,"opencv_features2d231.lib")
#pragma comment(lib,"opencv_highgui231.lib")
#pragma comment(lib,"opencv_imgproc231.lib")
#endif



typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;


static string c_path="E:/WANGMIAO/Image2/";
static string thumb_path="E:/WANGMIAO/Image2sm/";
 
struct SortPair
{
	int idx;
	float val;
	bool operator<(const SortPair &rhs)const
	{
		return val>rhs.val;
	}
};