#include "playercardbox.h"
#include "clientplayer.h"
#include "skin-bank.h"
#include "engine.h"
#include "carditem.h"
#include "client.h"
#include "clientstruct.h"
#include "timed-progressbar.h"

#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>

static QChar handcardFlag('h');
static QChar equipmentFlag('e');
static QChar judgingFlag('j');

const int PlayerCardBox::maxCardNumberInOneRow = 10;

const int PlayerCardBox::verticalBlankWidth = 37;
const int PlayerCardBox::placeNameAreaWidth = 15;
const int PlayerCardBox::intervalBetweenNameAndCard = 20;
const int PlayerCardBox::topBlankWidth = 42;
const int PlayerCardBox::bottomBlankWidth = 25;
const int PlayerCardBox::intervalBetweenAreas = 10;
const int PlayerCardBox::intervalBetweenRows = 5;
const int PlayerCardBox::intervalBetweenCards = 3;

PlayerCardBox::PlayerCardBox()
    : player(NULL), progressBar(NULL),
    rowCount(0), intervalsBetweenAreas(-1), intervalsBetweenRows(0), maxCardsInOneRow(0)
{
}

void PlayerCardBox::chooseCard(const QString &reason, const ClientPlayer *player,
    const QString &flags, bool handcardVisible,
    Card::HandlingMethod method, const QList<int> &disabledIds, const QList<int> &handcards)
{
    nameRects.clear();
    rowCount = 0;
    intervalsBetweenAreas = -1;
    intervalsBetweenRows = 0;
    maxCardsInOneRow = 0;

    this->handcards = handcards;
    this->player = player;
    this->title = tr("%1: please choose %2's card").arg(reason).arg(ClientInstance->getPlayerName(player->objectName()));
    this->flags = flags;
    bool handcard = false;
    bool equip = false;
    bool judging = false;

    if (flags.contains(handcardFlag) && !player->isKongcheng()) {
        updateNumbers(player->getHandcardNum());
        handcard = true;
    }

    if (flags.contains(equipmentFlag) && player->hasEquip()) {
        updateNumbers(player->getEquips().length());
        equip = true;
    }

    if (flags.contains(judgingFlag) && !player->getJudgingArea().isEmpty()) {
        updateNumbers(player->getJudgingArea().length());
        judging = true;
    }

    int max = maxCardsInOneRow;
    int maxNumber = maxCardNumberInOneRow;
    maxCardsInOneRow = qMin(max, maxNumber);

    prepareGeometryChange();

    moveToCenter();
    show();

    this->handcardVisible = handcardVisible;
    this->method = method;
    this->disabledIds = disabledIds;

    const int startX = verticalBlankWidth + placeNameAreaWidth + intervalBetweenNameAndCard;
    int index = 0;

    if (handcard) {
        QList<const Card *> cards;
        for (int i = 0; i < handcards.length(); ++i)
            cards << Sanguosha->getCard(handcards.at(i));
        arrangeCards(cards, QPoint(startX, nameRects.at(index).y()));

        ++index;
    }

    if (equip) {
        arrangeCards(player->getEquips(), QPoint(startX, nameRects.at(index).y()));

        ++index;
    }

    if (judging)
        arrangeCards(player->getJudgingArea(), QPoint(startX, nameRects.at(index).y()));

    if (ServerInfo.OperationTimeout != 0) {
        if (!progressBar) {
            progressBar = new QSanCommandProgressBar();
            progressBar->setMaximumWidth(qMin(boundingRect().width() - 16, (qreal)150));
            progressBar->setMaximumHeight(12);
            progressBar->setTimerEnabled(true);
            progressBarItem = new QGraphicsProxyWidget(this);
            progressBarItem->setWidget(progressBar);
            progressBarItem->setPos(boundingRect().center().x() - progressBarItem->boundingRect().width() / 2, boundingRect().height() - 20);
            connect(progressBar, SIGNAL(timedOut()), this, SLOT(reply()));
        }
        progressBar->setCountdown(QSanProtocol::S_COMMAND_CHOOSE_CARD);
        progressBar->show();
    }
}

void PlayerCardBox::globalchooseCard(const ClientPlayer *player, const QString &reason, const QString &flags,
    bool handcardVisible, const QList<int> &disabledIds, const QList<int> &handcards)
{
    nameRects.clear();
    rowCount = 0;
    intervalsBetweenAreas = -1;
    intervalsBetweenRows = 0;
    maxCardsInOneRow = 0;

    this->player = player;
    this->handcards = handcards;
    this->title = Sanguosha->translate(reason) + ":" + ClientInstance->text;
    this->flags = flags;
    bool handcard = false;
    bool equip = false;
    bool judging = false;

    if (flags.contains(handcardFlag) && !player->isKongcheng()) {
        updateNumbers(player->getHandcardNum());
        handcard = true;
    }

    if (flags.contains(equipmentFlag) && player->hasEquip()) {
        updateNumbers(player->getEquips().length());
        equip = true;
    }

    if (flags.contains(judgingFlag) && !player->getJudgingArea().isEmpty()) {
        updateNumbers(player->getJudgingArea().length());
        judging = true;
    }

    int max = maxCardsInOneRow;
    int maxNumber = maxCardNumberInOneRow;
    maxCardsInOneRow = qMin(max, maxNumber);
    if (maxCardsInOneRow < 2) maxCardsInOneRow = 2;

    prepareGeometryChange();
    moveToCenter();

    this->handcardVisible = handcardVisible;
    this->disabledIds = disabledIds;

    const int startX = verticalBlankWidth + placeNameAreaWidth + intervalBetweenNameAndCard;
    int index = 0;

    if (handcard) {
        QList<const Card *> cards;
        for (int i = 0; i < handcards.length(); ++i)
            cards << Sanguosha->getCard(handcards.at(i));
        arrangeCards(cards, QPoint(startX, nameRects.at(index).y()), true);

        ++index;
    }

    if (equip) {
        arrangeCards(player->getEquips(), QPoint(startX, nameRects.at(index).y()), true);

        ++index;
    }

    if (judging)
        arrangeCards(player->getJudgingArea(), QPoint(startX, nameRects.at(index).y()), true);
    hide();
}

QRectF PlayerCardBox::boundingRect() const
{
    if (player == NULL)
        return QRectF();

    if (rowCount == 0)
        return QRectF();

    const int cardWidth = G_COMMON_LAYOUT.m_cardNormalWidth;
    const int cardHeight = G_COMMON_LAYOUT.m_cardNormalHeight;

    int width = verticalBlankWidth * 2 + placeNameAreaWidth + intervalBetweenNameAndCard;

    if (maxCardsInOneRow > maxCardNumberInOneRow / 2) {
        width += cardWidth * maxCardNumberInOneRow / 2
            + intervalBetweenCards * (maxCardNumberInOneRow / 2 - 1);
    }
    else {
        width += cardWidth * maxCardsInOneRow
            + intervalBetweenCards * (maxCardsInOneRow - 1);
    }

    int areaInterval = intervalBetweenAreas;
    int height = topBlankWidth + bottomBlankWidth + cardHeight * rowCount
        + intervalsBetweenAreas * qMax(areaInterval, 0)
        + intervalsBetweenRows * intervalBetweenRows;

    if (ServerInfo.OperationTimeout != 0)
        height += 12;

    return QRectF(0, 0, width, height);
}

void PlayerCardBox::paintLayout(QPainter *painter)
{
    if (nameRects.isEmpty())
        return;

    foreach(const QRect &rect, nameRects)
        painter->drawRoundedRect(rect, 3, 3);

    int index = 0;

    if (flags.contains(handcardFlag) && !player->isKongcheng()) {
        G_COMMON_LAYOUT.playerCardBoxPlaceNameText.paintText(painter, nameRects.at(index),
            Qt::AlignCenter,
            tr("Handcard area"));
        ++index;
    }
    if (flags.contains(equipmentFlag) && player->hasEquip()) {
        G_COMMON_LAYOUT.playerCardBoxPlaceNameText.paintText(painter, nameRects.at(index),
            Qt::AlignCenter,
            tr("Equip area"));
        ++index;
    }
    if (flags.contains(judgingFlag) && !player->getJudgingArea().isEmpty()) {
        G_COMMON_LAYOUT.playerCardBoxPlaceNameText.paintText(painter, nameRects.at(index),
            Qt::AlignCenter,
            tr("Judging area"));
    }
}

void PlayerCardBox::clear()
{
    if (progressBar != NULL) {
        progressBar->hide();
        progressBar->deleteLater();
        progressBar = NULL;

        progressBarItem->deleteLater();
    }

    foreach(CardItem *item, items)
        item->deleteLater();
    items.clear();

    disappear();
}

int PlayerCardBox::getRowCount(const int &cardNumber) const
{
    return (cardNumber + maxCardNumberInOneRow - 1) / maxCardNumberInOneRow;
}

void PlayerCardBox::updateNumbers(const int &cardNumber)
{
    ++intervalsBetweenAreas;
    if (cardNumber > maxCardsInOneRow)
        maxCardsInOneRow = cardNumber;

    const int cardHeight = G_COMMON_LAYOUT.m_cardNormalHeight;
    const int y = topBlankWidth + rowCount * cardHeight
        + intervalsBetweenAreas * intervalBetweenAreas
        + intervalsBetweenRows * intervalBetweenRows;

    const int count = getRowCount(cardNumber);
    rowCount += count;
    intervalsBetweenRows += count - 1;

    const int height = count * cardHeight
        + (count - 1) * intervalsBetweenRows;

    nameRects << QRect(verticalBlankWidth, y, placeNameAreaWidth, height);
}

void PlayerCardBox::arrangeCards(const CardList &cards, const QPoint &topLeft, bool is_globalchoose)
{
    QList<CardItem *> areaItems;

    foreach(const Card *card, cards) {
        CardItem *item = new CardItem(card);
        if (handcards.contains(card->getId()) && !handcardVisible && Self != player && !player->getVisiblecards().contains(card))
            item = new CardItem(NULL);
        item->setAutoBack(false);
        item->resetTransform();
        item->setParentItem(this);
        item->setFlag(ItemIsMovable, false);
        item->setEnabled(!disabledIds.contains(card->getEffectiveId()));
        if (!is_globalchoose)
            connect(item, SIGNAL(clicked()), this, SLOT(reply()));
        else {
            item->setOpacity(0.9);
            connect(item, SIGNAL(clicked()), this, SLOT(global_click()));
        }
        items << item;
        areaItems << item;
    }

    int n = items.size();
    if (n == 0)
        return;

    const int rows = (n + maxCardNumberInOneRow - 1) / maxCardNumberInOneRow;
    const int cardWidth = G_COMMON_LAYOUT.m_cardNormalWidth;
    const int cardHeight = G_COMMON_LAYOUT.m_cardNormalHeight;
    const int min = qMin(maxCardsInOneRow, maxCardNumberInOneRow / 2);
    const int maxWidth = min * cardWidth + intervalBetweenCards * (min - 1);
    for (int row = 0; row < rows; ++row) {
        int count = qMin(maxCardNumberInOneRow, areaItems.size());
        double step = 0;
        if (count > 1) {
            step = qMin((double)cardWidth + intervalBetweenCards,
                (double)(maxWidth - cardWidth) / qMax(count - 1, 0));
        }
        for (int i = 0; i < count; ++i) {
            CardItem *item = areaItems.takeFirst();
            const double x = topLeft.x() + step * i;
            const double y = topLeft.y() + (cardHeight + intervalBetweenRows) * row;
            item->setPos(x, y);
            QPointF pos;
            pos.setX(x);
            pos.setY(y);
            item->setHomePos(pos);
        }
    }
}

void PlayerCardBox::reply()
{
    CardItem *item = qobject_cast<CardItem *>(sender());

    int index = items.indexOf(item);

    int id = -2;

    if (item)
        id = item->getId();

    ClientInstance->onPlayerChooseCard(index, id);
}

void PlayerCardBox::global_click()
{
    CardItem *item = qobject_cast<CardItem *>(sender());
    m_mutex.lock();

    item->setSelected(!item->isSelected());
    QPropertyAnimation *animation = new QPropertyAnimation(item, "opacity");
    if (item->opacity() < 1)
        animation->setEndValue(1);
    else
        animation->setEndValue(0.9);

    QPointF oldPos = item->homePos();
    QPointF newPos = oldPos;
    newPos.setY(newPos.y() + ((item->opacity() < 1) ? -1 : 1) * 15);
    item->setPos(newPos);
    item->setHomePos(newPos);

    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    m_mutex.unlock();
    int index = items.indexOf(item);
    int id;
    if (handcards.length() > 0 && index < handcards.length())
        id = handcards.at(index);
    else
        id = item->getId();
    emit global_choose(player, id);
}


void PlayerCardBox::setfalse()
{
    foreach(CardItem *item, items)
        if (!item->isSelected()) item->setEnabled(false);
}

void PlayerCardBox::reset()
{
    foreach(CardItem *item, items)
        if (!disabledIds.contains(item->getId())) item->setEnabled(true);
}
