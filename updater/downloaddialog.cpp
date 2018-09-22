/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>

#include "downloaddialog.h"
#include "resource.h"

DownloadDialog::DownloadDialog(LPCWSTR url, LPCWSTR filename)
    : mHwnd(nullptr),
      mHwndProgress(nullptr),
      mUrl(StrDupW(url)),
      mFilename(StrDupW(filename))
{
}

DownloadDialog::~DownloadDialog()
{
    LocalFree(mUrl);
    LocalFree(mFilename);
}

bool DownloadDialog::exec()
{
    DialogBoxParamW(nullptr,
                    MAKEINTRESOURCEW(ID_DOWNLOADDIALOG),
                    nullptr,
                    sDialogProc,
                    reinterpret_cast<LPARAM>(this));

    return false;
}

INT_PTR DownloadDialog::sDialogProc(HWND hwndDialog,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    // Check to see if a pointer to the instance can be retrieved from the
    // user data in the HWND
    DownloadDialog *downloadDialog = reinterpret_cast<DownloadDialog*>(
                GetWindowLongW(hwndDialog, GWLP_USERDATA));

    // If not, and the message is WM_INITDIALOG, the pointer is in lParam;
    // store a copy in the HWND for later
    if (!downloadDialog && message == WM_INITDIALOG) {
        downloadDialog = reinterpret_cast<DownloadDialog*>(lParam);
        downloadDialog->mHwnd = hwndDialog;
        SetWindowLongW(hwndDialog, GWLP_USERDATA, static_cast<LONG>(lParam));
    }

    // Invoke the instance's proc if available
    if (downloadDialog) {
        return downloadDialog->dialogProc(hwndDialog, message, wParam, lParam);
    }

    return FALSE;
}

INT_PTR DownloadDialog::dialogProc(HWND hwndDialog,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    {
        center();
        createProgressBar();
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_CANCEL:
            EndDialog(hwndDialog, ID_CANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

void DownloadDialog::center()
{
    // Determine the dimensions of the primary display
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Grab the width and height of the dialog
    RECT rect;
    GetWindowRect(mHwnd, &rect);
    LONG dialogWidth = rect.right - rect.left;
    LONG dialogHeight = rect.bottom - rect.top;

    SetWindowPos(mHwnd,
                 HWND_TOP,
                 screenWidth / 2 - dialogWidth / 2,
                 screenHeight / 2 - dialogHeight / 2,
                 0, 0,
                 SWP_NOSIZE);
}

void DownloadDialog::createProgressBar()
{
    // Map dialog coordinates to screen coordinates
    RECT rect = {10, 25, 290, 40};
    MapDialogRect(mHwnd, &rect);

    // Create the progress bar
    mHwndProgress = CreateWindowExW(0,
                                    PROGRESS_CLASSW,
                                    nullptr,
                                    WS_CHILD | WS_VISIBLE,
                                    rect.left, rect.top,
                                    rect.right - rect.left,
                                    rect.bottom - rect.top,
                                    mHwnd,
                                    nullptr,
                                    nullptr,
                                    nullptr);
}
