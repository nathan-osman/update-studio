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

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <Windows.h>

/**
 * @brief UI for showing update progress
 */
class UpdateDialog
{
public:

    UpdateDialog(LPCWSTR url, LPCWSTR filename);
    ~UpdateDialog();

    /**
     * @brief Display the dialog and wait for completion
     * @return true if the update succeeded
     */
    bool exec();

private:

    static INT_PTR CALLBACK sDialogProc(HWND hwndDialog,
                                        UINT message,
                                        WPARAM wParam,
                                        LPARAM lParam);

    INT_PTR dialogProc(HWND hwndDialog,
                       UINT message,
                       WPARAM wParam,
                       LPARAM lParam);

    void center();
    void createProgressBar();

    HWND mHwnd;
    HWND mHwndProgress;

    PWSTR mUrl;
    PWSTR mFilename;
};

#endif // UPDATEDIALOG_H
