#include "event_handler.hh"

long EventHandler::_id = 0;

long EventHandler::next_id() { return _id++; }

EventHandler::EventHandler() : numerical_id(EventHandler::next_id()) {}

EventHandler::~EventHandler() {}

long EventHandler::get_numerical_id() const { return numerical_id; }