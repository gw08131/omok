
// omokDlg.cpp : implementation file
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "pch.h"
#include "framework.h"
#include "omok.h"
#include "omokDlg.h"
#include "afxdialogex.h"
#include "checkWin.h"
#include <queue>
#include <thread>
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define CIRCLE_SIZE 20
#define  X_SIZE 600
#define Y_SIZE 610
int visited[Y_SIZE + 1][X_SIZE + 1] = { 0 };
#define PACKET_SIZE 1024
SOCKET skt;
bool sign = false;
typedef struct CMD_LOGIN {	//1
	int color;
}CMD_LOGIN;
// 0 = empty, 1 = 흰돌, 2=검은돌
//sign: false = white, true = balck

// ComokDlg dialog
bool canPlay = true;
std::queue<std::pair<int, int>> v;

void ComokDlg::checkWin(int x, int y)
{
	int nowPlayer = 0;
	bool isWin = false;
	int a1x, a1y = 0;
	int a2x, a2y = 0;
	int a3x, a3y = 0;
	int a4x, a4y = 0;
	int a5x, a5y = 0;

	//CClientDC dc(this);
	//CBrush red(RGB(255, 0, 0));
	//CBrush* rred = dc.SelectObject(&red);
	//	
	//	dc.Ellipse((y_index) * 40 + 10 - CIRCLE_SIZE + 20, x_index * 40 - CIRCLE_SIZE + 20, (y_index) * 40 + 10 + CIRCLE_SIZE + 20, x_index * 40 + CIRCLE_SIZE + 20);
		//dc.SelectObject(rred);

	/*for (int i = 0; i < 5; i++) //세로 이김 
	{
		if (x - 4 + i >= 0)
		{
			if (visited[x - 4 + i][y] == 1 && visited[x - 3 + i][y] == 1 && visited[x - 2 + i][y] == 1 && visited[x - 1 + i][y] == 1 && visited[x + i][y] == 1)
			{
				isWin = true;
				nowPlayer = 1;

				v.push({ x - 4 + i,y });
				v.push({ x - 3 + i,y });
				v.push({ x - 2 + i,y });
				v.push({ x - 1 + i,y });
				v.push({ x + i,y });
			}
			else if (visited[x - 4 + i][y] == 2 && visited[x - 3 + i][y] == 2 && visited[x - 2 + i][y] == 2 && visited[x - 1 + i][y] == 2 && visited[x + i][y] == 2)
			{
				isWin = true;
				nowPlayer = 2;

				v.push({ x - 4 + i,y });
				v.push({ x - 3 + i,y });
				v.push({ x - 2 + i,y });
				v.push({ x - 1 + i,y });
				v.push({ x + i,y });
			}
		}
	}

	for (int i = 0; i < 5; i++) // 가로 이김 
	{
		if (x - 4 + i >= 0)
		{
			if (visited[x][y - 4 + i] == 1 && visited[x][y - 3 + i] == 1 && visited[x][y - 2 + i] == 1 && visited[x][y - 1 + i] == 1 && visited[x][y + i] == 1)
			{
				isWin = true;
				nowPlayer = 1;

				v.push({ x , y - 4 + i });
				v.push({ x , y - 3 + i });
				v.push({ x , y - 2 + i });
				v.push({ x , y - 1 + i });
				v.push({ x , y + i });
			}
			else if (visited[x][y - 4 + i] == 2 && visited[x][y - 3 + i] == 2 && visited[x][y - 2 + i] == 2 && visited[x][y - 1 + i] == 2 && visited[x][y + i] == 2)
			{
				isWin = true;
				nowPlayer = 2;

				v.push({ x , y - 4 + i });
				v.push({ x , y - 3 + i });
				v.push({ x , y - 2 + i });
				v.push({ x , y - 1 + i });
				v.push({ x , y + i });
			}
		}
	}

	for (int i = 0; i < 5; i++) // 오른쪽 대각선 이김 
	{
		if (x - 4 + i >= 0)
		{
			if (visited[x - 4 + i][y - 4 + i] == 1 && visited[x - 3 + i][y - 3 + i] == 1 && visited[x - 2 + i][y - 2 + i] == 1 && visited[x - 1 + i][y - 1 + i] == 1 && visited[x + i][y + i] == 1)
			{
				isWin = true;
				nowPlayer = 1;

				v.push({ x - 4 + i , y - 4 + i });
				v.push({ x - 3 + i , y - 3 + i });
				v.push({ x - 2 + i , y - 2 + i });
				v.push({ x - 1 + i , y - 1 + i });
				v.push({ x + i , y + i });
			}
			else if (visited[x - 4 + i][y - 4 + i] == 2 && visited[x - 3 + i][y - 3 + i] == 2 && visited[x - 2 + i][y - 2 + i] == 2 && visited[x - 1 + i][y - 1 + i] == 2 && visited[x + i][y + i] == 2)
			{
				isWin = true;
				nowPlayer = 2;

				v.push({ x - 4 + i , y - 4 + i });
				v.push({ x - 3 + i , y - 3 + i });
				v.push({ x - 2 + i , y - 2 + i });
				v.push({ x - 1 + i , y - 1 + i });
				v.push({ x + i , y + i });
			}
		}
	}

	for (int i = 0; i < 5; i++) // 왼쪽 대각선 이김 
	{
		if (y - 4 + i >= 0)
		{
			if (visited[x - i][y + i] == 1 && visited[x + 1 - i][y - 1 + i] == 1 && visited[x + 2 - i][y - 2 + i] == 1 && visited[x + 3 - i][y - 3 + i] == 1 && visited[x + 4 - i][y - 4 + i] == 1)
			{
				isWin = true;
				nowPlayer = 1;

				v.push({ x + 4 - i , y - 4 + i });
				v.push({ x + 3 - i , y - 3 + i });
				v.push({ x + 2 - i, y - 2 + i });
				v.push({ x + 1 - i , y - 1 + i });
				v.push({ x - i , y + i });
			}
			else if (visited[x - i][y + i] == 2 && visited[x + 1 - i][y - 1 + i] == 2 && visited[x + 2 - i][y - 2 + i] == 2 && visited[x + 3 - i][y - 3 + i] == 2 && visited[x + 4 - i][y - 4 + i] == 2)
			{
				isWin = true;
				nowPlayer = 2;

				v.push({ x + 4 - i , y - 4 + i });
				v.push({ x + 3 - i , y - 3 + i });
				v.push({ x + 2 - i, y - 2 + i });
				v.push({ x + 1 - i , y - 1 + i });
				v.push({ x - i , y + i });

			}
		}
	}*/
	
	if (!v.empty())
	{
		if (isWin == true)
		{
			CClientDC dc(this);
			CBrush red(RGB(255, 0, 0));
			CBrush* rred = dc.SelectObject(&red);
			while (!v.empty())
			{
				a1x = v.front().first;
				a1y = v.front().second;
				v.pop();
				dc.Ellipse((a1y) * 40 + 10 - CIRCLE_SIZE, a1x * 40 - CIRCLE_SIZE, (a1y) * 40 + 10 + CIRCLE_SIZE, a1x * 40 + CIRCLE_SIZE);
			}
			//dc.Ellipse((a1y) * 40 + 10 - CIRCLE_SIZE + 20, a1x * 40 - CIRCLE_SIZE + 20, (a1y) * 40 + 10 + CIRCLE_SIZE + 20, a1x * 40 + CIRCLE_SIZE + 20);
			//dc.Ellipse((a2y) * 40 + 10 - CIRCLE_SIZE + 20, a2x * 40 - CIRCLE_SIZE + 20, (a2y) * 40 + 10 + CIRCLE_SIZE + 20, a2x * 40 + CIRCLE_SIZE + 20);
			//dc.Ellipse((a3y) * 40 + 10 - CIRCLE_SIZE + 20, a3x * 40 - CIRCLE_SIZE + 20, (a3y) * 40 + 10 + CIRCLE_SIZE + 20, a3x * 40 + CIRCLE_SIZE + 20);
			//dc.Ellipse((a4y) * 40 + 10 - CIRCLE_SIZE + 20, a4x * 40 - CIRCLE_SIZE + 20, (a4y) * 40 + 10 + CIRCLE_SIZE + 20, a4x * 40 + CIRCLE_SIZE + 20);
			//dc.Ellipse((a5y) * 40 + 10 - CIRCLE_SIZE + 20, a5x * 40 - CIRCLE_SIZE + 20, (a5y) * 40 + 10 + CIRCLE_SIZE + 20, a5x * 40 + CIRCLE_SIZE + 20);
			dc.SelectObject(rred);

			CString temp;
			if (nowPlayer == 1)
				temp.Format(_T("흰돌 이김"));
			else
				temp.Format(_T("검은돌 이김"));

			AfxMessageBox(temp);

			canPlay = false;

		}
	}



}

ComokDlg::ComokDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OMOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ComokDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ComokDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON1, &ComokDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ComokDlg message handlers
void proc_recvs(ComokDlg* omok) {
	char buffer[PACKET_SIZE] = { 0 };
	//	buffer[2] = color 구분
	//	buffer[3] = winner 구분
	
	while (!WSAGetLastError()) { 
		ZeroMemory(&buffer, PACKET_SIZE);
		recv(skt, buffer, PACKET_SIZE, 0);
		//sign = !sign;
		if (buffer[3] == 0)
		{
			CPoint point;
			int y_index = buffer[1];
			int x_index = buffer[0];
			point.x = 40 * y_index + 10;
			point.y = 40 * x_index;
			CClientDC dc(omok);

			if (point.x >= 0 && point.x <= X_SIZE + 40 && point.y >= 0 && point.y <= Y_SIZE && visited[x_index][y_index] == 0)
			{//visited 확인
				if (buffer[2] == false)
				{
					CBrush black(RGB(0, 0, 0));
					CBrush* bblack = dc.SelectObject(&black);
					dc.Ellipse(point.x - CIRCLE_SIZE, point.y - CIRCLE_SIZE, point.x + CIRCLE_SIZE, point.y + CIRCLE_SIZE);
					dc.SelectObject(bblack);
					visited[x_index][y_index] = 2;
				}
				else if (buffer[2] == true)
				{
					CBrush white(RGB(255, 255, 255));
					CBrush* wwhite = dc.SelectObject(&white);
					dc.Ellipse(point.x - CIRCLE_SIZE, point.y - CIRCLE_SIZE, point.x + CIRCLE_SIZE, point.y + CIRCLE_SIZE);
					dc.SelectObject(wwhite);
					visited[x_index][y_index] = 1;
				}
			}
		}
			else if (buffer[3] == 1)
			{
				CString temp;
				temp.Format(_T("검은돌 이김"));
				AfxMessageBox(temp);
			}
			else if (buffer[3] == 2)
			{
				CString temp;
				temp.Format(_T("흰돌 이김"));
				AfxMessageBox(temp);
			}
		
		

		//sign = !sign;

	}
}
BOOL ComokDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (1) {
		if (!connect(skt, (SOCKADDR*)&addr, sizeof(addr))) break;
	}
	char buffer[PACKET_SIZE] = { 0 };

	ZeroMemory(&buffer, PACKET_SIZE);
	recv(skt, buffer, PACKET_SIZE, 0);
	CMD_LOGIN* login = (CMD_LOGIN*)buffer;

	if (login->color == 1)
		sign = true;

	std::thread proc2(proc_recvs, this);
	proc2.detach();
	//std::thread proc2(proc_recvs);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect m_rectCurHist;
	this->GetWindowRect(m_rectCurHist);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void ComokDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				dc.Rectangle((x) * 40 + 10, (y) * 40, (40 * (x + 1)) + 1 + 10, (40 * (y + 1)) + 1);
			}
		}

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ComokDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







void ComokDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (canPlay)
	{
		point.x = ((point.x + 20) / 40) * 40 + 10;//격 맞춤 
		point.y = ((point.y + 20) / 40) * 40;
		int y_index = (point.x - 10) / 40;
		int x_index = point.y / 40;
		/*
		// TODO: Add your message handler code here and/or call default
		CClientDC dc(this);
		point.x = ((point.x + 20) / 40) * 40 + 10;//격 맞춤 
		point.y = ((point.y + 20) / 40) * 40;
		int y_index = (point.x - 10) / 40;
		int x_index = point.y / 40;
		if (point.x >= 0 && point.x <= X_SIZE + 40 && point.y >= 0 && point.y <= Y_SIZE && visited[x_index][y_index] == 0)
		{
			
			if (sign)
			{
				CBrush black(RGB(0, 0, 0));
				CBrush* bblack = dc.SelectObject(&black);
				dc.Ellipse(point.x - CIRCLE_SIZE, point.y - CIRCLE_SIZE, point.x + CIRCLE_SIZE, point.y + CIRCLE_SIZE);
				dc.SelectObject(bblack);
				visited[x_index][y_index] = 2;

			}
			else
			{
				CBrush white(RGB(255, 255, 255));
				CBrush* wwhite = dc.SelectObject(&white);
				dc.Ellipse(point.x - CIRCLE_SIZE, point.y - CIRCLE_SIZE, point.x + CIRCLE_SIZE, point.y + CIRCLE_SIZE);
				dc.SelectObject(wwhite);
				visited[x_index][y_index] = 1;

			}
		}
		*/
		char buffer[4];
		buffer[0] = x_index;
		buffer[1] = y_index;
		buffer[2] = sign;
		buffer[3] = 0;
		send(skt, buffer, strlen(buffer), 0);
		//checkWin(x_index, y_index);

		CDialogEx::OnLButtonDown(nFlags, point);
	}



}







/*void chekcWin()
{
	int result = 0;

	for (int y = 0; y < Y_SIZE + 1; y++) // 가로
	{
		for (int x = 0; x < X_SIZE + 2 - 5; x++)
		{
			for (int z = 0; z < 5; z++)
			{
				result = result + visited[y][x + z];
				if (result == 5)
				{
					CString temp;

					temp.Format(_T("흰돌 이김"));

					AfxMessageBox(temp);
				}
				else if (result == 10)
				{
					CString temp;

					temp.Format(_T("검은돌 이김"));

					AfxMessageBox(temp);
				}
			}
			result = 0;
		}
	}
	for (int x = 0; x < X_SIZE + 1; x++)// 세로
	{
		for (int y = 0; y < Y_SIZE + 1; y++)
		{
			for (int z = 0; z < 5; z++)
			{
				result = result + visited[y][x + z];
				if (result == 5)
				{
					CString temp;

					temp.Format(_T("흰돌 이김"));

					AfxMessageBox(temp);
				}
				else if (result == 10)
				{
					CString temp;

					temp.Format(_T("검은돌 이김"));

					AfxMessageBox(temp);
				}
			}
			result = 0;
		}
	}
}*/



void ComokDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default

	lpMMI->ptMinTrackSize = CPoint(400, 400);
	lpMMI->ptMaxTrackSize = CPoint(800, 771);
	CDialogEx::OnGetMinMaxInfo(lpMMI);


}


void ComokDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	for (int i = 0; i < Y_SIZE; i++)
	{
		for (int j = 0; j < X_SIZE; j++)
		{
			visited[i][j] = 0;
		}
	}
	Invalidate(TRUE);
	canPlay = true;
}
