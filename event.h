//
// Created by Radulescu Adrian on 22/11/2017.
//

#ifndef VIAGOGO_CODING_CHALLENGE_EVENT_H
#define VIAGOGO_CODING_CHALLENGE_EVENT_H

#include <set>
#include <vector>
#include <string>
#include <random>
#include <iostream>

/**
 * a struct representing a ticket
 */

struct Ticket {
    double price; // the price of the Ticket
    friend bool operator<(const Ticket& left, const Ticket& right) {
        return std::tie(left.price) < std::tie(right.price);
    }
    friend bool operator==(const Ticket& left, const Ticket& right) {
        return std::tie(left.price) == std::tie(right.price);
    }
};

/**
 * Represents an event object and the actions that can be performed on them
 * @memberof ID         = the ID of the event
 * @memberof tickets    = the available tickets for this event
 */

class Event {

    private:

    int mID;
    std::set<Ticket> mTickets;

    public:

    explicit Event(const int& ID);
    Event(const int&, const Ticket&);
    Event(const int&, const std::vector<Ticket>&);
    Event(const int&, const size_t&, const Ticket[]);
    Event(const Event&);
    Event();

    ~Event();

    //getters
    /**
     * @return the ID of the event
     */
    int getID() const;

    /**
     * @return the lowest price for this event without removing the ticket from the set
     */
    std::string peekLowestTicketPrice();

    std::string popLowestTicketPrice();

    /**
     * @return  all the available tickets for this event, sorted from lowest price to highest price
     */
    std::vector<Ticket> getTickets() const;

    //setters

    void setID(const int&);

    // operations
    /**
     * Adds a new ticket to this event
     * @param t  = the thicket to be inserted
     */
    void insertTicket(const Ticket &t);

    /**
     * Removes ticket with the specified price and returns it
     * @param price
     * @return
     */
    Ticket popTicketWithPrice(double price);

};


#endif //VIAGOGO_CODING_CHALLENGE_EVENT_H
