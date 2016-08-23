#include "widget.h"
#include "windows.h"
#include "windowsx.h"

#include <QHBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *pushButton = new QPushButton(QStringLiteral("关闭"), this);
    pushButton->setFixedSize(60, 25);
    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(pushButton);

    connect(pushButton, &QPushButton::clicked, this, &Widget::close);
    /* windows flags */
    this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

    /* windows API */
    HWND hwnd = (HWND)this->winId();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

}

Widget::~Widget()
{

}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG* msg = reinterpret_cast<MSG*>(message);

    int xPos = 0, yPos = 0;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos > 0 && xPos < 5)
            *result = HTLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0))
            *result = HTRIGHT;
        if(yPos > 0 && yPos < 5)
            *result = HTTOP;
        if(yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOM;
        if(xPos > 0 && xPos < 5 && yPos > 0 && yPos < 5)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > 0 && yPos < 5)
            *result = HTTOPRIGHT;
        if(xPos > 0 && xPos < 5 && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMRIGHT;

        return true;
        break;

    case WM_GETMINMAXINFO:
        if (::IsZoomed(msg->hwnd)) {

            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else {
            this->setContentsMargins(0, 0, 0, 0);
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        return true;
        break;

    case WM_NCCALCSIZE:
        return true;
        break;
    default:
        return false;
    }
}
