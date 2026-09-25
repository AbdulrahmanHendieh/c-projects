

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
/*
 * Initializes an empty tour by setting the head pointer to nullptr.
 */
    Tour();
/*
 * Destructor for the Tour class.
 * Responsible for freeing all dynamically allocated memory.
 * Iterates through the circular linked list and deletes each node
 * one by one to prevent memory leaks when the program terminates.
 */
    ~Tour();

/*
 * Prints the coordinates of all points in the tour to standard output
 * one point per line in the order they are visited.
 */
    void show() const;
/*
 * Draws the tour onto the given QGraphicsScene by drawing lines
 * between adjacent points in the circular linked list.
 */
    void draw(QGraphicsScene* scene) const;

/*
 * Returns the number of points (nodes) currently in the tour.
 */
    int size() const;
/*
 * Calculates and returns the total Euclidean distance of the tour
 * by summing the distances between all adjacent points.
 */
    double distance() const;
 /*
 * Inserts a new point p into the tour using the nearest neighbor heuristic.
 * The new point is inserted immediately after the node that is geographically closest to p.
 */
    void insertNearest(Point p);

/*
 * Inserts a new point p into the tour using the smallest increase heuristic.
 * The point is inserted exactly where it causes the smallest possible increase
 * in the total length of the tour.
 */
    void insertSmallest(Point p);

private:
    // The sart of the linked list
    Node* head;
};

#endif // TOUR_H
