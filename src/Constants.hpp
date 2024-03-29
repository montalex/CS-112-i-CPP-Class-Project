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

double const SEEKING_AUTOMATON_MAX_SPEED = 100;
double const SEEKING_AUTOMATON_MASS = 1;
double const SEEKING_AUTOMATON_RADIUS = 20;
double const SEEKING_DISTANCE_MID = 100;
double const SEEKING_DISTANCE_CLOSE = 30;

double const DECELERATION_WEAK = 1.9;
double const DECELERATION_MIDRANGE = 1.2;
double const DECELERATION_STRONG = 1.6;

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

#endif // INFOSV_CONSTANTS_HPP
