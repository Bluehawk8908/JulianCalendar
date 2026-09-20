// JulCalendar.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "JulCalendar.h"
#include <string>

#define MAX_LOADSTRING 100
#define CALC_OLD_TO_NEW 110
#define CALC_NEW_TO_OLD 111
#define TODAYS_DATE 112

void CalculateOldToNew();
void CalculateNewToOld();
void TodaysDate();

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hOldDay, hOldMonth, hOldYear;                                  // handlers for text boxes
HWND hNewDay, hNewMonth, hNewYear;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_JULCALENDAR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JULCALENDAR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JULCALENDAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JULCALENDAR);
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
      CW_USEDEFAULT, 0, 500, 400, nullptr, nullptr, hInstance, nullptr);

   
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
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case CALC_OLD_TO_NEW:
                CalculateOldToNew();
                break;
            case CALC_NEW_TO_OLD:
                CalculateNewToOld();
                break;
            case TODAYS_DATE:
                TodaysDate();
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            std::string labelJC = "Julian Calendar Date (Old Style):";
            std::string labelGC = "Gregorian Calendar Date (New Style):";

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(1));

            RECT rectLabel1 = { 15, 15, 300, 45 };
            DrawTextA(hdc, labelJC.c_str(), -1, &rectLabel1, DT_LEFT);
            hOldDay = CreateWindowA("edit", "dd", WS_VISIBLE | WS_CHILD | WS_BORDER, 15, 35, 30, 20, hWnd, NULL, NULL, NULL);
            hOldMonth = CreateWindowA("edit", "mm", WS_VISIBLE | WS_CHILD | WS_BORDER, 48, 35, 75, 20, hWnd, NULL, NULL, NULL);
            hOldYear = CreateWindowA("edit", "yyyy", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 35, 45, 20, hWnd, NULL, NULL, NULL);

            RECT rectLabel2 = { 15, 60, 300, 90 };
            DrawTextA(hdc, labelGC.c_str(), -1, &rectLabel2, DT_LEFT);
            hNewDay = CreateWindowA("edit", "dd", WS_VISIBLE | WS_CHILD | WS_BORDER, 15, 80, 30, 20, hWnd, NULL, NULL, NULL);
            hNewMonth = CreateWindowA("edit", "mm", WS_VISIBLE | WS_CHILD | WS_BORDER, 48, 80, 75, 20, hWnd, NULL, NULL, NULL);
            hNewYear = CreateWindowA("edit", "yyyy", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 80, 45, 20, hWnd, NULL, NULL, NULL);
            
            CreateWindowA("button", "Old to New", WS_VISIBLE | WS_CHILD | WS_BORDER, 15, 105, 80, 40, hWnd, (HMENU)CALC_OLD_TO_NEW, NULL, NULL);
            CreateWindowA("button", "New to Old", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 105, 80, 40, hWnd, (HMENU)CALC_NEW_TO_OLD, NULL, NULL);
            CreateWindowA("button", "Today's Date", WS_VISIBLE | WS_CHILD | WS_BORDER, 185, 105, 95, 40, hWnd, (HMENU)TODAYS_DATE, NULL, NULL);


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

void CalculateOldToNew() {
    char oldDayRaw[3], oldMonthRaw[10], oldYearRaw[5], newDayOutput[3], newYearOutput[5];
    int oldDay, oldMonth, oldYear, newDay, newMonth, newYear;
    int monthSize, dayOffset;
    
    GetWindowTextA(hOldDay, oldDayRaw, 3);
    GetWindowTextA(hOldMonth, oldMonthRaw, 10);
    GetWindowTextA(hOldYear, oldYearRaw, 5);
    
    if (oldDayRaw[1] != 0) {
        oldDay = (oldDayRaw[0] - 48) * 10;
        oldDay += oldDayRaw[1] - 48;
    }
    else {
        oldDay = oldDayRaw[0] - 48;
    }
    
    oldYear = (oldYearRaw[0] - 48) * 1000;
    oldYear += (oldYearRaw[1] - 48) * 100;
    oldYear += (oldYearRaw[2] - 48) * 10;
    oldYear += (oldYearRaw[3] - 48);
    
    if ((oldMonthRaw[0] == 'J' || oldMonthRaw[0] == 'j') && oldMonthRaw[1] == 'a')
        oldMonth = 1;
    else if (oldMonthRaw[0] == 'F' || oldMonthRaw[0] == 'f')
        oldMonth = 2;
    else if ((oldMonthRaw[0] == 'M' || oldMonthRaw[0] == 'm') && oldMonthRaw[1] == 'a' && oldMonthRaw[2] == 'r')
        oldMonth = 3;
    else if ((oldMonthRaw[0] == 'A' || oldMonthRaw[0] == 'a') && oldMonthRaw[1] == 'p')
        oldMonth = 4;
    else if ((oldMonthRaw[0] == 'M' || oldMonthRaw[0] == 'm') && oldMonthRaw[1] == 'a' && oldMonthRaw[2] == 'y')
        oldMonth = 5;
    else if ((oldMonthRaw[0] == 'J' || oldMonthRaw[0] == 'j') && oldMonthRaw[1] == 'u' && oldMonthRaw[2] == 'n')
        oldMonth = 6;
    else if ((oldMonthRaw[0] == 'J' || oldMonthRaw[0] == 'j') && oldMonthRaw[1] == 'u' && oldMonthRaw[2] == 'l')
        oldMonth = 7;
    else if ((oldMonthRaw[0] == 'A' || oldMonthRaw[0] == 'a') && oldMonthRaw[1] == 'u')
        oldMonth = 8;
    else if (oldMonthRaw[0] == 'S' || oldMonthRaw[0] == 's')
        oldMonth = 9;
    else if (oldMonthRaw[0] == 'O' || oldMonthRaw[0] == 'o')
        oldMonth = 10;
    else if (oldMonthRaw[0] == 'N' || oldMonthRaw[0] == 'n')
        oldMonth = 11;
    else if (oldMonthRaw[0] == 'D' || oldMonthRaw[0] == 'd')
        oldMonth = 12;
    else {
        MessageBeep(MB_OK);
        return;
    }
    
    switch (oldMonth) {
    case 2:
        if (oldYear % 4 == 0 && oldYear % 100 != 0 || oldYear % 400 == 0) //leap year rules
            monthSize = 29;
        else
            monthSize = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        monthSize = 30;
        break;
    default:
        monthSize = 31;
        break;
    }
    
    if (oldDay < 1 || oldDay > monthSize) { //guards against nonsense data entries
        MessageBeep(MB_OK);
        return;
    }

    if (oldYear < 1700 || oldYear > 2199){
        MessageBeep(MB_OK);
        return;
    }

    if ((oldYear >= 1700 && oldYear < 1800) || ((oldYear == 1800 && oldMonth == 1) || (oldYear == 1800 && oldMonth == 2 && oldDay >= 18))) //calendar discrepancy increases by a day every century on a drifting date
        dayOffset = 11;
    else if ((oldYear >= 1800 && oldYear < 1900) || ((oldYear == 1900 && oldMonth == 1) || (oldYear == 1900 && oldMonth == 2 && oldDay >= 17)))
        dayOffset = 12;
    else if ((oldYear >= 1900 && oldYear < 2100) || ((oldYear == 2100 && oldMonth == 1) || (oldYear == 2100 && oldMonth == 2 && oldDay >= 16))) //discrepenacy hangs by 1 for the 21st century
        dayOffset = 13;
    else
        dayOffset = 14;

    if (oldDay + dayOffset > monthSize){
        newDay = oldDay + dayOffset - monthSize;
        newMonth = oldMonth + 1;
        if (newMonth == 13) {
            newMonth = 1;
            newYear = oldYear + 1;
        } else
            newYear = oldYear;
    }
    else {
        newYear = oldYear;
        newMonth = oldMonth;
        newDay = oldDay + dayOffset;
    }

    if (newDay > 9){                        //converting int to char array by digits
        newDayOutput[0] = newDay / 10 + 48;
        newDayOutput[1] = newDay - ((newDay / 10) * 10) + 48;
    }
    else{
        newDayOutput[0] = newDay + 48;
        newDayOutput[1] = NULL;
    }

    newDayOutput[2] = NULL;

    switch (newMonth) {
    case 1:
        SetWindowTextA(hNewMonth, "January");
        break;
    case 2:
        SetWindowTextA(hNewMonth, "February");
        break;
    case 3:
        SetWindowTextA(hNewMonth, "March");
        break;
    case 4:
        SetWindowTextA(hNewMonth, "April");
        break;
    case 5:
        SetWindowTextA(hNewMonth, "May");
        break;
    case 6:
        SetWindowTextA(hNewMonth, "June");
        break;
    case 7:
        SetWindowTextA(hNewMonth, "July");
        break;
    case 8:
        SetWindowTextA(hNewMonth, "August");
        break;
    case 9:
        SetWindowTextA(hNewMonth, "September");
        break;
    case 10:
        SetWindowTextA(hNewMonth, "October");
        break;
    case 11:
        SetWindowTextA(hNewMonth, "November");
        break;
    default:
        SetWindowTextA(hNewMonth, "December");
        break;
    }

    if (newYear > 2000 && newYear < 2100){  //converting int back into chars digit by digit
        newYearOutput[0] = '2';
        newYearOutput[1] = '0';
        newYear -= 2000;
        if (newYear < 9) {
            newYearOutput[2] = '0';
            newYearOutput[3] = newYear + 48;
        }
        else {
            newYearOutput[1] = (newYear / 100) + 48;
            newYear -= (newYear / 100) * 100;
            newYearOutput[2] = (newYear / 10) + 48;
            newYear -= (newYear / 10) * 10;
            newYearOutput[3] = newYear + 48;
        }        
    }
    else {
        newYearOutput[0] = (newYear / 1000) + 48;
        newYear -= (newYear / 1000) * 1000;
        newYearOutput[1] = (newYear / 100) + 48;
        newYear -= (newYear / 100) * 100;
        newYearOutput[2] = (newYear / 10) + 48;
        newYear -= (newYear / 10) * 10;
        newYearOutput[3] = newYear + 48;         
    }

    newYearOutput[4] = NULL;

    SetWindowTextA(hNewDay, newDayOutput);    
    SetWindowTextA(hNewYear, newYearOutput);
};

void CalculateNewToOld() {
    char newDayRaw[3], newMonthRaw[10], newYearRaw[5], oldDayOutput[3], oldYearOutput[5];
    int newDay, newMonth, newYear, oldDay, oldMonth, oldYear;
    int monthSize, dayOffset;

    GetWindowTextA(hNewDay, newDayRaw, 3);
    GetWindowTextA(hNewMonth, newMonthRaw, 10);
    GetWindowTextA(hNewYear, newYearRaw, 5);

    if (newDayRaw[1] != 0) {
        newDay = (newDayRaw[0] - 48) * 10;
        newDay += newDayRaw[1] - 48;
    }
    else
        newDay = newDayRaw[0] - 48;

    newYear = (newYearRaw[0] - 48) * 1000;
    newYear += (newYearRaw[1] - 48) * 100;
    newYear += (newYearRaw[2] - 48) * 10;
    newYear += (newYearRaw[3] - 48);

    if ((newMonthRaw[0] == 'J' || newMonthRaw[0] == 'j') && newMonthRaw[1] == 'a')
        newMonth = 1;
    else if (newMonthRaw[0] == 'F' || newMonthRaw[0] == 'f')
        newMonth = 2;
    else if ((newMonthRaw[0] == 'M' || newMonthRaw[0] == 'm') && newMonthRaw[1] == 'a' && newMonthRaw[2] == 'r')
        newMonth = 3;
    else if ((newMonthRaw[0] == 'A' || newMonthRaw[0] == 'a') && newMonthRaw[1] == 'p')
        newMonth = 4;
    else if ((newMonthRaw[0] == 'M' || newMonthRaw[0] == 'm') && newMonthRaw[1] == 'a' && newMonthRaw[2] == 'y')
        newMonth = 5;
    else if ((newMonthRaw[0] == 'J' || newMonthRaw[0] == 'j') && newMonthRaw[1] == 'u' && newMonthRaw[2] == 'n')
        newMonth = 6;
    else if ((newMonthRaw[0] == 'J' || newMonthRaw[0] == 'j') && newMonthRaw[1] == 'u' && newMonthRaw[2] == 'l')
        newMonth = 7;
    else if ((newMonthRaw[0] == 'A' || newMonthRaw[0] == 'a') && newMonthRaw[1] == 'u')
        newMonth = 8;
    else if (newMonthRaw[0] == 'S' || newMonthRaw[0] == 's')
        newMonth = 9;
    else if (newMonthRaw[0] == 'O' || newMonthRaw[0] == 'o')
        newMonth = 10;
    else if (newMonthRaw[0] == 'N' || newMonthRaw[0] == 'n')
        newMonth = 11;
    else if (newMonthRaw[0] == 'D' || newMonthRaw[0] == 'd')
        newMonth = 12;
    else {
        MessageBeep(MB_OK);
        return;
    }

    newMonth--; //we need to know the size of the PREVIOUS month for our subtraction 
    if (newMonth == 0)
        newMonth = 12;

    switch (newMonth) {
    case 2:
        if (newYear % 4 == 0 && newYear % 100 != 0 || newYear % 400 == 0) //leap year rules
            monthSize = 29;
        else
            monthSize = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        monthSize = 30;
        break;
    default:
        monthSize = 31;
        break;
    }

    if (newDay < 1 || newDay > monthSize) { //guards against nonsense data
        MessageBeep(MB_OK);
        return;
    }

    if (newYear < 1700 || newYear > 2199) {
        MessageBeep(MB_OK);
        return;
    }

    if ((newYear >= 1700 && newYear < 1800) || (newYear == 1800 && newMonth < 3)) //calendar discrepancy increases by a day every century on the 1st of March
        dayOffset = 11;
    else if ((newYear >= 1800 && newYear < 1900) || (newYear == 1900 && newMonth < 3))
        dayOffset = 12;
    else if ((newYear >= 1900 && newYear < 2100) || (newYear == 2100 && newMonth < 3)) //discrepenacy hangs by 1 for the 21st century
        dayOffset = 13;
    else
        dayOffset = 14;

    if (newDay - dayOffset < 0) {
        oldDay = newDay - dayOffset + monthSize;
        oldMonth = newMonth;
        if (oldMonth == 12) {
            oldYear = newYear - 1;
        }
        else
            oldYear = newYear;
    }
    else {
        oldYear = newYear;
        oldMonth = newMonth + 1;
        oldDay = newDay - dayOffset;
    }

    if (oldDay > 9) {                        //converting int to char array by digits
        oldDayOutput[0] = oldDay / 10 + 48;
        oldDayOutput[1] = oldDay - ((oldDay / 10) * 10) + 48;
    }
    else {
        oldDayOutput[0] = oldDay + 48;
        oldDayOutput[1] = NULL;
    }
    oldDayOutput[2] = NULL;

    switch (oldMonth) {
    case 1:
        SetWindowTextA(hOldMonth, "January");
        break;
    case 2:
        SetWindowTextA(hOldMonth, "February");
        break;
    case 3:
        SetWindowTextA(hOldMonth, "March");
        break;
    case 4:
        SetWindowTextA(hOldMonth, "April");
        break;
    case 5:
        SetWindowTextA(hOldMonth, "May");
        break;
    case 6:
        SetWindowTextA(hOldMonth, "June");
        break;
    case 7:
        SetWindowTextA(hOldMonth, "July");
        break;
    case 8:
        SetWindowTextA(hOldMonth, "August");
        break;
    case 9:
        SetWindowTextA(hOldMonth, "September");
        break;
    case 10:
        SetWindowTextA(hOldMonth, "October");
        break;
    case 11:
        SetWindowTextA(hOldMonth, "November");
        break;
    default:
        SetWindowTextA(hOldMonth, "December");
        break;
    }

    if (oldYear > 2000 && oldYear < 2100) { //converting int back into chars digit by digit
        oldYearOutput[0] = '2';
        oldYearOutput[1] = '0';
        oldYear -= 2000;
        if (oldYear < 9) {
            oldYearOutput[2] = '0';
            oldYearOutput[3] = newYear + 48;
        }
        else {
            oldYearOutput[1] = (oldYear / 100) + 48;
            oldYear -= (oldYear / 100) * 100;
            oldYearOutput[2] = (oldYear / 10) + 48;
            oldYear -= (oldYear / 10) * 10;
            oldYearOutput[3] = oldYear + 48;
        }
    }
    else {
        oldYearOutput[0] = (oldYear / 1000) + 48;
        oldYear -= (oldYear / 1000) * 1000;
        oldYearOutput[1] = (oldYear / 100) + 48;
        oldYear -= (oldYear / 100) * 100;
        oldYearOutput[2] = (oldYear / 10) + 48;
        oldYear -= (oldYear / 10) * 10;
        oldYearOutput[3] = oldYear + 48;
    }

    oldYearOutput[4] = NULL;

    SetWindowTextA(hOldDay, oldDayOutput);
    SetWindowTextA(hOldYear, oldYearOutput);
};

void TodaysDate() {
    char usersDate[9], currentDay[3], currentYear[5];
    int currentMonth = 0;
    GetDateFormatA(0, 0, NULL, "ddMMyyyy", usersDate, sizeof(usersDate));

    currentDay[0] = usersDate[0];
    currentDay[1] = usersDate[1];
    currentDay[2] = NULL;

    currentMonth = (usersDate[2] - 48) * 10;
    currentMonth += usersDate[3] - 48;

    switch (currentMonth) {
    case 1:    
        SetWindowTextA(hNewMonth, "January");
        break;
    case 2:
        SetWindowTextA(hNewMonth, "February");
        break;
    case 3:
        SetWindowTextA(hNewMonth, "March");
        break;
    case 4:
        SetWindowTextA(hNewMonth, "April");
        break;
    case 5:
        SetWindowTextA(hNewMonth, "May");
        break;
    case 6:
        SetWindowTextA(hNewMonth, "June");
        break;
    case 7:
        SetWindowTextA(hNewMonth, "July");
        break;
    case 8:
        SetWindowTextA(hNewMonth, "August");
        break;
    case 9:
        SetWindowTextA(hNewMonth, "September");
        break;
    case 10:
        SetWindowTextA(hNewMonth, "October");
        break;
    case 11:
        SetWindowTextA(hNewMonth, "November");
        break;
    default:
        SetWindowTextA(hNewMonth, "December");
        break;
    }

    currentYear[0] = usersDate[4];
    currentYear[1] = usersDate[5];
    currentYear[2] = usersDate[6];
    currentYear[3] = usersDate[7];
    currentYear[4] = NULL;

    SetWindowTextA(hNewDay, currentDay);
    SetWindowTextA(hNewYear, currentYear);

    CalculateNewToOld();
}