/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while(!isEmpty(*robot)){
            delete robot;
            robot = new Robot();
        }
        units.push_back(robot);
    }
    teleportHero();
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (size_t i = 0; i < units.size(); i++){
        units[i]->draw(scene);
    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Unit* unit: units)
        unit->moveTowards(hero.asPoint());
}


void GameState::updateCrashes() {
    for (unsigned i = 0; i < units.size(); i++){
        for (unsigned j = i + 1; j < units.size(); j++){
            if (units[i] ->at(*units[j])){
                units[i] ->doCrash();
                units[j] ->doCrash();
            }

        }
    }
}

int GameState::countToBeJunked()const{
    int numberDestroyed =0;
    for(Unit* unit: units)
        if(unit->isToBeJunked())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i]->isToBeJunked()) {
            Point p = units[i]->asPoint();
            delete units[i];
            units[i] = new Junk(p);
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Unit* unit: units){
        if(hero.at(unit->asPoint())){
            return true;
        }
    }

    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Unit* u: units)
        if(u->at(unit))
            return false;
    return true;
}

GameState::~GameState(){
    for (Unit* unit: units){
        delete unit;
    }
    units.clear();
}

GameState::GameState(const GameState& other){
    for (Unit* const unit : other.units){
        units.push_back(unit->clone());
    }
    hero = other.hero;
}

GameState& GameState::operator=(const GameState& other){
    if (this != &other){

        for (Unit* unit: units){
            delete unit;
        }
        units.clear();
    }

    for (const Unit* unit: other.units){
        units.push_back(unit->clone());
    }
    hero = other.hero;

    return *this;
}
