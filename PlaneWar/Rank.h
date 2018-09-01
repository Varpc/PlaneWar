#pragma once
#include "GameObject.h"
#include <vector>
#include <algorithm>

struct Score {
	int score;
	char c;
	bool operator < (const Score & ans) const {
		return score < ans.score;
	}
};

class CRank : public CGameObject
{
public:
	CRank();
	~CRank();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);
	CRect GetRect();
	CRect GetRectCancel();
	static BOOL LoadImage();
private:
	enum {num, back, cancel, bang};
	bool m_bGetScore;
	std::vector<Score> m_nScore;
	static CImageList m_Images[4];
public:
	// 从文件中得到分数
	bool GetScore();
};

