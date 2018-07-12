/*
 * Header for sunriset.c (http://stjarnhimlen.se/comp/sunriset.c), which
 * was released to the public domain by Paul Schlyter 
 * (http://stjarnhimlen.se/comp/riset.html)
 * 
 * Released to the public domain by A. Johnson (johnsj96@uw.edu), 11 July 2018
 */

#ifndef SUNRISET_H
#define SUNRISET_H

#ifdef __cplusplus
extern "C" {
#endif


/* Computes the length of the day, from sunrise to sunset.            */
/* Sunrise/set is considered to occur when the Sun's upper limb is    */
/* 35 arc minutes below the horizon (this accounts for the refraction */
/* of the Earth's atmosphere).                                        */
double day_length(int year, int month, int day, double lon, double lat);

/* Computes the length of the day, including civil twilight.            */
/* Civil twilight starts/ends when the Sun's center is 6 degrees below  */
/* the horizon.                                                         */
double day_civil_twilight_length(int year, int month, int day, double *start, double *end);

/* Computes the length of the day, incl. nautical twilight.             */
/* Nautical twilight starts/ends when the Sun's center is 12 degrees    */
/* below the horizon.                                                   */
double day_nautical_twilight_length(int year, int month, int day, double *start, double *end);

/* Computes the length of the day, incl. astronomical twilight.            */
/* Astronomical twilight starts/ends when the Sun's center is 18 degrees   */
/* below the horizon.                                                      */
double day_astronomical_twilight_length(int year, int month, int day, double *start, double *end);

/* Computes times for sunrise/sunset.                                 */
/* Sunrise/set is considered to occur when the Sun's upper limb is    */
/* 35 arc minutes below the horizon (this accounts for the refraction */
/* of the Earth's atmosphere).                                        */
int sun_rise_set(int year, int month, int day, double lon, double lat, double *start, double *end);

/* Computes the start and end times of civil twilight.                  */
/* Civil twilight starts/ends when the Sun's center is 6 degrees below  */
/* the horizon.                                                         */
int civil_twilight(int year, int month, int day, double lon, double lat, double *start, double *end);

/* Computes the start and end times of nautical twilight.               */
/* Nautical twilight starts/ends when the Sun's center is 12 degrees    */
/* below the horizon.                                                   */
int nautical_twilight(int year, int month, int day, double lon, double lat, double *start, double *end);

/* Computes the start and end times of astronomical twilight.              */
/* Astronomical twilight starts/ends when the Sun's center is 18 degrees   */
/* below the horizon.                                                      */
int astronomical_twilight(int year, int month, int day, double lon, double lat, double *start, double *end);


#ifdef __cplusplus
}
#endif

#endif /* SUNRISET_H */

