//
// Created by Radulescu Adrian on 22/11/2017.
//

#include "event_plane.h"

/**
 *
 * EventPlanePoint functions
 */

EventPlanePoint::EventPlanePoint(const int &rXCoord, const int &rYCoord) {
    this ->mXCoord = rXCoord;
    this ->mYCoord = rYCoord;

    this ->mEvent = Event(-1);

}

EventPlanePoint::EventPlanePoint(const int &rXCoord, const int &rYCoord, const Event& rEvent) {
    this ->mXCoord = rXCoord;
    this ->mYCoord = rYCoord;

    this ->mEvent = rEvent;
    this ->mNeighbourEvents.push_back(*this);
}

EventPlanePoint::EventPlanePoint(const int &rXCoord, const int &rYCoord, const int& rNumberOfPoints, const EventPlanePoint eventPoints[]) {
    this ->mXCoord = rXCoord;
    this ->mYCoord = rYCoord;

    this ->mEvent = Event(-1);

    for (int i = 0; i < rNumberOfPoints; i ++) {
        this ->mNeighbourEvents.push_back(eventPoints[i]);
    }
}

EventPlanePoint::EventPlanePoint(const int &rXCoord, const int &rYCoord, const std::vector<EventPlanePoint>& eventPoints) {
    this ->mXCoord = rXCoord;
    this ->mYCoord = rYCoord;

    this ->mEvent = Event(-1);

    for (int i = 0; i < eventPoints.size(); i ++) {
        this ->mNeighbourEvents.push_back(eventPoints[i]);
    }
}

EventPlanePoint::~EventPlanePoint() {
    this ->mNeighbourEvents.clear();
}

int EventPlanePoint::getX() const {
    return this ->mXCoord;
}

int EventPlanePoint::getY() const {
    return this ->mYCoord;
}

Event EventPlanePoint::getEvent() const {
    return this ->mEvent;
}

size_t EventPlanePoint::getNumberOfNeighbourEvents() const {
    return this ->mNeighbourEvents.size();
}


int EventPlanePoint::getDistanceTo(EventPlanePoint otherPoint) {
    return abs(this ->mXCoord - otherPoint.getX()) + abs(this ->mYCoord - otherPoint.getY());
}

int EventPlanePoint::getDistanceTo(const int& rXCoord, const int& rYCoord) {
    return abs(this ->mXCoord - rXCoord) + abs(this ->mYCoord - rYCoord);
}

const std::vector<EventPlanePoint>& EventPlanePoint::getNeighbourEvents() const {
    return this ->mNeighbourEvents;
}

void EventPlanePoint::setEvent(const Event& rEvent) {
    this ->mEvent = rEvent;
    this ->mNeighbourEvents.push_back(*this);
}

void EventPlanePoint::setNumberOfNeighbourEventsThreshold(const int& rNewThreshold) {
    this ->mNeighbourEventsSizeThreshold = rNewThreshold;
}

void EventPlanePoint::updateNeighbourEvents(const EventPlanePoint &rFirstNeighbour,
                                            const EventPlanePoint &rSecondNeighbour) {
    std::set<int> used_ids; /* a set of IDs of points which have already been put into this points list*/
    std::vector<EventPlanePoint> new_neighbours; /* the list of new neighbours*/

    std::function<int(EventPlanePoint, EventPlanePoint)> compare =
        [&](EventPlanePoint firstPoint, EventPlanePoint secondPoint) {
            return this ->getDistanceTo(firstPoint) < this ->getDistanceTo(secondPoint);
        };                                          /* the compare function to be used between when deciding
                                                       which event(point) is closer to this point*/

    std::function<void(EventPlanePoint)> insert_event_point = [&](EventPlanePoint eventPlanePoint){


        //std::cout << eventPlanePoint.getX() << " " << eventPlanePoint.getY() << "\n";

        if (used_ids.find(eventPlanePoint.getEvent().getID()) == used_ids.end()) {
            // the point is not in the current array of new neighbours
            new_neighbours.push_back(eventPlanePoint);
            used_ids.insert(eventPlanePoint.getEvent().getID());
            //std::cout << new_neighbours.size() << "\n";
        }
    };


    int i = 0;  /* an index iterator on the array of neighbours of this point*/
    int j = 0;  /* an index iterator on the array of neighbours of the first neighbour point*/
    int k  = 0; /* an index iterator on the array of neighbours of the second neighbour point*/

    // merge the three arrays

    for (; new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
               && i < this ->mNeighbourEvents.size()
               && j < rFirstNeighbour.getNeighbourEvents().size()
               && k < rSecondNeighbour.getNeighbourEvents().size();) {

        // get the closest point of the 3 present candidates

        if (compare(this->mNeighbourEvents[i], rFirstNeighbour.getNeighbourEvents()[j])
            &&compare(this->mNeighbourEvents[i], rSecondNeighbour.getNeighbourEvents()[k])) {

            // the neighbour from the current neighbours array is closest
            insert_event_point(this ->mNeighbourEvents[i]);
            i ++;
        } else {
            if (compare(rFirstNeighbour.getNeighbourEvents()[j], rSecondNeighbour.getNeighbourEvents()[k])) {
                insert_event_point(rFirstNeighbour.getNeighbourEvents()[j]);
                j ++;
            } else {
                insert_event_point(rSecondNeighbour.getNeighbourEvents()[k]);
                k ++;
            }

        }

    }

    for (;new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
             && i < this ->mNeighbourEvents.size()
             && j < rFirstNeighbour.getNeighbourEvents().size();) {

        if (compare(this ->mNeighbourEvents[i], rFirstNeighbour.getNeighbourEvents()[j])) {
            insert_event_point(this ->mNeighbourEvents[i]);
            i ++;
        } else {
            insert_event_point(rFirstNeighbour.getNeighbourEvents()[j]);
            j ++;
        }

    }


    for (; new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
               && i < this ->mNeighbourEvents.size()
               && k < rSecondNeighbour.getNeighbourEvents().size();) {

        if (compare(this ->mNeighbourEvents[i], rSecondNeighbour.getNeighbourEvents()[k])) {
            insert_event_point(this ->mNeighbourEvents[i]);
            i ++;
        } else {
            insert_event_point(rSecondNeighbour.getNeighbourEvents()[k]);
            k ++;
        }
    }

    for (;new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
             && j < rFirstNeighbour.getNeighbourEvents().size()
             && k < rSecondNeighbour.getNeighbourEvents().size();) {

        if (compare(rFirstNeighbour.getNeighbourEvents()[j], rSecondNeighbour.getNeighbourEvents()[k])) {
            insert_event_point(rFirstNeighbour.getNeighbourEvents()[j]);
            j ++;
        } else {
            insert_event_point(rSecondNeighbour.getNeighbourEvents()[k]);
            k ++;
        }
    }

    for (;new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
              && i < this ->mNeighbourEvents.size(); i ++){
        insert_event_point(this ->mNeighbourEvents[i]);
    }

    for (;new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
             && j < rFirstNeighbour.getNeighbourEvents().size(); j ++) {
        insert_event_point(rFirstNeighbour.getNeighbourEvents()[j]);
    }

    for (;new_neighbours.size() < this ->mNeighbourEventsSizeThreshold
              && k < rSecondNeighbour.getNeighbourEvents().size(); k ++) {
        insert_event_point(rSecondNeighbour.getNeighbourEvents()[k]);
    }

    // copy the resulting array to the original array
    this ->mNeighbourEvents.clear();
    for (i = 0; i < new_neighbours.size(); i ++) {
        this ->mNeighbourEvents.push_back(new_neighbours[i]);
    }
}


/**
 * EventPlane member functions
 */

EventPlane::EventPlane(const int& rXLower, const int& rYLower, const int& rXUpper, const int& rYUpper, const std::vector<EventPlanePoint>& rEventPoints) {

    this ->mXLower = rXLower;
    this ->mYLower = rYLower;
    this ->mXUpper = rYUpper;
    this ->mYUpper = rYUpper;

    this ->mRows = abs(rXUpper - rXLower) + 1; // using the X axis as rows
    this ->mCols = abs(rYUpper - rYLower) + 1; // using the Y axis as columns

    this ->mpGrid = new EventPlanePoint**[this ->mRows];


    // auxiliary grids for calculating the closest neighbour events

    EventPlanePoint ****pAuxGrid = new EventPlanePoint***[4];

    std::pair<int , int> x = {1,2};

    std::pair<int, int> grid_corners[4] = { {0, 0}, {0, this ->mCols - 1}, {this ->mRows - 1, 0}, {this ->mRows - 1, this ->mCols - 1}};
    std::pair<int, int> increments[4]   = { {1, 1,}, {1, -1}, {-1, 1}, {-1, -1}}; // the increments from each corner on the X and Y axis


    pAuxGrid[0]  = new EventPlanePoint**[this ->mRows]; // each cell contains the neighbour events from its upper left side
    pAuxGrid[1] = new EventPlanePoint**[this ->mRows]; // each cell contains the neighbour events from its upper right side
    pAuxGrid[2]  = new EventPlanePoint**[this ->mRows]; // each cell contains the neighbour events from its lower left side
    pAuxGrid[3] = new EventPlanePoint**[this ->mRows]; // each cell contains the neighbour events from its lower right side

    // initialize grids with points that initially don't have any events

    for (int i = 0; i < this ->mRows; i ++) {

        this ->mpGrid[i] = new EventPlanePoint*[this ->mCols];

        for (int k = 0; k < 4; k ++)
            pAuxGrid[k][i] = new EventPlanePoint*[this ->mCols];


        for (int j = 0; j <= this ->mCols; j ++) {
            this ->mpGrid[i][j] = new EventPlanePoint(i + this ->mXLower, j + this ->mYLower);

            for (int k = 0; k < 4; k ++)
                pAuxGrid[k][i][j] = new EventPlanePoint(i + this ->mXLower, j + this ->mYLower);
        }
    }

    std::cout << "grid and auxiliaries created\n";
    // initialize the points that contain events

    for (auto it = rEventPoints.begin(); it != rEventPoints.end(); it ++) {
         for (int k = 0; k < 4; k ++) {
             //std::cout << it ->getX() - this ->mXLower << " " << it ->getY() - this ->mYLower;

             pAuxGrid[k][it ->getX() - this ->mXLower][it ->getY() - this ->mYLower] ->setEvent(it ->getEvent());
             this ->mpGrid[it ->getX() - this ->mXLower][it ->getY() - this ->mYLower] ->setEvent(it ->getEvent());

             //std::cout << pAuxGrid[k][it ->getX() - this ->mXLower][it ->getY() - this ->getYLower()] ->getX() + 10 << " , " << pAuxGrid[k][it ->getX() - this ->mXLower][it ->getY() - this ->getYLower()] ->getY() + 10<< " " << pAuxGrid[k][it ->getX() - this ->mXLower][it ->getY() - this ->getYLower()] ->getNeighbourEvents().size() << "\n";
         }
    }

    std::cout << "points added to the plane\n";

    // a function that checks if a given index is within the bounds of the grid
    std::function<bool(int, int, int, int)> check_if_within_bounds = [](int index, int increment_value, int lower_bound, int upper_bound){
        return index - increment_value >= lower_bound && index - increment_value < upper_bound;
    };

    for (int k = 0; k < 4; k ++) {
        //std::cout << k << "/////////////////////////////////////////// " << grid_corners[3 - k].first << " " << grid_corners[3 - k].second << "\n";

        for (int i = grid_corners[k].first; i != grid_corners[3 - k].first; i += increments[k].first) {
            for (int j = grid_corners[k].second; j != grid_corners[3 - k].second; j += increments[k].second) {

                bool i_condition = check_if_within_bounds(i, increments[k].first, 0, this ->mRows);
                bool j_condition = check_if_within_bounds(j, increments[k].second, 0, this ->mCols);

                // check if updates can be made from both neighbour points

                if (i_condition && j_condition) {
                    pAuxGrid[k][i][j]->updateNeighbourEvents(*pAuxGrid[k][i][j - increments[k].second], *pAuxGrid[k][i - increments[k].first][j]);
                } else if (j_condition) {
                    pAuxGrid[k][i][j]->updateNeighbourEvents(*pAuxGrid[k][i][j - increments[k].second], *pAuxGrid[k][i][j - increments[k].second]);
                } else if (i_condition) {
                    pAuxGrid[k][i][j]->updateNeighbourEvents(*pAuxGrid[k][i - increments[k].first][j], *pAuxGrid[k][i - increments[k].first][j]);
                }

            }
        }
    }

    std::cout << "\n individual calculations made\n";

    // combine the results of the 4 matrices

    for (int i = 0; i < this ->mRows; i ++) {
        for (int j = 0; j < this ->mCols; j ++) {
            for (int k = 0; k < 4; k ++){

                bool i_condition = check_if_within_bounds(i, increments[k].first, 0, this ->mRows);
                bool j_condition = check_if_within_bounds(j, increments[k].second, 0, this ->mCols);

                if (i_condition && j_condition) {
                    this ->mpGrid[i][j] ->updateNeighbourEvents(*pAuxGrid[k][i][j - increments[k].second], *pAuxGrid[k][i - increments[k].first][j]);
                } else if (j_condition) {
                    this ->mpGrid[i][j] ->updateNeighbourEvents(*pAuxGrid[k][i][j - increments[k].second], *pAuxGrid[k][i][j - increments[k].second]);
                } else if (i_condition) {
                    this ->mpGrid[i][j] ->updateNeighbourEvents(*pAuxGrid[k][i - increments[k].first][j], *pAuxGrid[k][i - increments[k].first][j]);
                }
            }
        }
    }

    std::cout << "final calculations made\n";

    // delete the auxiliary matrices

    for (int i = 0; i < this ->mRows; i ++) {
        for (int j = 0; j < this ->mCols; j ++)
            for (int k = 0; k < 4; k ++)
                delete pAuxGrid[k][i][j];

        for (int k = 0; k < 4; k ++)
            delete pAuxGrid[k][i];
    }

    for (int k = 0; k < 4; k ++)
        delete pAuxGrid[k];
    std::cout << "mem freed\n";
}

int EventPlane::getXLower() const {
    return mXLower;
}

int EventPlane::getYLower() const {
    return mYLower;
}

int EventPlane::getXUpper() const {
    return mXUpper;
}

int EventPlane::getYUpper() const {
    return mYUpper;
}

EventPlane::~EventPlane() {

    for (int i = 0; i < this ->mRows; i ++) {
        for (int j = 0; j < this ->mCols; j ++)
                delete this ->mpGrid[i][j];

        delete this ->mpGrid[i];
    }
}

std::vector<EventPlanePoint> EventPlane::getNeighbourEventsOf(const int& rXCoord, const int& rYCoord) {
    return this ->mpGrid[rXCoord - this ->mXLower][rYCoord - this ->mYLower] ->getNeighbourEvents();
}


void EventPlane::setXUpper(int mXUpper) {
    EventPlane::mXUpper = mXUpper;
}

void EventPlane::setYUpper(int mYUpper) {
    EventPlane::mYUpper = mYUpper;
}

void EventPlane::setYLower(int mYLower) {
    EventPlane::mYLower = mYLower;
}

void EventPlane::setXLower(int mXLower) {
    EventPlane::mXLower = mXLower;
}

void EventPlane::setGrid(EventPlanePoint ***pGrid) {
    EventPlane::mpGrid = pGrid;
}



EventPlanePoint ***EventPlane::getGrid() const {
    return mpGrid;
}

// other functions

std::vector<EventPlanePoint> generateRandomEvents(const int& rXLower, const int& rYLower, const int& rXUpper, const int& rYUpper) {

    // create seed and generateor
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> x_coordinate_distribution(rXLower, rXUpper);
    std::uniform_int_distribution<> y_coordinate_distribution(rYLower, rYUpper);
    std::uniform_int_distribution<> number_of_elements_distribution(0, 50);
    std::uniform_real_distribution<> price_distribution(0, 100);

    int x_coord;
    int y_coord;
    int x_already_used[rXUpper - rXLower + 1];  // x_already_used[i] there is at least one point on the ith vertical
    int y_already_used[rYUpper - rYLower + 1];  // y_already_used[i] there is at least one point on the ith horizontal

    memset(x_already_used, 0, sizeof(x_already_used));
    memset(y_already_used, 0, sizeof(y_already_used));

    std::vector<EventPlanePoint> points;

    int limit = number_of_elements_distribution(generator) ;
    size_t number_of_tickets;
    //std::cout << "nr of elem: " << limit << "\n";
    for (int i = 0; i < limit; i ++) {

        x_coord = x_coordinate_distribution(generator) - rXLower;
        y_coord = y_coordinate_distribution(generator) - rYLower;
        //std::cout << x_coord << " " << y_coord << "\n";

        if (x_already_used[x_coord]
            &&y_already_used[y_coord]) {
            continue;
        }

        // mark point as used
        x_already_used[x_coord] = 1;
        y_already_used[y_coord] = 1;

        //std::cout << x_coord << " " << y_coord << "\n";
        // generate random number of tickets with random prices
        number_of_tickets = (size_t) number_of_elements_distribution(generator);
        Ticket tickets[number_of_tickets];
        for (int j = 0; j < number_of_tickets; j ++)
            tickets[j] = {price_distribution(generator)};
        //std::cout << number_of_tickets << "\n";
        points.emplace_back(x_coord + rXLower, y_coord + rYLower, Event(i, number_of_tickets, tickets));
        //std::cout << "finished point "<< i << " \n";
    }
    return points;
}