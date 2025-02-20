/*
    RPG Paper Maker Copyright (C) 2017-2021 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "itemsdatas.h"
#include "systemitem.h"
#include "rpm.h"
#include "common.h"
#include "systemeffect.h"
#include "systemcost.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

ItemsDatas::ItemsDatas()
{
    m_model = new QStandardItemModel;
}

ItemsDatas::~ItemsDatas()
{
    SuperListItem::deleteModel(m_model);
}

void ItemsDatas::read(QString path){
    RPM::readJSON(Common::pathCombine(path, RPM::PATH_ITEMS), *this);
}

QStandardItemModel* ItemsDatas::model() const { return m_model; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void ItemsDatas::setDefault() {
    int i, j, length, l;
    QStandardItemModel *modelEffects;
    SystemItem *sys;

    QString names[] = {
        RPM::translate(Translations::HP_POTION),
        RPM::translate(Translations::SUPER_HP_POTION),
        RPM::translate(Translations::MEGA_HP_POTION),
        RPM::translate(Translations::MP_POTION),
        RPM::translate(Translations::SUPER_MP_POTION),
        RPM::translate(Translations::MEGA_MP_POTION),
        RPM::translate(Translations::TP_POTION),
        RPM::translate(Translations::SUPER_TP_POTION),
        RPM::translate(Translations::MEGA_TP_POTION),
        RPM::translate(Translations::PHOENIX_FEATHER),
        RPM::translate(Translations::KEY)
    };
    int iconsX[] = {
        10, 11, 12, 13, 14, 15, 0, 1, 2, 0, 9
    };
    int iconsY[] = {
        1, 1, 1, 1, 1, 1, 2, 2, 2, 0, 1
    };
    int types[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
    };
    bool consumables[] = {
        true, true, true, true, true, true, true, true, true, true, false
    };
    QString descriptions[] = {
        RPM::translate(Translations::HP_POTION_DESCRIPTION),
        RPM::translate(Translations::SUPER_HP_POTION_DESCRIPTION),
        RPM::translate(Translations::MEGA_HP_POTION_DESCRIPTION),
        RPM::translate(Translations::MP_POTION_DESCRIPTION),
        RPM::translate(Translations::SUPER_MP_POTION_DESCRIPTION),
        RPM::translate(Translations::MEGA_MP_POTION_DESCRIPTION),
        RPM::translate(Translations::TP_POTION_DESCRIPTION),
        RPM::translate(Translations::SUPER_TP_POTION_DESCRIPTION),
        RPM::translate(Translations::MEGA_TP_POTION_DESCRIPTION),
        RPM::translate(Translations::PHOENIX_FEATHER_DESCRIPTION),
        RPM::translate(Translations::KEY)
    };
    TargetKind targetsKind[] = {
        TargetKind::Ally, TargetKind::Ally, TargetKind::Ally, TargetKind::Ally,
        TargetKind::Ally, TargetKind::Ally, TargetKind::Ally, TargetKind::Ally,
        TargetKind::Ally, TargetKind::Ally, TargetKind::None
    };
    QString targetConditionsFormulas[] = {
        "t.hp > 0", "t.hp > 0", "t.hp > 0", "t.hp > 0", "t.hp > 0", "t.hp > 0",
        "t.hp > 0", "t.hp > 0", "t.hp > 0", "t.hp === 0", ""
    };
    AvailableKind availablesKind[] = {
        AvailableKind::Always, AvailableKind::Always, AvailableKind::Always,
        AvailableKind::Always, AvailableKind::Always, AvailableKind::Always,
        AvailableKind::Always, AvailableKind::Always, AvailableKind::Always,
        AvailableKind::Always, AvailableKind::Never
    };
    int songsID[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    int prices[] = {
        10, 100, 500, 20, 200, 600, 20, 200, 600, 1000, 0
    };
    QVector<SystemEffect *> effects[] = {
        {SystemEffect::createDamage("-10", QString())}, {SystemEffect
        ::createDamage("-100", QString())}, {SystemEffect::createDamage("-2000",
        QString())}, {SystemEffect::createDamageMP("-10")}, {SystemEffect
        ::createDamageMP("-100")}, {SystemEffect::createDamageMP("-2000")}, {
        SystemEffect::createDamageTP("-10")}, {SystemEffect::createDamageTP(
        "-100")}, {SystemEffect::createDamageTP("-2000")}, {SystemEffect
        ::createDamage("-1", QString())}, {}
    };
    length = (sizeof(names)/sizeof(*names));
    QStandardItemModel *modelPrice;
    for (i = 0; i < length; i++) {
        modelEffects = new QStandardItemModel;
        modelPrice = new QStandardItemModel;
        for (j = 0, l = effects[i].length(); j < l; j++) {
            modelEffects->appendRow(effects[i][j]->getModelRow());
        }
        modelEffects->appendRow(new QStandardItem);
        modelPrice->appendRow((new SystemCost(DamagesKind::Currency, new
            PrimitiveValue(PrimitiveValueKind::DataBase, 1), new PrimitiveValue(
            PrimitiveValueKind::DataBase, 1), 1, new PrimitiveValue(QString
            ::number(prices[i]))))->getModelRow());
        sys = new SystemItem(i + 1, names[i], 1, iconsX[i], iconsY[i], types[i],
            consumables[i], new SystemTranslatable(-1, descriptions[i]), targetsKind[i],
            targetConditionsFormulas[i].isEmpty() ? new PrimitiveValue(
            PrimitiveValueKind::None) : new PrimitiveValue(targetConditionsFormulas[i]),
            availablesKind[i], new SystemPlaySong(songsID[i], SongKind::Sound),
            new PrimitiveValue(PrimitiveValueKind::None), new PrimitiveValue(
            PrimitiveValueKind::None), new PrimitiveValue(true), new
            SystemTranslatable(1, SystemItem::DEFAULT_BATTLE_MESSAGE), modelPrice,
            modelEffects);
        m_model->appendRow(sys->getModelRow());
    }
}

// -------------------------------------------------------
//
//  READ / WRITE
//
// -------------------------------------------------------

void ItemsDatas::read(const QJsonObject &json){

    // Clear
    SuperListItem::deleteModel(m_model, false);

    // Read
    QJsonArray jsonList = json["items"].toArray();
    for (int i = 0; i < jsonList.size(); i++){
        QStandardItem* item = new QStandardItem;
        SystemItem* sysItem = new SystemItem;
        sysItem->read(jsonList[i].toObject());
        item->setData(QVariant::fromValue(reinterpret_cast<quintptr>(sysItem)));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
        item->setText(sysItem->toString());
        m_model->appendRow(item);
    }
}

// -------------------------------------------------------

void ItemsDatas::write(QJsonObject &json) const{
    QJsonArray jsonArray;
    for (int i = 0; i < m_model->invisibleRootItem()->rowCount(); i++){
        QJsonObject jsonCommon;
        SystemItem* sysItem = ((SystemItem*)m_model->item(i)->data()
                               .value<quintptr>());
        sysItem->write(jsonCommon);
        jsonArray.append(jsonCommon);
    }
    json["items"] = jsonArray;
}
