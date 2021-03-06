#include "photo.h"
#include "clientplayer.h"
#include "carditem.h"
#include "engine.h"
#include "standard.h"
#include "client.h"
#include "playercarddialog.h"
#include "rolecombobox.h"

#include <QPainter>
#include <QDrag>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QMessageBox>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QMenu>
#include <QGraphicsDropShadowEffect>

#include "pixmapanimation.h"

Photo::Photo()
#ifdef USE_RCC
    :Pixmap(":system/photo-back.png"),
#else
    :Pixmap("image/system/photo-back.png"),
#endif
    player(NULL),
    handcard("image/system/handcard.png"),
    action_item(NULL), save_me_item(NULL), permanent(false),
    weapon(NULL), armor(NULL), defensive_horse(NULL), offensive_horse(NULL),
    order_item(NULL), hide_avatar(false)
{
    setAcceptHoverEvents(true);

    QSettings settings("image/system/photo.ini", QSettings::IniFormat);

    back_icon = new Pixmap("image/system/small-back.png");
    back_icon->setParentItem(this);
    settings.beginGroup("back_icon");
    QList<QVariant> coord = settings.value("pos").toList();
    back_icon->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    back_icon->setZValue(coord.at(2).toReal());
    back_icon->setOpacity(settings.value("opacity").toReal());
    back_icon->hide();
    settings.endGroup();

    chain_icon = new Pixmap("image/system/chain.png");
    chain_icon->setParentItem(this);
    chain_icon->setPos(boundingRect().width() - 22, 5);
    chain_icon->hide();

    wake_icon = new Pixmap("image/system/sleep.png");
    wake_icon->setParentItem(this);
    settings.beginGroup("wake_icon");
    coord = settings.value("pos").toList();
    wake_icon->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    wake_icon->setZValue(coord.at(2).toReal());
    wake_icon->setOpacity(settings.value("opacity").toReal());
    wake_icon->hide();
    settings.endGroup();

    progress_bar = new QProgressBar;
    progress_bar->setMinimum(0);
    progress_bar->setMaximum(100);
    progress_bar->setValue(0);
    progress_bar->hide();
    progress_bar->setMaximumHeight(15);
    progress_bar->setMaximumWidth(pixmap.width());
    progress_bar->setTextVisible(false);
    timer_id = 0;

    frame_item = new QGraphicsPixmapItem(this);
    settings.beginGroup("frame_item");
    coord = settings.value("pos").toList();
    frame_item->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    frame_item->setZValue(coord.at(2).toReal());
    frame_item->setOpacity(settings.value("opacity").toReal());
    settings.endGroup();

    QGraphicsProxyWidget *widget = new QGraphicsProxyWidget(this);
    widget->setWidget(progress_bar);
    widget->setPos( -6 , - 25);

    skill_name_item = new QGraphicsSimpleTextItem(this);
    skill_name_item->setBrush(Qt::white);
    skill_name_item->setFont(Config.SmallFont);
    skill_name_item->moveBy(10, 30);

    QGraphicsDropShadowEffect * drp = new QGraphicsDropShadowEffect;
    drp->setBlurRadius(10);
    drp->setColor(Qt::yellow);
    drp->setOffset(0);
    skill_name_item->setGraphicsEffect(drp);

    emotion_item = new QGraphicsPixmapItem(this);
    settings.beginGroup("emotion_item");
    coord = settings.value("moveby").toList();
    emotion_item->moveBy(coord.first().toReal(), coord.last().toReal());
    emotion_item->setZValue(settings.value("zvalue").toReal());
    emotion_item->setOpacity(settings.value("opacity").toReal());
    settings.endGroup();

    avatar_area = new QGraphicsRectItem(0, 0, 122, 50, this);
    avatar_area->setPos(5, 15);
    avatar_area->setPen(Qt::NoPen);
    avatar_area->setZValue(0.3);

    small_avatar_area = new QGraphicsRectItem(0, 0, 42, 36, this);
    small_avatar_area->setPos(86, 30);
    small_avatar_area->setPen(Qt::NoPen);
    small_avatar_area->setZValue(0.3);

    equips << &weapon << &armor << &defensive_horse << &offensive_horse;
    int i;
    for(i=0; i<4; i++){
        equip_rects[i] = new QGraphicsRectItem(QRect(1, 118 + 17 * i, 129, 16), this);
        equip_rects[i]->setPen(Qt::NoPen);
    }

    kingdom_item = new QGraphicsPixmapItem(this);
    settings.beginGroup("kingdom_item");
    coord = settings.value("pos").toList();
    kingdom_item->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    kingdom_item->setZValue(coord.at(2).toReal());
    kingdom_item->setOpacity(settings.value("opacity").toReal());
    settings.endGroup();

#ifdef USE_RCC
    ready_item = new QGraphicsPixmapItem(QPixmap(":system/ready.png"), this);
#else
    ready_item = new QGraphicsPixmapItem(QPixmap("image/system/ready.png"), this);
#endif
    settings.beginGroup("ready_item");
    coord = settings.value("pos").toList();
    ready_item->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    ready_item->setZValue(coord.at(2).toReal());
    ready_item->setOpacity(settings.value("opacity").toReal());
    ready_item->hide();
    settings.endGroup();

    mark_item = new QGraphicsTextItem(this);
    settings.beginGroup("mark_item");
    coord = settings.value("pos").toList();
    mark_item->setPos(coord.at(0).toReal(), coord.at(1).toReal());
    mark_item->setZValue(coord.at(2).toReal());
    mark_item->setOpacity(settings.value("opacity").toReal());
    settings.endGroup();
    mark_item->setDefaultTextColor(Qt::white);

    role_combobox = NULL;
    pile_button = NULL;
    settings.deleteLater();
}

void Photo::setOrder(int order){
    QPixmap pixmap(QString("image/system/number/%1.png").arg(order));
    if(order_item)
        order_item->setPixmap(pixmap);
    else{
        order_item = new QGraphicsPixmapItem(pixmap, this);
        order_item->setVisible(ServerInfo.EnableSame);
        order_item->moveBy(15, 0);
    }
}

void Photo::revivePlayer(){
    updateAvatar();
    updateSmallAvatar();
    this->setOpacity(1.0);

    role_combobox->show();
}

void Photo::createRoleCombobox(){
    role_combobox = new RoleCombobox(this);

    QString role = player->getRole();
    if(!ServerInfo.EnableHegemony && !role.isEmpty())
            role_combobox->fix(role);

    connect(player, SIGNAL(role_changed(QString)), role_combobox, SLOT(fix(QString)));
}

void Photo::updateRoleComboboxPos()
{
    //if(pile_button)pile_button->setPos(46, 48);
}

void Photo::showProcessBar(){
    progress_bar->setValue(0);
    progress_bar->show();

    if(ServerInfo.OperationTimeout != 0)
        timer_id = startTimer(500);
}

void Photo::hideProcessBar(){
    progress_bar->setValue(0);
    progress_bar->hide();

    if(timer_id != 0){
        killTimer(timer_id);
        timer_id = 0;
    }
}

void Photo::setEmotion(const QString &emotion, bool permanent){
    this->permanent = permanent;

    if(emotion == "."){
        emotion_item->hide();
        return;
    }

    QString path = QString("image/system/emotion/%1.png").arg(emotion);
    emotion_item->setPixmap(QPixmap(path));
    emotion_item->show();

    if(emotion == "question" || emotion == "no-question")
        return;
    //if(emotion.contains("cards"))
    //    emotion_item->moveBy(-10,0);
    if(emotion.contains("skill")){
        QString spec_name = QString("%1/revise.ini").arg(path.replace(".png", ""));
        QSettings settings(spec_name, QSettings::IniFormat);
        qreal x = settings.value("x", 65535).toReal();
        qreal y = settings.value("y", 65535).toReal();
        qreal scale = settings.value("s", 1.0).toReal();
        qreal oca = settings.value("o", 1.0).toReal();
        settings.deleteLater();

        if(x != 65535 && y != 65535)
            emotion_item->moveBy(x, y);
        emotion_item->setScale(scale);
        emotion_item->setOpacity(oca);
    }

    if(!permanent)
        QTimer::singleShot(2000, this, SLOT(hideEmotion()));

    PixmapAnimation::GetPixmapAnimation(this, emotion);
}

void Photo::tremble(){
    QPropertyAnimation *vibrate = new QPropertyAnimation(this, "x");
    static qreal offset = 20;

    vibrate->setKeyValueAt(0.5, x() - offset);
    vibrate->setEndValue(x());

    vibrate->setEasingCurve(QEasingCurve::OutInBounce);

    vibrate->start(QAbstractAnimation::DeleteWhenStopped);
}

void Photo::showSkillName(const QString &skill_name){
    skill_name_item->setText(Sanguosha->translate(skill_name));
    skill_name_item->show();

    QTimer::singleShot(1500, this, SLOT(hideSkillName()));
}

void Photo::hideSkillName(){
    skill_name_item->hide();
}

void Photo::setWakeState(){
    if(player->getWakeSkills().isEmpty())
        return;
    if(player->getMark("_wake") > 0)
        wake_icon->setPixmap(QPixmap("image/system/wake.png"));
    else
        wake_icon->setPixmap(QPixmap("image/system/sleep.png"));
}

void Photo::setDrankState(){
    if(player->hasFlag("drank"))
        avatar_area->setBrush(QColor(0xFF, 0x00, 0x00, 255 * 0.45));
    else if(player->hasMark("poison"))
        setPoisonState();
    else
        avatar_area->setBrush(Qt::NoBrush);
}

void Photo::setEcstState(){
    if(player->hasFlag("ecst"))
        avatar_area->setBrush(QColor(0x00, 0x00, 0xDD, 255 * 0.35));
    else if(player->hasMark("poison"))
        setPoisonState();
    else
        avatar_area->setBrush(Qt::NoBrush);
}

void Photo::setPoisonState(){
    if(player->hasMark("poison"))
        avatar_area->setBrush(QColor(0x00, 0xFF, 0x00, 255 * 0.3));
    else if(player->hasFlag("drank"))
        setDrankState();
    else if(player->hasFlag("ecst"))
        setEcstState();
    else
        avatar_area->setBrush(Qt::NoBrush);
}

void Photo::setActionState(){
    if(action_item == NULL){
        action_item = new QGraphicsPixmapItem(this);
        action_item->setPixmap(QPixmap("image/system/3v3/actioned.png"));
        action_item->setPos(75, 40);
    }

    action_item->setVisible(player->hasFlag("actioned"));
}

void Photo::hideEmotion(){
    if(!permanent)
        emotion_item->hide();
}

void Photo::timerEvent(QTimerEvent *event){
    int step = 100 / double(ServerInfo.OperationTimeout * 5);
    int new_value = progress_bar->value() + step;
    new_value = qMin(progress_bar->maximum(), new_value);
    progress_bar->setValue(new_value);

    if(new_value == progress_bar->maximum()){
        killTimer(event->timerId());
        timer_id = 0;
    }
}

void Photo::setPlayer(const ClientPlayer *player)
{
    this->player = player;

    if(player){
        connect(player, SIGNAL(general_changed()), this, SLOT(updateAvatar()));
        connect(player, SIGNAL(general2_changed()), this, SLOT(updateSmallAvatar()));
        connect(player, SIGNAL(kingdom_changed()), this, SLOT(updateAvatar()));
        connect(player, SIGNAL(ready_changed(bool)), this, SLOT(updateReadyItem(bool)));
        connect(player, SIGNAL(state_changed()), this, SLOT(refresh()));
        connect(player, SIGNAL(phase_changed()), this, SLOT(updatePhase()));
        connect(player, SIGNAL(waked()), this, SLOT(setWakeState()));
        connect(player, SIGNAL(drank_changed()), this, SLOT(setDrankState()));
        connect(player, SIGNAL(ecst_changed()), this, SLOT(setEcstState()));
        connect(player, SIGNAL(poison_changed()), this, SLOT(setPoisonState()));
        connect(player, SIGNAL(action_taken()), this, SLOT(setActionState()));
        connect(player, SIGNAL(pile_changed(QString)), this, SLOT(updatePile(QString)));

        mark_item->setDocument(player->getMarkDoc(false));
    }

    updateAvatar();
}

void Photo::hideAvatar(){
    hide_avatar = true;
    kingdom_item->hide();

    update();
}

void Photo::showCard(int card_id){
    const Card *card = Sanguosha->getCard(card_id);

    CardItem *card_item = new CardItem(card);
    scene()->addItem(card_item);

    QPointF card_pos(pos() + QPointF(0, 20));
    card_item->setPos(card_pos);
    card_item->setHomePos(card_pos);
    card_item->setEnabled(false);

    QTimer::singleShot(2000, card_item, SLOT(deleteLater()));
}

void Photo::updateAvatar(){
    if(player){
        const General *general = player->getAvatarGeneral();
        avatar_area->setToolTip(general->getSkillDescription());
        bool success = avatar.load(general->getPixmapPath("small"));
        QPixmap kingdom_icon(player->getKingdomIcon());
        kingdom_item->setPixmap(kingdom_icon);
        kingdom_frame.load(player->getKingdomFrame());

        if(!success){
            QPixmap pixmap(General::SmallIconSize);
            pixmap.fill(Qt::black);
            QPainter painter(&pixmap);

            painter.setPen(Qt::white);
            painter.setFont(Config.SmallFont);
            painter.drawText(0, 0, pixmap.width(), pixmap.height(),
                             Qt::AlignCenter,
                             Sanguosha->translate(player->getGeneralName()));

            avatar = pixmap;
        }

    }else{
        avatar = QPixmap();
        kingdom_frame = QPixmap();

        avatar_area->setToolTip(QString());
        small_avatar_area->setToolTip(QString());

        ready_item->hide();
    }

    hide_avatar = false;
    kingdom_item->show();

    update();
}

void Photo::updateSmallAvatar(){
    const General *general2 = player->getGeneral2();
    if(general2){
        bool success = small_avatar.load(general2->getPixmapPath("tiny"));
        small_avatar_area->setToolTip(general2->getSkillDescription());

        if(!success){
            QPixmap pixmap(General::TinyIconSize);
            pixmap.fill(Qt::black);

            QPainter painter(&pixmap);

            painter.setPen(Qt::white);
            painter.drawText(0, 0, pixmap.width(), pixmap.height(),
                             Qt::AlignCenter,
                             Sanguosha->translate(player->getGeneral2Name()));

            small_avatar = pixmap;
        }
    }

    hide_avatar = false;
    update();
}

void Photo::updateReadyItem(bool visible){
    ready_item->setVisible(visible);
}

void Photo::refresh(){
    if(player && player->getHp() <= 0 && player->isAlive() && player->getMaxHP() > 0){
        setFrame(SOS);

        if(save_me_item == NULL){
            QPixmap save_me("image/system/death/save-me.png");
            save_me_item = new QGraphicsPixmapItem(save_me, this);
            save_me_item->setPos(5, 20);
        }
        save_me_item->show();
    }else{
        if(save_me_item)
            save_me_item->hide();
        updatePhase();
    }

    update();
}

const ClientPlayer *Photo::getPlayer() const{
    return player;
}

void Photo::speak(const QString &content)
{

}

CardItem *Photo::takeCardItem(int card_id, Player::Place place){
    CardItem *card_item = NULL;

    if(place == Player::Hand || place == Player::Special){
        card_item = new CardItem(Sanguosha->getCard(card_id));
        card_item->setPos(pos());
        card_item->shift();
    }else if(place == Player::Equip){
        foreach(CardItem **equip_ptr, equips){
            CardItem *equip = *equip_ptr;
            if(equip && equip->getCard()->getId() == card_id){
                card_item = equip;
                *equip_ptr = NULL;

                int index = equips.indexOf(equip_ptr);
                equip_rects[index]->setToolTip(QString());
                break;
            }
        }
    }else if(place == Player::Judging){
        card_item = CardItem::FindItem(judging_area, card_id);
        if(card_item){
            int index = judging_area.indexOf(card_item);
            delete judging_pixmaps.takeAt(index);
            judging_area.removeAt(index);
        }
    }

    update();
    return card_item;
}

void Photo::installEquip(CardItem *equip){
    const EquipCard *equip_card = qobject_cast<const EquipCard *>(equip->getCard());
    int index = -1;
    switch(equip_card->location()){
    case EquipCard::WeaponLocation: weapon = equip; index = 0; break;
    case EquipCard::ArmorLocation: armor = equip; index = 1; break;
    case EquipCard::DefensiveHorseLocation: defensive_horse = equip; index = 2; break;
    case EquipCard::OffensiveHorseLocation: offensive_horse = equip; index = 3; break;
    }

    if(index >= 0)
        equip_rects[index]->setToolTip(equip_card->getDescription());

    equip->setHomePos(pos());
    equip->goBack(true);

    update();
}

void Photo::installDelayedTrick(CardItem *trick){
    trick->setHomePos(pos());
    trick->goBack(true);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(this);
    const DelayedTrick *delay = player->topDelayedTrick();
    item->setPixmap(QPixmap(delay->getIconPath()));
    QString tooltip = delay->getDescription();
    if(delay->isVirtualCard())
        tooltip = QString("%1<br/>----------<br/>%2").arg(tooltip)
                .arg(Sanguosha->getCard((delay->getSubcards()).at(0))->getDescription());
    item->setToolTip(tooltip);

    item->setPos(-10, 16 + judging_area.count() * 19);
    item->setZValue(1.1);
    judging_area << trick;
    judging_pixmaps << item;
}

void Photo::addCardItem(CardItem *card_item){
    card_item->setHomePos(pos());
    card_item->goBack(true);

    update();
}

void Photo::drawMagatama(QPainter *painter, int index, const QPixmap &pixmap, QSettings &settings){
    QList<QVariant> coord = settings.value("magatama_item/first").toList();
    static const QPoint first_row(coord.first().toReal(), coord.last().toReal());
    coord = settings.value("magatama_item/second").toList();
    static const QPoint second_row(coord.first().toReal(), coord.last().toReal());
    static const int skip = settings.value("magatama_item/skip").toInt();

    // index is count from 0
    if(index >= 5){
        // draw magatama at first row
        QPoint pos = first_row;
        pos.rx() += (index - 5) * skip;
        painter->drawPixmap(pos, pixmap);
    }else{
        // draw magatama at second row
        QPoint pos = second_row;
        pos.rx() += index * skip;
        painter->drawPixmap(pos, pixmap);
    }
}

void Photo::drawHp(QPainter *painter, QSettings &settings){
    int hp = qMax(0, player->getHp());

    int index = 5;
    if(player->isWounded())
        index = qBound(0, hp, 5);

    QPixmap *magatama = MagatamaWidget::GetSmallMagatama(index);
    QPixmap *zero_magatama = MagatamaWidget::GetSmallMagatama(0);

    int max_hp = player->getMaxHP();
    int i;
    for(i=0; i< hp; i++)
        drawMagatama(painter, i, *magatama, settings);
    for(i=hp; i< max_hp; i++)
        drawMagatama(painter, i, *zero_magatama, settings);
}

void Photo::setFrame(FrameType type){
    static QPixmap playing_frame("image/system/frame/playing.png");
    static QPixmap responsing_frame("image/system/frame/responsing.png");
    static QPixmap sos_frame("image/system/frame/sos.png");

    QPixmap *to_draw = NULL;
    switch(type){
    case Playing: to_draw = &playing_frame; break;
    case Responsing: to_draw = &responsing_frame; break;
    case SOS: to_draw = &sos_frame; break;
    default:
        break;
    }

    if(to_draw){
        frame_item->setPixmap(*to_draw);
        frame_item->show();
    }else{
        frame_item->hide();
    }

    update();
}

void Photo::updatePhase(){
    if(player->getPhase() != Player::NotActive)
        setFrame(Playing);
    else
        setFrame(NoFrame);
}

static bool CompareByNumber(const Card *card1, const Card *card2){
    return card1->getNumber() < card2->getNumber();
}

void Photo::updatePile(const QString &pile_name){
    QPushButton *button = NULL;
    QGraphicsProxyWidget *button_widget = NULL;

    if(pile_button == NULL){
        button = new QPushButton;
        button->setObjectName(pile_name);
        button->setProperty("private_pile","true");

        button_widget = new QGraphicsProxyWidget(this);
        button_widget->setWidget(button);
        //button_widget->setPos(pos());
        button_widget->moveBy(46, 68);
        button_widget->resize(80, 16);
        //scene()->addItem(button_widget);

        QMenu *menu = new QMenu(button);
        button->setMenu(menu);

        pile_button = button_widget;
    }else
    {
        button_widget = pile_button;
        button = qobject_cast<QPushButton *>(pile_button->widget());
    }

    ClientPlayer *who = qobject_cast<ClientPlayer *>(sender());
    if(who == NULL)
        return;

    QStringList names = who->getPileNames();
    button->menu()->clear();

    button_widget->hide();
    int active = 0;
    foreach(QString pile_name,names)
    {
        const QList<int> &pile = who->getPile(pile_name);
        if(!pile.isEmpty()){
            button_widget->show();
            active++;
            button->setText(QString("%1 (%2)").arg(Sanguosha->translate(pile_name)).arg(pile.length()));
        }

        QMenu *menu = button->menu();
        menu->setProperty("private_pile","true");
        //menu->clear();

        QList<const Card *> cards;
        foreach(int card_id, pile){
            const Card *card = Sanguosha->getCard(card_id);
            cards << card;
        }

        qSort(cards.begin(), cards.end(), CompareByNumber);
        foreach(const Card *card, cards){
            menu->addAction(card->getSuitIcon(),
                            QString("%1 (%2)").arg(card->getFullName())
                            .arg(Sanguosha->translate(pile_name)));
        }
        menu->addSeparator();
    }
    if(active>1)button->setText(QString(tr("Multiple")));

    if(who->getMaxHP()>5)
    {
        button_widget->setPos(pos());
        button_widget->moveBy(100, 68);
        button_widget->resize(16,16);
        button->setText(QString());
    }
}

void Photo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Pixmap::paint(painter, option, widget);

    if(!player)
        return;
    QSettings settings("image/system/photo.ini", QSettings::IniFormat);

    painter->setPen(Qt::white);
    QString title = player->screenName();
    painter->drawText(QRectF(0,0,132,19), title, QTextOption(Qt::AlignHCenter));

    static QPixmap wait_frame("image/system/wait-frame.png");
    if(kingdom_frame.isNull())
        painter->drawPixmap(3, 13, wait_frame);

    if(hide_avatar)
        return;

    // avatar related
    painter->drawPixmap(5, 15, avatar);
    painter->drawPixmap(86, 30, small_avatar);

    // kingdom related
    painter->drawPixmap(3, 13, kingdom_frame);

    int n = player->getHandcardNum();
    if(n > 0){
        settings.beginGroup("handcard_item");
        QList<QVariant> coord = settings.value("pos").toList();
        painter->drawPixmap(coord.first().toReal(), coord.last().toReal(), handcard);
        painter->setPen(Qt::yellow);
        coord = settings.value("text_pos").toList();
        painter->drawText(coord.first().toReal(), coord.last().toReal(), QString::number(n));
        settings.endGroup();
    }

    painter->setPen(Qt::white);
    QString state_str = player->getState();
    if(!state_str.isEmpty() && state_str != "online"){
        QList<QVariant> coord = settings.value("state_item/pos").toList();
        painter->drawText(coord.first().toReal(), coord.last().toReal(), Sanguosha->translate(state_str));
    }

    drawHp(painter, settings);

    if(player->getPhase() != Player::NotActive){
        static QList<QPixmap> phase_pixmaps;
        if(phase_pixmaps.isEmpty()){
            QStringList names;
            names << "round_start" << "start" << "judge" << "draw"
                    << "play" << "discard" << "finish";

            foreach(QString name, names)
                phase_pixmaps << QPixmap(QString("image/system/phase/%1.png").arg(name));
        }

        int index = static_cast<int>(player->getPhase());
        QPixmap phase_pixmap = phase_pixmaps.at(index);
        painter->drawPixmap(115, 120, phase_pixmap);
    }

    drawEquip(painter, weapon, 0);
    drawEquip(painter, armor, 1);
    drawEquip(painter, defensive_horse, 2);
    drawEquip(painter, offensive_horse, 3);

    chain_icon->setVisible(player->isChained());
    back_icon->setVisible(! player->faceUp());
    wake_icon->setVisible(!player->getWakeSkills().isEmpty());

    if(player->isDead()){
        if(death_pixmap.isNull()){
            QString path = player->getDeathPixmapPath();
            death_pixmap.load(path);
            death_pixmap = death_pixmap.scaled(death_pixmap.size() / (1.25));
        }
        QList<QVariant> coord = settings.value("death_pixmap/pos").toList();
        painter->drawPixmap(coord.first().toReal(), coord.last().toReal(), death_pixmap);
    }
    settings.deleteLater();
}

void Photo::drawEquip(QPainter *painter, CardItem *equip, int order){
    if(!equip)
        return;

    QRect suit_rect(6, 105 + 19 + order * 15, 12.5, 12.5);
    painter->drawPixmap(suit_rect, equip->getSuitPixmap());

    const EquipCard *card = qobject_cast<const EquipCard *>(equip->getCard());
    painter->setPen(Qt::white);
    QFont bold_font;
    bold_font.setBold(true);
    //painter->setFont(bold_font);
    painter->drawText(25, 115 + 19 + order * 15, card->getNumberString());
    painter->drawText(39, 115 + 19 + order * 15, card->label());
}

QVariant Photo::itemChange(GraphicsItemChange change, const QVariant &value){
    if(change == ItemFlagsHaveChanged){
        if(!ServerInfo.EnableSame)
            order_item->setVisible(flags() & ItemIsSelectable);
    }

    return Pixmap::itemChange(change, value);
}

void Photo::killPlayer(){
    if(!avatar.isNull())
        MakeGray(avatar);

    if(!small_avatar.isNull())
        MakeGray(small_avatar);

    kingdom_frame = QPixmap();
    if(!ServerInfo.EnableHegemony)
        role_combobox->hide();

    if(save_me_item)
        save_me_item->hide();
}
