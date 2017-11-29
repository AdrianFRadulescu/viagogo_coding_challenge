#include <iostream>
#include <string>
#include "event.h"
#include "event_plane.h"


int main() {

    std::vector<EventPlanePoint> event_points = generateRandomEvents(-10, -10, 10, 10);

    std::cout << "Generated events:\n";
    for (const auto &it : event_points) {
        std::cout << "(" << it.getX() << "," << it.getY() << "), Ticket prices: ";
        for (auto ticket : it.getEvent().getTickets()) {
            std::cout << "$" + std::to_string(ticket.price) << " ";
        }
        std::cout << "\n";
    }

    EventPlane event_plane = EventPlane(-10, -10, 11, 11, event_points);

    std::cout << "Please Input Coordinates:\n> ";

    std::string user_input;

    std::getline(std::cin, user_input);

    // parse user input
    int coordinates[2] = {0 , 0}, coord_index = 0, sign_index = 0, sign[2] = {1, 1};
    for (auto it : user_input) {
        if ('0' <= it && it <='9') {
            coordinates[coord_index] = coordinates[coord_index] * 10 + (it - '0');
        } else if (it == '-') {
            sign[sign_index ++] = -1;
        } else if (coord_index == 0 && it != 0) {
            coord_index ++;
            sign_index ++;
        }
    }

    for (int i = 0; i < 2; i ++)
        coordinates[i] *= sign[i];

    std::vector<EventPlanePoint> query_answer = event_plane.getNeighbourEventsOf(coordinates[0], coordinates[1]);

    std::cout << "Closest events to (" << coordinates[0] << "," << coordinates[1] << "):\n";

    for (auto it : query_answer) {
        std::cout << "Event " << it.getEvent().getID() << " - " << it.getEvent().peekLowestTicketPrice() <<", Distance " << it.getDistanceTo(coordinates[0], coordinates[1]) << "\n";
    }

    query_answer.clear();

    return 0;
}