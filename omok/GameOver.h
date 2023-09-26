#pragma once


// GameOver dialog

class GameOver : public CDialogEx
{
	DECLARE_DYNAMIC(GameOver)
	


public:
	GameOver(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GameOver();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	
public:
};
