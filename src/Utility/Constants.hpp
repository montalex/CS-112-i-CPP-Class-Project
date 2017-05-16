/*
 * prjsv 2016
 * Marco Antognini
 */

#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>

// Numerical constants
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307;         ///< TAU constant (= 2 * PI)
double const PI = 3.141592654;          ///< PI constant
double const EPSILON = 1e-8;            ///< a small epsilon value

// Stats titles
namespace s
{

std::string const GENERAL = "general";
std::string const WOLVES = "wolves";
std::string const SHEEP   = "sheep";
std::string const GRASS  = "grass";
std::string const INFECTED  = "infected";
std::string const ANIMAL_INDIVIDUAL = "Tracked Animal";
std::string const GRASS_INDIVIDUAL   = "Tracked grass";

std::string const INDIVIDUAL = "Tracked Animal";
std::string const HEALTH = "health";
std::string const ENERGY = "energy";
std::string const VIRUS = "virus";
std::string const SCORE = "score";
std::string const ADASCORE = "adapt-score";
std::string const IMUNAC= "immune-act";


} // s


// Ad'hoc constants
// Seeking Automaton
double const SEEKING_AUTOMATON_MAX_SPEED = 100;
double const SEEKING_AUTOMATON_MASS = 1;
double const SEEKING_AUTOMATON_RADIUS = 20;
double const SEEKING_DISTANCE_MID = 100;
double const SEEKING_DISTANCE_CLOSE = 30;

// Animal
double const ANIMAL_MAX_SPEED = 100;
double const ANIMAL_MASS = 1;
double const ANIMAL_RADIUS = 50;
double const ANIMAL_VIEW_RANGE = 60 * DEG_TO_RAD;
double const ANIMAL_VIEW_DISTANCE = 300;

// Deceleration
double const DECELERATION_WEAK = 1.9;
double const DECELERATION_MIDRANGE = 1.2;
double const DECELERATION_STRONG = 1.6;


/// Random walk jitter
double const ANIMAL_RANDOM_WALK_JITTER = 7;

/// Random walk radius
double const ANIMAL_RANDOM_WALK_RADIUS = 50;

/// Random walk distance
double const ANIMAL_RANDOM_WALK_DISTANCE = 160;

int const ANIMAL_AVOIDANCE_WEIGHT = 2000;
int const ANIMAL_PROXIMITY_MIN = 60;

#endif // INFOSV_CONSTANTS_HPP
