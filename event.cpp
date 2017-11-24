//
// Created by Radulescu Adrian on 22/11/2017.
//

#include "event.h"



Event::Event() = default;

Event::Event(const int& ID) {
    this ->mID = ID;
}

Event::Event(const int& rID, const Ticket& rTicket) {

    this ->mID = rID;
    this ->mTickets.insert(rTicket);
}

Event::Event(const int& rID, const size_t& rNumberOfTickets, const Ticket rTickets[]) {

    this ->mID = rID;
    for (int i = 0; i < rNumberOfTickets; i ++) {
        this ->mTickets.insert(rTickets[i]);
    }
}

Event::Event(const int& rID, const std::vector<Ticket>& rTickets) {

    this ->mID = rID;
    for (auto ticket : rTickets) {
        this ->mTickets.insert(ticket);
    }
}

Event::Event(const Event& event) {

    this ->mID = event.mID;

    for (auto ticket : event.getTickets()) {
        this ->mTickets.insert(ticket);
    }
}

Event::~Event() {
    this ->mTickets.clear();
}

int Event::getID() const{
    return this->mID;
}

void Event::setID(const int& rID) {
    this ->mID = rID;
}

void Event::insertTicket(const Ticket &t) {
    this ->mTickets.insert(t);
}

Ticket Event::popTicketWithPrice(double price) {
    Ticket aux_ticket = {price};
    auto it = this ->mTickets.find(aux_ticket);
    if (it != this->mTickets.end()) {
        return *it;
    }
    else {
        aux_ticket = {-1};
        return aux_ticket;
    }
}

std::string Event::peekLowestTicketPrice() {

    if (this ->mTickets.empty()) {
        return "No tickets available";
    }
    return "$" + std::to_string(this ->mTickets.begin() ->price);
}

std::string Event::popLowestTicketPrice() {

    std::string ticket_price = "$" + std::to_string(this ->mTickets.begin() ->price);
    this ->mTickets.erase(this ->mTickets.begin());

    return ticket_price;
}

std::vector<Ticket> Event::getTickets() const {
    std::vector<Ticket> v(this ->mTickets.size());
    std::copy(this ->mTickets.begin(), this ->mTickets.end(), v.begin());
    return v;
}




