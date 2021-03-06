#ifndef _Nijigen_PACKAGE_H
#define _Nijigen_PACKAGE_H

#include "package.h"
#include "card.h"

class NijigenPackage : public Package
{
    Q_OBJECT

public:
    NijigenPackage();
};

class WuxinCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE WuxinCard();

    bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    void use(Room *room, ServerPlayer *player, QList<ServerPlayer *> &targets) const;
};

#endif

