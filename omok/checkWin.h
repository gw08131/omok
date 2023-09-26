#pragma once


// checkWin dialog

class checkWin : public CDialogEx
{
	DECLARE_DYNAMIC(checkWin)

public:
	checkWin(CWnd* pParent = nullptr);   // standard constructor
	virtual ~checkWin();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = checkWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
