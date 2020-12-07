// encrypt_decrypt.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "encrypt_decrypt.h"
#include "FileIO.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
string getFileName;                             //variable for file name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Encrypt_Decrypt(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ENCRYPTDECRYPT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ENCRYPTDECRYPT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ENCRYPTDECRYPT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ENCRYPTDECRYPT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_FILE_ENCRYPT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Encrypt_Decrypt);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void selectFile(HWND hDlg)
{
    //using commdlg.h library declared in framework.h
    OPENFILENAME ofn;

    char file_name[100];

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hDlg;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = _T("All Files\0*.*\0Text\0*.TXT\0");
    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    getFileName = ofn.lpstrFile;
    SetDlgItemText(hDlg, IDC_EDIT_SELECT, ofn.lpstrFile);
}

void deleteFilePath(string& str, vector<string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of("\\", end)) != string::npos)
    {
        end = str.find("\\", start);
        out.push_back(str.substr(start, end - start));
    }
}

INT_PTR CALLBACK Encrypt_Decrypt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SendDlgItemMessage(hDlg, IDC_COMBO_TYPE, CB_ADDSTRING, 0, (LPARAM)"Caesar Cipher");
        SendDlgItemMessage(hDlg, IDC_COMBO_TYPE, CB_ADDSTRING, 0, (LPARAM)"AES");
        SendDlgItemMessage(hDlg, IDC_COMBO_TYPE, CB_SETCURSEL, 0, 0);
        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON_SELECT)
        {
            selectFile(hDlg);
        }

        if (LOWORD(wParam) == IDC_BUTTON_GO)
        {
            int cbPos = SendDlgItemMessage(hDlg, IDC_COMBO_TYPE, CB_GETCURSEL, 0, 0);

            int key;
            key = GetDlgItemInt(hDlg, IDC_EDIT_KEY, NULL, TRUE);

            if (getFileName == "")
            {
                MessageBox(hDlg, "Select File", "File Error", MB_ICONERROR | MB_OK);
                return (INT_PTR)TRUE;
            }

            char strKey[100];
            GetDlgItemText(hDlg, IDC_EDIT_KEY, strKey, 100);

            if (cbPos == 1) //Caesar Cipher
            {
                if (strcmp(strKey, "") == 0)
                {
                    MessageBox(hDlg, "Enter Key", "Key Error", MB_ICONERROR | MB_OK);
                    return (INT_PTR)TRUE;
                }

                if (IsDlgButtonChecked(hDlg, IDC_RADIO_ENCRYPT))
                {
                    string fileContents = FileIO::readFile(getFileName);

                    CaesarCipher ccEnc(fileContents, key);

                    string fileContentsEncrypted = ccEnc.encrypt();

                    vector<string> fileNameWoPath;
                    deleteFilePath(getFileName, fileNameWoPath);

                    FileIO::writeFile("Encrypted"+fileNameWoPath.back(), fileContentsEncrypted);

                    MessageBox(hDlg, "Encrypted Caesar Cipher successfully", "Encrypt msg", 0);
                }
                else if (IsDlgButtonChecked(hDlg, IDC_RADIO_DECRYPT))
                {
                    string fileContents = FileIO::readFile(getFileName);

                    CaesarCipher ccEnc(fileContents, key);

                    string fileContentsDecrypted = ccEnc.decrypt();

                    vector<string> fileNameWoPath;
                    deleteFilePath(getFileName, fileNameWoPath);

                    FileIO::writeFile("Decrypted"+ fileNameWoPath.back(), fileContentsDecrypted);

                    MessageBox(hDlg, "Decrypted Caesar Cipher successfully", "Decrypt msg", 0);
                }
            }
            else if (cbPos == 0) //AES 
            {
                if (IsDlgButtonChecked(hDlg, IDC_RADIO_ENCRYPT))
                {
                    string fileContents = FileIO::readFile(getFileName);

                    vector<string> fileContentsEncrypted = cAES::encryptAES(fileContents);

                    FileIO::writeFile("Key.txt", fileContentsEncrypted.at(0));
                    FileIO::writeFile("IV.txt", fileContentsEncrypted.at(1));

                    vector<string> fileNameWoPath;
                    deleteFilePath(getFileName, fileNameWoPath);

                    FileIO::writeFile("Encrypted" + fileNameWoPath.back(), fileContentsEncrypted.at(2));

                    MessageBox(hDlg, "Encrypted AES successfully", "Encrypt msg", 0);
                }
                else if (IsDlgButtonChecked(hDlg, IDC_RADIO_DECRYPT))
                {

                    char getKey[100], getIV[100];
                    GetDlgItemText(hDlg, IDC_EDIT_KEY, getKey, 100);
                    GetDlgItemText(hDlg, IDC_EDIT_IV, getIV, 100);

                    if (strcmp(getKey, "") == 0)
                    {
                        MessageBox(hDlg, "Enter Key", "Key Error", MB_ICONERROR | MB_OK);
                        return (INT_PTR)TRUE;
                    }

                    if (strcmp(getIV, "") == 0)
                    {
                        MessageBox(hDlg, "Enter IV", "IV Error", MB_ICONERROR | MB_OK);
                        return (INT_PTR)TRUE;
                    }

                    string strGetKey(getKey);
                    string strGetIV(getIV);

                    string convertKeyToByte, convertIVToByte;
                    StringSource ss1(strGetKey, true, new HexDecoder(new StringSink(convertKeyToByte)));
                    const byte* bGetKey = (const byte*)convertKeyToByte.data();
                    StringSource ss2(strGetIV, true, new HexDecoder(new StringSink(convertIVToByte)));
                    const byte* bGetIV = (const byte*)convertIVToByte.data();

                    string fileContents = FileIO::readFile(getFileName);

                    string fileContentsDecrypted = cAES::decryptAES(fileContents, bGetKey, bGetIV);

                    vector<string> fileNameWoPath;
                    deleteFilePath(getFileName, fileNameWoPath);

                    FileIO::writeFile("Decrypted" + fileNameWoPath.back(), fileContentsDecrypted);

                    MessageBox(hDlg, "Decrypted AES successfully", "Decrypt msg", 0);
                }
            }
            
            
        }

        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
