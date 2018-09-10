#include "UASQuickViewTextItem.h"
#include "logging.h"
#include <QVBoxLayout>
#include <math.h>

UASQuickViewTextItem::UASQuickViewTextItem(QWidget *parent) : UASQuickViewItem(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);
    titleLabel = new UASQuickViewTextLabel(this);
    //titleLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    this->layout()->addWidget(titleLabel);
    valueLabel = new UASQuickViewTextLabel(this);
    //valueLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    valueLabel->setText("0.00");
    this->layout()->addWidget(valueLabel);
    //spacerItem = new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Ignored);
    //layout->addSpacerItem(spacerItem);
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(this->height() / 2.0);
    titlefont.setPixelSize(this->height() / 4.0);
    valueLabel->setFontSize(this->height() / 2.0);
    titleLabel->setFontSize(this->height() / 4.0);
    // use golden ratio for evenly distributed colors	     // 균등하게 분포 된 색상에 황금 비율 사용  
    double golden_ratio_conjugate = 0.618033988749895;
    double h = ((double)rand() / (double)(RAND_MAX));
    h = h + golden_ratio_conjugate;
    h = fmod(h, 1.0);     // hue, 0.0 - 1.0
    double s = 0.75;    // saturation, the bigger it is, the stronger the color is	 채도가 크면 클수록 색상이 강해집니다.  
    double v = 0.8516;  // value, represents lightness or brightness, 0 is black	 값은 밝기 또는 밝기를 나타내며 0은 검정색입니다.  
    QColor color = QColor::fromHsvF(h, s, v);
    titleLabel->setFontColor(color);
    valueLabel->setFontColor(color);
}

QString UASQuickViewTextItem::value()
{
    return valueLabel->text();
}

QString UASQuickViewTextItem::title()
{
    return titleLabel->text();
}

void UASQuickViewTextItem::setValue(double value)
{

    //Lon/Lat needs 7 decimal places, everything else should be scaled by value.	 Lon / Lat에는 소수점 7 자리가 필요합니다. 나머지는 값으로 조정해야합니다.  
    if ((titleLabel->text().toLower() == "longitude") ||
            (titleLabel->text().toLower() == "latitude") ||
            (titleLabel->text().toLower() == "lon") ||
            (titleLabel->text().toLower() == "lat"))
    {
        valueLabel->setText(QString::number(value,'f',7));
        return;
    }
    if (value < 10 && value > -10)
    {
        valueLabel->setText(QString::number(value,'f',2));
    }
    else if (value < 100 && value > -100)
    {
        valueLabel->setText(QString::number(value,'f',2));
    }
    else if (value < 1000 && value > -1000)
    {
        valueLabel->setText(QString::number(value,'f',1));
    }
    else if (value < 10000 && value > -10000)
    {
        valueLabel->setText(QString::number(value,'f',1));
    }
    else
    {
        valueLabel->setText(QString::number(value,'f',0));
    }
}

void UASQuickViewTextItem::setTitle(QString title)
{
    if (title.indexOf("."))
    {
        titleLabel->setText(title.mid(title.indexOf(".")+1));
    }
    else
    {
        titleLabel->setText(title);
    }
}
int UASQuickViewTextItem::minValuePixelSize()
{
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(this->height());
    titlefont.setPixelSize(valuefont.pixelSize() / 1.3);
    //spacerItem->setGeometry(QRect(0,0,20,this->height()/10.0));

    QFontMetrics metrics(valuefont);
    //valuefont.setPixelSize(this->height() / 2.0);
    bool fit = false;
    while (!fit)
    {

        QFontMetrics valfm( valuefont );
        QRect valbound = valfm.boundingRect(0,0, valueLabel->width(), valueLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, "45678.00"/*valueLabel->text()*/);
        //QFontMetrics titlefm( titlefont );
        //QRect titlebound = titlefm.boundingRect(0,0, titleLabel->width(), titleLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, titleLabel->text());

        if ((valbound.width() <= valueLabel->width() && valbound.height() <= valueLabel->height()))// && (titlebound.width() <= titleLabel->width() && titlebound.height() <= titleLabel->height()))
            fit = true;
        else
        {
            if (valuefont.pixelSize()-5 <= 0)
            {
                fit = true;
                valuefont.setPixelSize(5);
            }
            else
            {
                valuefont.setPixelSize(valuefont.pixelSize() - 5);
            }
            //titlefont.setPixelSize(valuefont.pixelSize() / 2.0);
            QLOG_TRACE() << "Point size:" << valuefont.pixelSize() << valueLabel->width() << valueLabel->height();
        }
    }
    return valuefont.pixelSize();
}
void UASQuickViewTextItem::setValuePixelSize(int size)
{
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(size);
    titlefont.setPixelSize(valuefont.pixelSize() / 1.6);
    valueLabel->setFontSize(size);
    titleLabel->setFontSize(size / 1.6);
    update();
}

void UASQuickViewTextItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    return;
    QFont valuefont = valueLabel->font();
    QFont titlefont = titleLabel->font();
    valuefont.setPixelSize(this->height());
    titlefont.setPixelSize(valuefont.pixelSize() / 1.6);
    //spacerItem->setGeometry(QRect(0,0,20,this->height()/10.0));

    QFontMetrics metrics(valuefont);
    //valuefont.setPixelSize(this->height() / 2.0);
    bool fit = false;
    while (!fit)
    {

        QFontMetrics valfm( valuefont );
        QRect valbound = valfm.boundingRect(0,0, valueLabel->width(), valueLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, valueLabel->text());
        //QFontMetrics titlefm( titlefont );
        //QRect titlebound = titlefm.boundingRect(0,0, titleLabel->width(), titleLabel->height(), Qt::TextWordWrap | Qt::AlignLeft, titleLabel->text());

        if ((valbound.width() <= valueLabel->width() && valbound.height() <= valueLabel->height()))// && (titlebound.width() <= titleLabel->width() && titlebound.height() <= titleLabel->height()))
            fit = true;
        else
        {
            if (valuefont.pixelSize()-5 <= 0)
            {
                fit = true;
                valuefont.setPixelSize(5);
            }
            else
            {
                valuefont.setPixelSize(valuefont.pixelSize() - 5);
            }
            //titlefont.setPixelSize(valuefont.pixelSize() / 2.0);
            QLOG_TRACE() << "Point size:" << valuefont.pixelSize() << valueLabel->width() << valueLabel->height();
        }
    }
titlefont.setPixelSize(valuefont.pixelSize() / 1.8);
    valueLabel->setFont(valuefont);
    titleLabel->setFont(titlefont);
    update();
}
