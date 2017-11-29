//
// Created by Radulescu Adrian on 22/11/2017.
//

#ifndef VIAGOGO_CODING_CHALLENGE_EVENT_GRID_H
#define VIAGOGO_CODING_CHALLENGE_EVENT_GRID_H

#include "event.h"
#include <queue>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>

/**
 * Represents a general point(may or may not contain an event) in the event plane
 */

class EventPlanePoint {

    private:
    int mXCoord;
    int mYCoord;
    Event mEvent;

    int mNeighbourEventsSizeThreshold = 5;          /*!< the maximum number of close events to be considered, 5 in this case */
    std::vector<EventPlanePoint> mNeighbourEvents;      /*!< the closest events to this point */

    public:

    /**
     * @brief Constructs a point in the plane with and empty neighbour event array(vector) with no registered envent
     */

    EventPlanePoint(const int&, const int&);

    EventPlanePoint(const int&, const int&, const Event&);

    EventPlanePoint(const int&, const int&, const int&, const EventPlanePoint[]);

    EventPlanePoint(const int&, const int&, const std::vector<EventPlanePoint>&);

    ~EventPlanePoint();

    // getters

    /**
     * @return the x coordinate of the point
     */

    int getX() const;

    /**
     * @return the y coordinate of the point
     */

    int getY() const;

    /**
     * @return the event contained in this point if any
     */

    Event getEvent() const;

    /**
     * @return the number of neighbour events this point has
     */

    size_t getNumberOfNeighbourEvents() const;

    /**
     * Calculates the Manhattan distance to the given point
     * @param otherPoint  the point to which the distance is calculated
     * @return  the Manhattan distance
     */

    int getDistanceTo(EventPlanePoint otherPoint);

    /**
     * Calculates the Manhattan distance to the point described by the given coordinates
     * @return  the Manhattan distance
     */

    int getDistanceTo(const int&, const int&);

    /**
     * Returns an array of the closest events(up to mNeighbourEventsSizeThreshold) to this point
     * @return
     */

    const std::vector<EventPlanePoint>& getNeighbourEvents() const;

    // setters

    void setEvent(const Event&);

    /**
     * @brief sets the new neighbour event threshold to the given parameter
     * @param
     */

    void setNumberOfNeighbourEventsThreshold(const int&);

    /**
     * Recalculate the neighbour events to this point using the data provided from the given neighbour points
     * Merges the three EventPlanePoint arrays of neighbours until the new array contains the maximum addmited number of
     * elements(mNeighbourEventsSizeThreshold = 5)
     * @param rFirstNeighbour
     * @param rSecondNeighbour
     */

    void updateNeighbourEvents(const EventPlanePoint &rFirstNeighbour, const EventPlanePoint &rSecondNeighbour);

};


/**
 * A data structure containing all points in the plane that contain events
 * Implemented as a 2D Binary Search Tree where nodes that contain events objects
 * Contains a density matrix
 */

class EventPlane {

    private:

    int mXLower; /*!< the lower bound of the grid on the X axis*/
    int mYLower; /*!< the lower bound of the grid on the Y axis*/
    int mXUpper; /*!< the upper bound of the grid on the X axis*/
    int mYUpper; /*!< the upper bound of the grid on the Y axis*/

    int mRows;  /*!< the number of rows in the matrix representing the plane*/
    int mCols;  /*!< the number of colums in the matrix representing the plane*/

    EventPlanePoint ***mpGrid;

    public:

    /**
     * Creates an empty plane
     */
    EventPlane(const int&, const int&, const int&, const int&, const std::vector<EventPlanePoint>&);
    ~EventPlane();

    // getters and setters

    int getXLower() const;

    int getYLower() const;

    int getXUpper() const;

    int getYUpper() const;

    EventPlanePoint ***getGrid() const;

    std::vector<EventPlanePoint> getNeighbourEventsOf(const int&, const int&);

    // setters

    void setXLower(int mXLower);

    void setYLower(int mYLower);

    void setXUpper(int mXUpper);

    void setYUpper(int mYUpper);

    void setGrid(EventPlanePoint ***pGrid);

};

std::vector<EventPlanePoint> generateRandomEvents(const int& rXLower, const int& rYLower, const int& rXUpper, const int& rYUpper);

#endif //VIAGOGO_CODING_CHALLENGE_EVENT_GRID_H
