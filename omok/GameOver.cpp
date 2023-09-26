// GameOver.cpp : implementation file
//

#include "pch.h"
#include "omok.h"
#include "GameOver.h"
#include "afxdialogex.h"


// GameOver dialog

IMPLEMENT_DYNAMIC(GameOver, CDialogEx)

GameOver::GameOver(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

GameOver::~GameOver()
{
}

void GameOver::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




// GameOver message handler