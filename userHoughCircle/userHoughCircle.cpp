//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "userHoughCircle.h"
#include <opencv2/core/core.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <KScOpenCvUtils.h>
using namespace cv;
using namespace std;
// DLL을 만들기 위한 부분
BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: break;
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// 함수의 정의 부분
int CDECL userHoughCircle(KScRgbImage2d* input, KScRgbImage2d* output, float* r)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	Mat src, gray;
	src = KScRgbImage2dToMat(input);
	cvtColor(src, gray, CV_RGB2GRAY);

	GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 20, 200, 20, 5, 50);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		*r = radius;
	}
	MatToKScRgbImage2d(src, input);
	input->CopyToObject(output);
	// 후처리 /////////////////////////////////////////////////////////////////////
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


