// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

int CProcess::getStarInfo(CImage* pImage, int nTh)
{
    unsigned char* fm = (unsigned char*)pImage->GetBits();  // 이미지 데이터의 포인터를 불러옴

    // 이미지의 너비와 높이 불러오기
    int nWidth = pImage->GetWidth();
    int nHeight = pImage->GetHeight();
    int nPitch = pImage->GetPitch();  // 이미지의 행마다 바이트 단위로 저장되는데, 행 간 간격을 얻어옴
    int nSum = 0;  // 픽셀 값이 임계값(nTh)을 초과하는 픽셀의 수를 저장할 변수를 초기화

    // 이미지의 모든 픽셀을 순회하면서 임계값을 초과하는 경우 픽셀 수를 증가시킴
    for (int k = 0; k < nWidth * nHeight; k++) {
        if (fm[k] > nTh) {
            nSum++;
        }
    }

    // 임계값을 초과하는 픽셀의 수를 반환
    return nSum;
}



// CProcess 멤버 함수
