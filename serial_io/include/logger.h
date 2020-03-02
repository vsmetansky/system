#pragma once

#include <stdarg.h>

void logg(char *message);
void logg_term(char *message);

void logg_series_one(char *message, int n, ...);
void logg_series_one_term(char *message, int n, ...);