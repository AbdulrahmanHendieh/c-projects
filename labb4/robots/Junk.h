// name: Abdulrahman Hendieh
// liu Id: abdhe895

/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:
    Junk(const Point& p): Unit(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
     */
    void draw(QGraphicsScene* scene) const override;

    /*
     * Does nothing because junk remains stationary and does not move towards the hero
     */
    void moveTowards(const Point& pt) override;

    /*
     * Does nothing because junk cannot crash further
     */
    void doCrash() override;

    /*
     * Returns false since junk is already scrap metal and cannot be junked agai
     */
    bool isToBeJunked() const override;

   /*
    * Returns false because junk is inanimate and not considered alive
    */
    bool isAlive() const override;

    /*
     * Creates and returns a heap allocated deep copy of this exact Jnk object using the copy costructor
     */
    Unit* clone() const override;

};

#endif // JUNK_H
