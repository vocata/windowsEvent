#pragma comment(lib, "User32.lib")
#include "widget.h"
#include "windows.h"
#include "windowsx.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

    HWND hwnd = (HWND)this->winId();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

}

Widget::~Widget()
{

}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);

    int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
    int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
    switch(msg->message)
    {
    case WM_NCHITTEST:

        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos > 18 && xPos < 22)
            *result = HTLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18))
            *result = HTRIGHT;
        if(yPos > 18 && yPos < 22)
            *result = HTTOP;
        if(yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOM;
        if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
            *result = HTTOPRIGHT;
        if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
            *result = HTBOTTOMRIGHT;

        return true;
        break;

    case WM_NCCALCSIZE:
            return true;
    }
    return false;
}
