// Liu ID: abdhe895
// name: Abdulrahman Hendieh
#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"





Tour::Tour()
{
    head = nullptr;
}

Tour::~Tour()
{
    if (head == nullptr) {
        return;
    }
    Node* current_node = head;

        do{

        Node* next_node = current_node->next;
            delete current_node;
        current_node = next_node;
        }while(current_node != head);
}

void Tour::show () const
{
    if (head == nullptr){
        return;
    }

    Node* current_node = head;

    do{
        cout << current_node -> point.toString() << endl;
        current_node = current_node -> next;
    } while (current_node != head);
}

void Tour::draw(QGraphicsScene *scene) const
{
    if (head == nullptr){
        return;
    }
    Node* current_node = head;

    do{
        current_node->point.drawTo(current_node->next->point, scene);
        current_node = current_node->next;
    }while (current_node != head);

}

int Tour::size() const
{
    if (head == nullptr){
        return 0;
    }

    int number_nodes = 0;
    Node* current_node = head;

    do{
        number_nodes += 1;
        current_node = current_node -> next;
    } while (current_node != head);

    return number_nodes;
}

double Tour::distance() const
{
    if (head == nullptr){
        return 0;
    }

    double total_tour_distance = 0.0;
    Node* current_node = head;

    do{
        double distance_between_two_points =  current_node->point.distanceTo(current_node->next->point);
        total_tour_distance += distance_between_two_points;
        current_node = current_node -> next;
    } while (current_node != head);


    return total_tour_distance;
}

void Tour::insertNearest(Point p)
{
    if (head == nullptr){
        head = new Node(p);
        head->next = head;
        return;
    }
    Node* closest_node = head;
    double closest_node_distance_to_p = head ->point.distanceTo(p);
    Node* current_node = head->next;

    do{
        double new_distance = current_node->point.distanceTo(p);

        if (closest_node_distance_to_p > new_distance){
            closest_node_distance_to_p = new_distance;
            closest_node = current_node;
        }

        current_node = current_node->next;

    } while (current_node != head);

    Node* new_node = new Node(p);
    new_node->next = closest_node->next;
    closest_node->next = new_node;
}

void Tour::insertSmallest(Point p)
{
    if (head == nullptr){
        head = new Node(p);
        head->next = head;
        return;
    }


    Node* first_node = head;
    Node* sec_node = head->next;
    double smallest_increase = first_node->point.distanceTo(p) + sec_node->point.distanceTo(p) - first_node->point.distanceTo(sec_node->point);
    Node* best_node_to_insert_after = first_node;
    Node* current_node = head->next;

    do{
        double new_increase = current_node->point.distanceTo(p) + current_node->next->point.distanceTo(p) - current_node->point.distanceTo(current_node->next->point);

        if (smallest_increase > new_increase){
            smallest_increase = new_increase;
            best_node_to_insert_after = current_node;
        }
        current_node = current_node->next;
    } while (current_node != head);

    Node* new_node = new Node(p);
    new_node->next = best_node_to_insert_after->next;
    best_node_to_insert_after->next = new_node;

}
