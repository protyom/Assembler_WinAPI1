#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

unsigned int* A;
char seps[] = " ,\t\n";
char* str;
extern "C" unsigned __stdcall AllDoubPalindroms(unsigned*, unsigned);
extern "C" unsigned __cdecl AllDoubPalindroms1(unsigned*, unsigned);
extern "C" unsigned __fastcall AllDoubPalindroms2(unsigned*, unsigned);
HINSTANCE hInst = 0;

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	hInst = hInstance;
	HWND hMDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	ShowWindow(hMDialog, SW_SHOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hMDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static unsigned int res1;
	char temp[6];
	static HWND hEdit;
	int i=0;
	int size,size_str;
	char* token;
	switch (uMsg) {
	case WM_INITDIALOG:
		_itoa_s(1,temp,10);
		SetDlgItemInt(hDlg, IDC_EDIT2, 10, FALSE);
		hEdit = GetDlgItem(hDlg, IDC_EDIT3);
		A = new unsigned int(10);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COUNT: {
			/*A[0] = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			A[1] = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			A[2] = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			A[3] = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			A[4] = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
			A[5] = GetDlgItemInt(hDlg, IDC_EDIT6, NULL, FALSE);
			A[6] = GetDlgItemInt(hDlg, IDC_EDIT7, NULL, FALSE);
			A[7] = GetDlgItemInt(hDlg, IDC_EDIT8, NULL, FALSE);
			A[8] = GetDlgItemInt(hDlg, IDC_EDIT9, NULL, FALSE);
			A[9] = GetDlgItemInt(hDlg, IDC_EDIT10, NULL, FALSE);
			res1 = AllDoubPalindroms2(A, 10);*/
			size = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			delete[] A;
			A = new unsigned int[size];
			size_str = GetWindowTextLength(hEdit);
			str = new char[size_str];
			GetDlgItemText(hDlg, IDC_EDIT3, str, size_str);
			token = strtok(str, seps);
			int i = 0;
			while (token != NULL && i < size)
			{
				A[i] = atoi(token);
				token = strtok(NULL, seps);
				i++;
			}
			for (i; i < size; i++)
				A[i] = 0;
			res1 = AllDoubPalindroms(A, size);
			if (res1 != size + 1)
				SetDlgItemInt(hDlg, IDC_EDIT11, A[res1], FALSE);
			else
				SetDlgItemText(hDlg, IDC_EDIT11, "No result");
			return TRUE;
		}
		case ID_EXIT:
			PostQuitMessage(0);
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}